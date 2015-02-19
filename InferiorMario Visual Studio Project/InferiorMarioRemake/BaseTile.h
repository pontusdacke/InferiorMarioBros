#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

// Bypass circular dependencies
class TextureHandler;
class Level;
class Entity;

class BaseTile
{
public:
	// Constructors & Destructors
	BaseTile(void);
	BaseTile(const sf::Texture& texture, sf::Vector2f position, TextureHandler* textureHandler, 
			 const std::string& id, int lifeTimeInMilliseconds);
	virtual ~BaseTile(void);

	// Getters & Setters
	const sf::Sprite& GetSprite() const;
	
	// Functions
	virtual void Draw(sf::RenderWindow& window);
	virtual void Hit(Entity& entity, Level& level);

protected:
	// Variables
	bool animate;
	bool hasLifeTime;
	int lifeTimeMS;
	bool visible;

	// Objects & Classes
	TextureHandler* textureHandler;
	std::string id;
	sf::Clock lifeClock;
	sf::Vector2f stdPosition; // Standard position. The original position
	sf::Sprite sprite;
	sf::SoundBuffer coinBuffer;
	sf::Sound coinSound;

	// Functions
	void SpawnCoin(Level& level);
	void SpawnMushroom(Level& level);
private:
	// Functions
	void SpawnObject(BaseTile* tile, Level& level);
};

