#include "PlayerInputComponent.h"
#include "Player.h"


PlayerInputComponent::PlayerInputComponent(float walkAcceleration, float jumpAcceleration)
	: InputComponent(walkAcceleration, jumpAcceleration)
{
	buffer.loadFromFile("smb_jump-small.wav");
	jumpSound.setBuffer(buffer);
}
PlayerInputComponent::~PlayerInputComponent(void) { }

void PlayerInputComponent::Update(Entity& entity)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if (!player) return; // Couldn't cast entity to player

	// Slow down instead of instant stop
	if(player->velocity.x > 0)
		player->velocity.x -= 1.0f;
	
	else if (player->velocity.x < 0)
		player->velocity.x += 1.0f;
	
	// Prevent velocity from flipping over and below 0 causing continuous movement when idle
	if (player->velocity.x > -0.1 && player->velocity.x < 0.1) 
		player->velocity.x = 0;

	// Read input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Move right
	{
		player->velocity.x = getWalkAcceleration(); 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Move right
	{
		player->velocity.x = -getWalkAcceleration(); 
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Jump
	{
		if(player->canJump && !player->isJumping)
		{
			jumpSound.play();
			player->setAirState(true);
			player->isJumping = true;
			player->canJump = false;
		}
		if(player->isJumping)
		{
			player->velocity.y = -getJumpAcceleration();
		}
	}
}
