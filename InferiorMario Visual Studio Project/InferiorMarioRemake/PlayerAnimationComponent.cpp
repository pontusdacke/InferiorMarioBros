#include "PlayerAnimationComponent.h"
#include "Player.h"

PlayerAnimationComponent::PlayerAnimationComponent(void) : deathAnimation(false) { }
PlayerAnimationComponent::~PlayerAnimationComponent(void) { }

void PlayerAnimationComponent::Initialize(Entity& entity, const std::string& filePath)
{
	// Load animation data (Move to XML file when you got time)
	idleLeftFrame1 = sf::IntRect(0, 0, 32, 32);
	idleRightFrame1 = sf::IntRect(128, 0, 32, 32);
	moveLeftFrame1 = sf::IntRect(32, 0, 32, 32);
	moveLeftFrame2 = sf::IntRect(64, 0, 32, 32);
	moveRightFrame1 = sf::IntRect(160, 0, 32, 32);
	moveRightFrame2 = sf::IntRect(192, 0, 32, 32);
	jumpLeftFrame1 = sf::IntRect(0, 32, 32, 32);
	jumpRightFrame1 = sf::IntRect(32, 32, 32, 32);
	breakLeftFrame1 = sf::IntRect(96, 0, 32, 32);
	breakRightFrame1 = sf::IntRect(224, 0, 32, 32);
	killFrame1 = sf::IntRect(64, 32, 32, 32);

	if(!getTexture().loadFromFile(filePath))
	{
		// This shouldnt happend, so we want to terminate program if it does.
		throw "Couldn't load the texture :("; 
	}

	// Initialize the sprite
	Player* player = dynamic_cast<Player*>(&entity);
	player->sprite.setTexture(getTexture());
	player->sprite.setPosition(350, 96);
	player->sprite.setTextureRect(idleRightFrame1);
}
void PlayerAnimationComponent::Update(Entity& entity)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if (!player) return; // Couldn't cast entity to player

	// Switch between animations depending on what the player does.
	if (entity.velocity.y > 0 || entity.velocity.y < 0)
	{
		if (player->currentState == AnimationState::moveLeft || player->currentState == AnimationState::idleLeft)
			player->currentState = AnimationState::jumpLeft;
		else if (player->currentState == AnimationState::moveRight || player->currentState == AnimationState::idleRight)
			player->currentState = AnimationState::jumpRight;
	}
	else if	(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player->currentState = AnimationState::moveRight;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player->currentState = AnimationState::moveLeft;
	else if	(entity.velocity.x > 0) player->currentState = AnimationState::breakRight;
	else if (entity.velocity.x < 0) player->currentState = AnimationState::breakLeft;
	else if	(entity.velocity.x == 0) entity.Idle();
	

	// Update animation data when clock ticks above interval
	if (player->IsAlive() && getMilliseconds() > getInterval())
	{
		// Change texture rectangle
		SetRectangle(entity);
		// Restart the animation timer
		RestartTimer();
	}
	// Check if enemy is dead and animate accordingly.
	if(!player->IsAlive())
	{
		player->sprite.setTextureRect(killFrame1);

		if (!deathAnimation) 
		{
			deathClock.restart();
			deathAnimation = true;
		}
	}
}
void PlayerAnimationComponent::SetRectangle(Entity& entity)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if (!player) return; // Couldn't cast entity to player

	switch(player->currentState) // Different animations for different states
	{
		case AnimationState::idleLeft:
			player->sprite.setTextureRect(idleLeftFrame1);
			break;
		case AnimationState::idleRight:
			player->sprite.setTextureRect(idleRightFrame1);
			break;
		case AnimationState::moveLeft:
			// Toggle between the two frames #Note to self: Animation frame counter. This is stupid
			if(player->sprite.getTextureRect() == moveLeftFrame1) 
				player->sprite.setTextureRect(moveLeftFrame2);
			else
				player->sprite.setTextureRect(moveLeftFrame1);
			break;
		case AnimationState::moveRight:
			// Toggle between the two frames #Note to self: Animation frame counter. This is stupid
			if(player->sprite.getTextureRect() == moveRightFrame1)
				player->sprite.setTextureRect(moveRightFrame2);
			else
				player->sprite.setTextureRect(moveRightFrame1);
			break;
		case AnimationState::jumpLeft:
			player->sprite.setTextureRect(jumpLeftFrame1);
			break;
		case AnimationState::jumpRight:
			player->sprite.setTextureRect(jumpRightFrame1);
			break;
		case AnimationState::breakLeft:
			player->sprite.setTextureRect(breakLeftFrame1);
			break;
		case AnimationState::breakRight:
			player->sprite.setTextureRect(breakRightFrame1);
			break;
	}
}
