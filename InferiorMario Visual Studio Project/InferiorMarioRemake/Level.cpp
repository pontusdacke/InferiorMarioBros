#include "Level.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"
#include "EnemyInputComponent.h"
#include "EnemyPhysicsComponent.h"

Level::Level(void)
{
	enemyCount = 0;
}
Level::~Level(void)
{
	// Clear the arrays 
	for (int y = 0; y < dimensions.y; y++)
	{
		for (int x = 0; x < dimensions.x; x++)
		{
			DeleteTile(x, y);
			DeleteObject(x, y);
		}
	}
}
const sf::Vector2i& Level::GetDimensions(void) const
{
	return dimensions;
}
void Level::SetDimensions(int width, int height)
{
	// Set dimensions for map and objectMap assuming there can only be objects in the map range
	// Setting 100 as size on enemyList. We wont ever pass 100 enemies per map.
	enemyList.resize(100);
	map.resize(width);
	objectMap.resize(width);
	for (int i = 0; i < width; i++)
	{
		map[i].resize(height, 0);
		objectMap[i].resize(height, 0);
	}
	dimensions = sf::Vector2i(width,height);
}
void Level::AddTile(int x, int y, CollisionTile* tile)
{
	// Add a tile to the map
	if(tile)
		map[x][y] = tile;
}
void Level::AddObject(int x, int y, BaseTile* baseTile)
{
	// Add an object to the object map
	if(baseTile)
		objectMap[x][y] = baseTile;
}
void Level::AddEnemy(int x, Enemy* enemy)
{
	if(enemy) 
	{
		enemyList[x] = enemy;
		enemy->Initialize();
	}
}
CollisionTile* Level::GetTile(unsigned int x, unsigned int y) const
{
	// Retrieve a tile from the map
	if(x < map.capacity() && y < map[x].capacity())
		return map[x][y];
	return NULL;
}
BaseTile* Level::GetObject(unsigned int x, unsigned int y) const
{
	// Retrieve a object from the object map
	if(x < objectMap.capacity() && y < objectMap[x].capacity())
		return objectMap[x][y];
	return NULL;
}
Enemy* Level::GetEnemy(unsigned int x) const
{
	if (x < enemyList.capacity())
		return enemyList[x];
	return NULL;
}
void Level::LoadLevel(const std::string& filename, TextureHandler& textureHandler)
{
	// Load level data from file
	// Load from xml
	std::ifstream inFile(filename);
	// Check if we could open the file
	if(!inFile) throw "Could not load level: " + filename;

	std::string xmlContents, line;
	while(std::getline(inFile, line))
		xmlContents += line;
	
	// Convert string to rapidxml readable char* pointer
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	// Created a parsed document with &xmlData[0] which is the char*
	rapidxml::xml_document<char> doc;
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

	// Get root node
	rapidxml::xml_node<char>* root = doc.first_node();

	// Get level attributes
	int width = std::stoi(root->first_attribute("width")->value());
	int height = std::stoi(root->first_attribute("height")->value());

	// Resize level
	SetDimensions(width, height);
	// Load each necessary tileset
	rapidxml::xml_node<char>* tileset = root->first_node("tileset");
	while(tileset)
	{
		std::string path = tileset->first_attribute("path")->value();
		// Load tileset
		textureHandler.LoadTileset(path);
		// Go to next tileset
		tileset = tileset->next_sibling("tileset");
	}

	// Load all tiles
	rapidxml::xml_node<char>* node = root->first_node("tile");
	while(node)
	{
		// Read values from xml file
		int x = std::stoi(node->first_attribute("x")->value());
		int y = std::stoi(node->first_attribute("y")->value());
		std::string baseid =node->first_attribute("baseid")->value();

		std::string walkString = node->first_attribute("walkable")->value();
		bool walkable = (walkString == "true")? true : false;

		// Create tile and add it to level ( new destroyed in deconstructor )
		CollisionTile* newTile = new CollisionTile(textureHandler.GetTexture(baseid), sf::Vector2f(x*32, y*32), walkable, &textureHandler, baseid);
		AddTile(x, y, newTile);

		// Go to next node
		node = node->next_sibling("tile");
	}

	// Load all enemies
	node = root->first_node("enemy");
	while(node)
	{
		int x = std::stoi(node->first_attribute("x")->value());
		int y = std::stoi(node->first_attribute("y")->value());
		sf::Vector2f pos = sf::Vector2f(x * 32, y * 32);
		Enemy* newEnemy = new Enemy(new EnemyInputComponent(3), new EnemyPhysicsComponent(), new EnemyAnimationComponent(), pos);
		AddEnemy(enemyCount, newEnemy);
		
		node = node->next_sibling("enemy");
		enemyCount++;
	}
}
// Templating these delete functions for shortage of code affected performance greatly!
void Level::DeleteTile(int x, int y)
{
	// Delete tile pointers
	if(map[x][y] != NULL)
	{
		delete map[x][y];
		map[x][y] = NULL;
	}
}
void Level::DeleteObject(int x, int y)
{
	// Delete object pointers
	if(objectMap[x][y] != NULL)
	{
		delete objectMap[x][y];
		objectMap[x][y] = NULL;
	}
}
void Level::DeleteEnemy(int x)
{
	// Delete enemy by index
	if(enemyList[x] != NULL)
	{
		delete enemyList[x];
		enemyList[x] = NULL;
	}
}
void Level::Draw(sf::RenderWindow& window, Camera& camera)
{
	BaseTile* object;
	// Calculate the bounds of the screen
	sf::IntRect bounds(camera.GetTileBounds(window, 32));
		
	for (int y = bounds.top; y < bounds.height; y++)
	{
		for (int x = bounds.left; x < bounds.width; x++)
		{
			// Retrieve tile and draw it
			object = GetTile(x, y);
			if (object) 
				object->Draw(window);

			// Retrieve object and draw it
			object = GetObject(x, y);
			if (object) 
				object->Draw(window);
		}
	}
}
void Level::DrawEnemies(sf::RenderWindow& window, Camera& camera)
{
	for (int i = 0; i < enemyCount; i++)
	{
		if (enemyList[i])
			enemyList[i]->Draw(window);
	}
}
void Level::UpdateEnemies(sf::RenderWindow& window, Camera& camera)
{
	for (int i = 0; i < enemyCount; i++)
	{		
		if (enemyList[i] && !enemyList[i]->IsAlive() && enemyList[i]->deathTimer.getElapsedTime().asMilliseconds() > 300) 
		{
			DeleteEnemy(i);
			break; // We deleted the enemy, lets not continue...
		}
		// Update the enemies
		if (enemyList[i])
			enemyList[i]->Update(camera, *this, window);
	}
}