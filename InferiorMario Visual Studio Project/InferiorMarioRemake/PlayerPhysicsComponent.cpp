#include "PlayerPhysicsComponent.h"
#include "PlayerGoalInputComponent.h"
#include "Player.h"
#include "Enemy.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(void)
{
	kickBuffer.loadFromFile("smb_kick.wav");
	kickSound.setBuffer(kickBuffer);
	bumpBuffer.loadFromFile("smb_bump.wav");
	bumpSound.setBuffer(bumpBuffer);
} 
PlayerPhysicsComponent::~PlayerPhysicsComponent(void) { }

void PlayerPhysicsComponent::Update(Entity& entity, Level& level, Camera& camera, sf::RenderWindow& window)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if(!player) return; // Couldn't cast entity to player

	// Update player gravity 
	if (jumpClock.getElapsedTime().asMilliseconds() > 300)
	{
		player->isJumping = false;
	}
	if (player->IsInAir() || player->velocity.y < 0)
	{
		player->velocity.y += getGravity();
		if(player->velocity.y > getMaxFallSpeed()) 
			player->velocity.y = getMaxFallSpeed(); // Max fallspeed
	} 
	else
	{
		player->velocity.y = 0;
	}
	
	// Move player in x-axis
	player->Move(player->velocity.x, 0);
	// Check collision if we are alive
	if (player->IsAlive())
		if (Collision(window, level, camera, *player, collisionRectangle, collisionTile))
		{
			CollisionResponseXAxis(*player, camera, level); // Resolve X-axis collision
		}

	// Move player in y-axis
	player->Move(0, player->velocity.y);
	// Check collision
	if (player->IsAlive())
		if (Collision(window, level, camera, *player, collisionRectangle, collisionTile))
		{
			CollisionResponseYAxis(*player, camera, level); // Resolve Y-axis collision
		}

	// Check collision against objects ( enemies and such )
	if (player->IsAlive())
		if (ObjectCollision(window, level, camera, *player, collisionObject))
		{
			CollisionResponseObject(*player, camera, level);
		}

	// Check that the player doesent exit the map in x-axis
	if (player->getPosition().x < 0) player->sprite.setPosition(0, player->getPosition().y);
	
	// Check if player has crossed goal line
	if (player->getPosition().x > 6304) //6304 is the x coordinat of the flag
	{
		player->ChangeInputComponent(new PlayerGoalInputComponent());
	}

	// Kill player if fall below map
	if (player->getPosition().y > 460) player->Kill();
}
void PlayerPhysicsComponent::CollisionResponseYAxis(Entity& entity, Camera& camera, Level& level)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if(!player) return; // if the entity was no player.. ABORT MISSION!

	if (player->getPosition().y < collisionRectangle.top) // Hitting a block from above
	{
		player->sprite.setPosition(player->getPosition().x, collisionRectangle.top - 33);
		player->velocity.y = 0;
		player->Idle();
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			jumpClock.restart();
			player->canJump = true;
		}
	}
	else if (player->getPosition().y > collisionRectangle.top) // Hitting a block from below
	{
		player->sprite.setPosition(player->getPosition().x, collisionRectangle.height + 1);
		player->velocity.y = 0;
		player->isJumping = false;

		CollisionTile *t;
			
		if (entity.getPosition().x < collisionRectangle.left + 16)
			t = level.GetTile(collisionTile.x, collisionTile.y);
		else if (entity.getPosition().x >= collisionRectangle.left + 16)
			t = level.GetTile(collisionTile.x + 1, collisionTile.y);

		if(t->GetWalkable()) t = level.GetTile(collisionTile.x, collisionTile.y);

		if(t)
		{
			t->Hit(entity, level);
			bumpSound.play();
		}
	}	
}
void PlayerPhysicsComponent::CollisionResponseObject(Entity& entity, Camera &camera, Level &level)
{
	Player* player = dynamic_cast<Player*>(&entity);
	if (!player) return; // Couldn't cast entity to player

	if (player->velocity.y > 0) // We have collided with an object while in air
	{
		// Object is an enemy since we have no other objects now.
		kickSound.play(); 
		player->AddScore(100);
		player->velocity.y = -10;
		level.GetEnemy(collisionObject)->Kill();
	}
	else if (player->velocity.y == 0)
	{
		player->Kill();
		player->velocity.y = 0;
		player->velocity.x = 0;
	}
}