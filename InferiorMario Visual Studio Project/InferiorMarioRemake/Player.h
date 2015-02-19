#pragma once
#include "Entity.h"

// Includes needed for collision
#include "Camera.h" 
#include "Level.h"

class Player : 
	public Entity
{
public:
	// Constructors & Destructors
	Player(InputComponent* inputComponent, PhysicsComponent* physicsComponent, AnimationComponent* animationComponent);
	~Player(void);

	// Variables
	bool canJump;
	bool isJumping;

	// Getters and Setters
	int GetScore(void) const;
	int GetCoins(void) const;
	
	// Functions
	virtual void Initialize(void);
	virtual void Update(Camera& camera, Level& level, sf::RenderWindow& window);
	void ChangeInputComponent(InputComponent* component);
	void Pause(void);
	void UnPause(void);
	void AddScore(int x);
	void AddCoins(int x);
private:
	// Objects
	sf::Vector2f temporaryPosition; // Variable to store position when pausing

	// Variables
	int score;
	int coins;
	bool hasWon; // Has the player reached its goal?
};