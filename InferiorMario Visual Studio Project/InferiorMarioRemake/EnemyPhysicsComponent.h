#pragma once
#include "physicscomponent.h"
class EnemyPhysicsComponent :
	public PhysicsComponent
{
public:
	// Constructors & Destructors
	EnemyPhysicsComponent(void);
	~EnemyPhysicsComponent(void);

	// Functions
	virtual void Update(Entity& entity, Level& level, Camera& camera, sf::RenderWindow& window);
	virtual void CollisionResponseObject(Entity& entity, Camera &camera, Level &level);
};

