#pragma once
#include "AnimationComponent.h"

class PlayerAnimationComponent :
	public AnimationComponent
{
public:
	// Constructors & Destructors
	PlayerAnimationComponent(void);
	virtual ~PlayerAnimationComponent(void);

	// Functions
	virtual void Initialize(Entity& entity, const std::string& filePath);
	virtual void Update(Entity& entity);
private:
	// Animation data. NOTE TO SELF: Move to file
	sf::IntRect idleLeftFrame1;
	sf::IntRect idleRightFrame1;
	sf::IntRect moveLeftFrame1;
	sf::IntRect moveLeftFrame2;
	sf::IntRect moveRightFrame1;
	sf::IntRect moveRightFrame2;
	sf::IntRect jumpLeftFrame1;
	sf::IntRect jumpRightFrame1;
	sf::IntRect breakLeftFrame1;
	sf::IntRect breakRightFrame1;
	sf::IntRect killFrame1;

	// Functions
	void SetRectangle(Entity& entity);

	// Objects
	sf::Clock deathClock;

	// Variables
	bool deathAnimation;
};

