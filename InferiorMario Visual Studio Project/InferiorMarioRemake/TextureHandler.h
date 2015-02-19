#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <map>
#include <fstream>
#include "BaseTile.h"
#include "rapidxml.hpp"

class TextureHandler
{
public:
	TextureHandler(void);
	~TextureHandler(void);

	void SetTileSize(int tileSize);
	void LoadTileset(const std::string& filename);
	void AddTexture(const sf::Texture& texture, const std::string& id);
	sf::Texture& GetTexture(const std::string& index);
private:
	std::vector<sf::Texture> textureList;
	std::map<std::string, int> textureIDs;
	int tileSize;
};

