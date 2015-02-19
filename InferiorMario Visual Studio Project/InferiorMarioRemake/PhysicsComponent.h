#pragma once
#include <SFML\Graphics.hpp>
#include "Camera.h"
#include "Level.h"
#include "CollisionManager.h"

class Entity; 

class PhysicsComponent
{
public:
	// Constructors & Destructors
	PhysicsComponent(void);
	virtual ~PhysicsComponent(void);

	// Collision variables/objects
	sf::FloatRect collisionRectangle;
	sf::Vector2i collisionTile;
	int collisionObject;

	// Functions
	virtual void Update(Entity& entity, Level& level, Camera& camera, sf::RenderWindow& window);
	virtual void CollisionResponseXAxis(Entity& entity, Camera& camera, Level& level);
	virtual void CollisionResponseYAxis(Entity& entity, Camera& camera, Level& level);
	virtual void CollisionResponseObject(Entity& entity, Camera &camera, Level &level);

	// Getters & Setters
	float getGravity(void) const { return gravity; }
	float getMaxFallSpeed(void) const { return maxFallSpeed; }
	const sf::Vector2f& getLastPosition(void) const { return lastPosition; }
	void setLastPosition(sf::Vector2f vector) { lastPosition = vector; }
	sf::FloatRect getCollisionRectangle(void) { return collisionRectangle; }

private:
	// Variables
	float gravity;
	float maxFallSpeed;

	// Objects
	sf::Vector2f lastPosition;
};

