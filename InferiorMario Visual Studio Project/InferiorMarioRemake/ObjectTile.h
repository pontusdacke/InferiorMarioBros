#pragma once
#include "BaseTile.h"

class ObjectTile :
	public BaseTile
{
public:
	ObjectTile(const sf::Texture& texture, sf::Vector2f position, TextureHandler* textureHandler, const std::string& id);
	~ObjectTile(void);
	virtual void Hit(Entity& entity, Level& level);
private:
};

