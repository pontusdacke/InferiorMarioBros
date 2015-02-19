#include "CollisionManager.h"
#include "Entity.h"
#include "Enemy.h"

bool ObjectCollision(sf::RenderWindow &window, Level& level, Camera &camera, Entity &entity, int &object)
{
	sf::FloatRect entityRectangle = entity.sprite.getGlobalBounds();
	entityRectangle.width += entityRectangle.left;
	entityRectangle.height += entityRectangle.top;

	Entity* obj; // Object
	sf::IntRect bounds = camera.GetTileBounds(window, 32);

	for (int x = 0; x < 3; x++)
	{
		// Get the tile we are drawing
		obj = level.GetEnemy(x);
		if(obj)// && entity.velocity.y > 0)
		{
			// Get the rectangle around the tile
			sf::FloatRect objRectangle(obj->sprite.getPosition().x,
				obj->sprite.getPosition().y,
				obj->sprite.getPosition().x + 32,
				obj->sprite.getPosition().y + 32);

			// Check if the player intersects with the tile
			if(Intersect(entityRectangle, objRectangle))	
			{
				object = x; // Store the array-position of the object
				return true;
			}
		}
	}
	return false;
}
bool Collision(sf::RenderWindow &window, const Level &level, Camera &camera, Entity &entity, sf::FloatRect &collisionRectangle, sf::Vector2i &baseTile)
{
	// Rectangle surrounding player
	sf::FloatRect entityRectangle = entity.sprite.getGlobalBounds();
	entityRectangle.width += entityRectangle.left;
	entityRectangle.height += entityRectangle.top;

	int tileSize = 32;
	BaseTile* tile;
	CollisionTile* cTile;
	// Loop through all tiles
	sf::IntRect bounds = camera.GetTileBounds(window, tileSize);
	for (int y = bounds.top; y < bounds.height + bounds.top; y++)
	{
		for (int x = bounds.left; x < bounds.width + bounds.left; x++)
		{
			// Get the tile we are drawing
			tile = level.GetTile(x, y);
			if(tile) cTile = static_cast<CollisionTile*>(tile);
			if(cTile && !cTile->GetWalkable())
			{
				// Get the rectangle around the tile
				sf::FloatRect tileRectangle(cTile->GetSprite().getPosition().x,
					cTile->GetSprite().getPosition().y,
					cTile->GetSprite().getPosition().x + tileSize,
					cTile->GetSprite().getPosition().y + tileSize);

				// Check if the player intersects with the tile
				if(Intersect(entityRectangle, tileRectangle)) 
				{
					baseTile = sf::Vector2i(x, y); // Store the array-position of the tile
					collisionRectangle = tileRectangle; // Store the world-position of the rectangle
					return true;
				}
			}
		}
	} 
	return false;
}

// Intersection method (SFML's built in doesen't work)
bool Intersect(const sf::FloatRect &rectA, const sf::FloatRect &rectB)
{
	return !(rectB.left > rectA.width ||
		    rectB.width < rectA.left ||
			rectB.top > rectA.height ||
			rectB.height < rectA.top);
}