#include "PlayerGoalInputComponent.h"
#include "Player.h"

PlayerGoalInputComponent::PlayerGoalInputComponent(void)
	: InputComponent(6.0f, 12.0f)
{
}


PlayerGoalInputComponent::~PlayerGoalInputComponent(void)
{
}

void PlayerGoalInputComponent::Update(Entity& entity)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if (!player) return; // Couldn't cast entity to player
	
	if (player->isJumping)
	{
		player->velocity.x = 0;
		player->sprite.setPosition(player->sprite.getPosition().x, player->sprite.getPosition().y + 5);
	}
	else
	{
		if (player->getPosition().x > 6496)
		{
			player->Hide();
			player->velocity.x = 0;
		}
		else
			player->velocity.x = getWalkAcceleration(); 
	}
}
