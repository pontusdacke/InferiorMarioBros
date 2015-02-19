#pragma once
#include "basetile.h"
class CollisionTile :
	public BaseTile
{
public:
	// Constructors & Destructors
	CollisionTile(const sf::Texture& texture, sf::Vector2f position, bool walkable, TextureHandler* txtHandler, const std::string& id);
	~CollisionTile(void);

	// Getters & Setters
	bool GetWalkable(void) const;
private:
	// Variabels
	bool walkable;
};

