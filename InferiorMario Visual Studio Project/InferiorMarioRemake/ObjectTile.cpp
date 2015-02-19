#include "ObjectTile.h"


ObjectTile::ObjectTile(const sf::Texture& texture, sf::Vector2f position, TextureHandler* txtHandler, const std::string& id)
	: BaseTile(texture, position, txtHandler, id)
{ }
ObjectTile::~ObjectTile(void) { }

void ObjectTile::Hit(Entity& entity, Level& level)
{
	animate = true;
	//if(id == "D") // Coinblock
	//{
	//	sprite.setTexture(textureHandler->GetTexture("C")); // Change texture to used coinblock
	//	// Spawn a coin over the block we collided with
	//	level.AddObject(stdPosition.x / 32, stdPosition.y / 32 - 1, 
	//		new BaseTile(textureHandler->GetTexture("*"), sf::Vector2f(stdPosition.x, stdPosition.y - 32), 
	//		textureHandler, "*"));
	//}
}