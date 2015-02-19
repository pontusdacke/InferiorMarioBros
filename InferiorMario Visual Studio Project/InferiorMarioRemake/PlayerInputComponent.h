#pragma once
#include "InputComponent.h"
#include <SFML\Audio.hpp>

class Entity;

class PlayerInputComponent :
	public InputComponent
{
public:
	// Constructors & Destructors
	PlayerInputComponent(float walkAcceleration, float jumpAcceleration);
	virtual ~PlayerInputComponent(void);

	// Functions
	virtual void Update(Entity& entity);
private:
	// Objects
	sf::SoundBuffer buffer;
	sf::Sound jumpSound;
};

