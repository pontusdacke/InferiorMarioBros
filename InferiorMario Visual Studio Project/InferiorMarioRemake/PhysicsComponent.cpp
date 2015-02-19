#include "PhysicsComponent.h"
#include "Player.h"

PhysicsComponent::PhysicsComponent(void)
	: gravity(1.0f),
	maxFallSpeed(16.0f) 
{
}
PhysicsComponent::~PhysicsComponent(void) { }

void PhysicsComponent::Update(Entity& entity, Level& level, Camera& camera, sf::RenderWindow& window)
{
	// Update entity gravity 
	if(entity.IsInAir() || entity.velocity.y < 0)
	{
		entity.velocity.y += gravity; // Increase fallspeed
		if(entity.velocity.y > maxFallSpeed) // Check that the entity does not exceed max fallspeed
			entity.velocity.y = maxFallSpeed; 
	} 
	else
	{
		entity.velocity.y = 0; // Not in air -> we are on ground -> no velocity
	}

	// Store last position
	lastPosition = sf::Vector2f(entity.getPosition().x, entity.getPosition().y);

	// Move the entity in Y-Axis
	entity.Move(0, entity.velocity.y);
	if(Collision(window, level, camera, entity, collisionRectangle, collisionTile))
	{
		CollisionResponseYAxis(entity, camera, level);
	}
	
	// Move the entity in X-Axis
	entity.Move(entity.velocity.x, 0);
	if(Collision(window, level, camera, entity, collisionRectangle, collisionTile))
	{
		CollisionResponseXAxis(entity, camera, level);
	}
}
void PhysicsComponent::CollisionResponseXAxis(Entity& entity, Camera& camera, Level& level)
{
	// Check where the entity is in relation to the tile we collided with and 
	// position the entity on the correct side
	if (entity.getPosition().x < collisionRectangle.left)
		entity.sprite.setPosition(collisionRectangle.left - 33, entity.getPosition().y);
	else if (entity.getPosition().x >= collisionRectangle.left)
		entity.sprite.setPosition(collisionRectangle.width + 1, entity.getPosition().y);
}
void PhysicsComponent::CollisionResponseYAxis(Entity& entity, Camera& camera, Level& level)
{
	// Reset position
	entity.Idle();
	entity.velocity.y = 0;
	if (entity.getPosition().y < collisionRectangle.top)
	{
		entity.sprite.setPosition(entity.getPosition().x, collisionRectangle.top - 33);
	}
	else if (entity.getPosition().y > collisionRectangle.top)
	{
		entity.sprite.setPosition(entity.getPosition().x, collisionRectangle.height + 1);
	}
}
void PhysicsComponent::CollisionResponseObject(Entity& entity, Camera &camera, Level &level)
{
	// Nothing here yet :D
}