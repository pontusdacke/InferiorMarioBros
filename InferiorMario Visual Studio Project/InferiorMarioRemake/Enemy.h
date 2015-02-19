#pragma once
#include "Entity.h"

// Includes needed for collision
#include "Camera.h" 
#include "Level.h"

class Enemy : 
	public Entity
{
public:
	// Constructors & Destructors
	Enemy(InputComponent* input, PhysicsComponent* physicsComponent, AnimationComponent* animationComponent, sf::Vector2f& pos);
	~Enemy(void);

	// Functions
	virtual void Update(Camera& camera, Level& level, sf::RenderWindow& window);
	virtual void Initialize(void);

	// Variabels
	bool Direction; // TRUE is RIGHT & FALSE is LEFT
};

