#include "TextureHandler.h"


TextureHandler::TextureHandler(void) { }
TextureHandler::~TextureHandler(void) { }

void TextureHandler::AddTexture(const sf::Texture& texture, const std::string& id)
{
	textureList.push_back(texture);
	// Pair texture id with texture index
	textureIDs[id] = textureList.size() - 1;
}
sf::Texture& TextureHandler::GetTexture(const std::string& index)
{
	return textureList[textureIDs[index]];
}
void TextureHandler::SetTileSize(int tileSize) { this->tileSize = tileSize; }
void TextureHandler::LoadTileset(const std::string& filename)
{
	// Load file into an ifstream
	std::ifstream inFile(filename);

	// Failcheck
	if(!inFile) throw "Could not load tileset: " + filename;

	// Put file contents in this string
	std::string xmlContents;
	{
		std::string line;
		while(std::getline(inFile, line))
			xmlContents += line;
	}
	//Convert string to rapidxml readable char*
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0'); 

	// Create a parsed document with &xmlData[0] which is the char* pointer
	rapidxml::xml_document<char> doc;
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

	// Get Root Node
	rapidxml::xml_node<char>* root = doc.first_node();

	std::string imagePath;
	sf::Image tileset;

	rapidxml::xml_node<char>* imagefile = root->first_node("imagefile");
	while(imagefile)
	{
		// Get and parse image file, and then load.
		imagePath = imagefile-> first_attribute("path")->value();
		tileset.loadFromFile(imagePath);

		// Go through each tile
		rapidxml::xml_node<char>* tile = imagefile->first_node("tile");
		while(tile)
		{
			// Get all attributes
			int x = std::stoi(tile->first_attribute("x")->value());
			int y = std::stoi(tile->first_attribute("y")->value());
			int frames = std::stoi(tile->first_attribute("frames")->value());
			std::string id = tile->first_attribute("id")->value();

			// Copy the right tile image from tileset
			sf::Image tileImage;
			tileImage.create(tileSize, tileSize);
			tileImage.copy(tileset, 0, 0, sf::IntRect(x * tileSize, y * tileSize, frames * tileSize, tileSize), true);

			// Add image to texture list
			sf::Texture temp;
			temp.loadFromImage(tileImage);
			AddTexture(temp, id);

			// Go to next tile
			tile = tile->next_sibling();
		}

		// Go to next imageFile
		imagefile = imagefile->next_sibling();
	}
}
