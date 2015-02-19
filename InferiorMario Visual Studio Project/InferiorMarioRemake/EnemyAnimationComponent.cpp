#include "EnemyAnimationComponent.h"
#include "Enemy.h"

EnemyAnimationComponent::EnemyAnimationComponent(void) 
{
	deathAnimation = false;
}
EnemyAnimationComponent::~EnemyAnimationComponent(void) { }

void EnemyAnimationComponent::Initialize(Entity& entity, const std::string& filePath)
{
	// Initialize frames by settings values from the position in the spritesheet
	moveFrame1 = sf::IntRect(128, 64, 32, 32); 
	moveFrame2 = sf::IntRect(160, 64, 32, 32);  
	killFrame1 = sf::IntRect(192, 64, 32, 32);

	// Load spritesheet
	if(!getTexture().loadFromFile(filePath))
	{
		// This shouldnt happend, so we want to terminate program if it does.
		throw "Couldn't load the texture :("; 
	}

	// Initialize the sprite
	Enemy* enemy = dynamic_cast<Enemy*>(&entity);
	enemy->sprite.setTexture(getTexture());
	enemy->sprite.setTextureRect(moveFrame1);
}
void EnemyAnimationComponent::Update(Entity& entity)
{
	Enemy* enemy = dynamic_cast<Enemy*>(&entity);
	if (!enemy) return; // Couldn't cast entity to enemy

	// Animate enemy
	if (enemy->IsAlive() && getMilliseconds() > 300 )
	{
		animationClock.restart();
		if (enemy->sprite.getTextureRect() == moveFrame1)
			enemy->sprite.setTextureRect(moveFrame2);
		else
			enemy->sprite.setTextureRect(moveFrame1);
	}
	// Check if enemy is dead and animate accordingly.
	if(!enemy->IsAlive())
	{
		enemy->sprite.setTextureRect(killFrame1);

		if (!deathAnimation) 
		{
			deathClock.restart();
			deathAnimation = true;
		}
	}
	if (deathAnimation && deathClock.getElapsedTime().asMilliseconds() > 250)
	{
		if (enemy)
			enemy->Hide();
	}
}
