 #include "BaseTile.h"
#include "TextureHandler.h"
#include "Level.h"
#include "Entity.h"
#include "Player.h"

BaseTile::BaseTile(void)
{
	animate = false;
	hasLifeTime = false;
	visible = true;
	coinBuffer.loadFromFile("smb_coin.wav");
	coinSound.setBuffer(coinBuffer);
}
BaseTile::BaseTile(const sf::Texture& texture, sf::Vector2f position, TextureHandler* txtHandler, const std::string& id, int lifeTimeInMilliseconds) 
	: textureHandler(txtHandler),
	id(id)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
	stdPosition = position;
	animate = false;
	visible = true;
	lifeTimeMS = lifeTimeInMilliseconds;
	if (lifeTimeInMilliseconds < 0) hasLifeTime = false;
	else hasLifeTime = true;
	coinBuffer.loadFromFile("smb_coin.wav");
	coinSound.setBuffer(coinBuffer);
}
BaseTile::~BaseTile(void) { }

// Getters & Setters
const sf::Sprite& BaseTile::GetSprite() const { return sprite; }

// Functions
void BaseTile::Draw(sf::RenderWindow& window)
{
	if (sprite.getPosition().y < stdPosition.y - 5) 
		animate = false;
	if (animate)
		sprite.move(0, -2);
	if (!animate && sprite.getPosition().y < stdPosition.y)
		sprite.move(0, 2);

	if (hasLifeTime && lifeClock.getElapsedTime().asMilliseconds() > lifeTimeMS)
		visible = false;

	if (visible)
		window.draw(sprite);
}
void BaseTile::Hit(Entity& entity, Level& level)
{
	Player* player = static_cast<Player*>(&entity);
	animate = true;

	// NOTE TO SELF: This we want to do using inheritance instead.
	if(id == "D") // Coinblock
	{
		coinSound.play();
		SpawnCoin(level);
		player->AddCoins(1);
	}
}
void BaseTile::SpawnCoin(Level& level)
{
	sprite.setTexture(textureHandler->GetTexture("C")); // Change texture to used coinblock
	id = "C";
	// Spawn a coin over the block we collided with
	SpawnObject(new BaseTile(textureHandler->GetTexture("*"), sf::Vector2f(stdPosition.x, stdPosition.y - 32), 
		textureHandler, "*", 300), level);
}
void BaseTile::SpawnMushroom(Level& level)
{
	sprite.setTexture(textureHandler->GetTexture("C")); // Change texture to used coinblock
}
void BaseTile::SpawnObject(BaseTile* tile, Level& level)
{
	level.AddObject(stdPosition.x / 32, stdPosition.y / 32 - 1, tile); // -1 to spawn ABOVE our block
}
