#include "CollisionTile.h"


CollisionTile::CollisionTile(const sf::Texture& texture, sf::Vector2f position, bool walkable, TextureHandler* txtHandler, const std::string& id)
	: BaseTile(texture, position, txtHandler, id, -1),
	walkable(walkable)
{ }
CollisionTile::~CollisionTile(void) { }

// Getters & Setters
bool CollisionTile::GetWalkable(void) const { return walkable; }