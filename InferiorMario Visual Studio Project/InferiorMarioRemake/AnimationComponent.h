#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"

// Circular dependency workaround
class Entity;

class AnimationComponent
{
public:
	// Constructors & Destructors
	AnimationComponent(void);
	virtual ~AnimationComponent(void);

	// Functions
	virtual void Initialize(Entity& entity, const std::string& filePath);
	virtual void Update(Entity& entity);
	void RestartTimer(void) { animationClock.restart(); }

	// Getters & Setters
	sf::Texture& getTexture(void) { return texture; }
	int getMilliseconds(void) const { return animationClock.getElapsedTime().asMilliseconds(); }
	int getInterval(void) const { return interval; }

protected:
	// Objects
	sf::Clock animationClock;
private:
	// Objects
	sf::Texture texture;
	
	// Variables
	int interval;
	int currentFrame;
};

