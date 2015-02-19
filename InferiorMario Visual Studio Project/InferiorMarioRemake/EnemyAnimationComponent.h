#pragma once
#include "AnimationComponent.h"

class EnemyAnimationComponent :
	public AnimationComponent
{
public:
	// Constructors & Destructors
	EnemyAnimationComponent(void);
	virtual ~EnemyAnimationComponent(void);

	// Functions
	virtual void Initialize(Entity& entity, const std::string& filePath);
	virtual void Update(Entity& entity);
private:
	// Animationdata
	sf::IntRect moveFrame1;
	sf::IntRect moveFrame2;
	sf::IntRect killFrame1;

	// Variables
	bool deathAnimation;

	// Objects
	sf::Clock deathClock;
};

