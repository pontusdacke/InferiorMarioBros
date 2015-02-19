#pragma once
#include "PhysicsComponent.h"
#include <SFML\Audio.hpp>

class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	// Constructors & Destructors
	PlayerPhysicsComponent(void);
	virtual ~PlayerPhysicsComponent(void);

	// Functions
	virtual void Update(Entity& entity, Level& level, Camera& camera, sf::RenderWindow& window);
	virtual void CollisionResponseYAxis(Entity &entity, Camera &camera, Level &level);
	virtual void CollisionResponseObject(Entity& entity, Camera &camera, Level &level);
private:
	// Objects
	sf::Clock jumpClock;
	sf::SoundBuffer kickBuffer, bumpBuffer;
	sf::Sound kickSound, bumpSound;
};

