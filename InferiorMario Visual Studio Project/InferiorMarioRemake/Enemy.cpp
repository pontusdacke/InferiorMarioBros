#include "Enemy.h"

Enemy::Enemy(InputComponent* input, PhysicsComponent* physicsComponent, AnimationComponent* animationComponent, sf::Vector2f& pos)
	: Entity(input, physicsComponent, animationComponent)
{
	// Set the direction and position.
	Direction = false;
	sprite.setPosition(pos);
}
Enemy::~Enemy() { }

// Functions
void Enemy::Initialize(void)
{
	// Initialize the animation component and pass in the spritesheet
	animation->Initialize(*this, "spritesheet.png");
}
void Enemy::Update(Camera& camera, Level& level, sf::RenderWindow& window)
{
	// Dont update the enemy if it is outside the camera. 
	// This is not great, but it prevents enemies to fall outside of the map when they are outside of the screen.
	sf::IntRect bounds(camera.GetTileBounds(window, 32));
	if (sprite.getPosition().x > bounds.left*32 - 32 && sprite.getPosition().x < bounds.width*32)
	{
		// Update the enemies components
		input->Update(*this);
		physics->Update(*this, level, camera, window);
		animation->Update(*this);
	}
}