#include "InputComponent.h"
#include "Entity.h"

InputComponent::InputComponent(float walkAcceleration, float jumpAcceleration)
	: walk_acceleration(walkAcceleration),
	jump_acceleration(jumpAcceleration)
{ }
InputComponent::~InputComponent(void) { }

void InputComponent::Update(Entity& entity)
{
	// Read input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		entity.velocity.x = walk_acceleration;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		entity.velocity.x = -walk_acceleration;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		entity.velocity.y = -walk_acceleration;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		entity.velocity.y = walk_acceleration;
	
	else // StopMove
	{
		// Slow down instead of instant stop
		// X-axis
		if(entity.velocity.x > 0)
			entity.velocity.x -= 0.6f;
		else if (entity.velocity.x < 0)
			entity.velocity.x += 0.6f;
		// Y-axis
		if(entity.velocity.y > 0)
			entity.velocity.y -= 0.6f;
		else if (entity.velocity.y < 0)
			entity.velocity.y += 0.6f;

		// Prevent velocity from flipping over and below 0 causing continuous movement when idle
		if (entity.velocity.x > -0.3 && entity.velocity.x < 0.3) // X-axis
			entity.velocity.x = 0;
		if (entity.velocity.y > -0.3 && entity.velocity.y < 0.3) // Y-axis
			entity.velocity.y = 0;
	}
}
