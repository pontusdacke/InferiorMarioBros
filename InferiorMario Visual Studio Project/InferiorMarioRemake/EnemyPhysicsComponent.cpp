#include "EnemyPhysicsComponent.h"
#include "Enemy.h"

EnemyPhysicsComponent::EnemyPhysicsComponent(void) { }
EnemyPhysicsComponent::~EnemyPhysicsComponent(void) { }

void EnemyPhysicsComponent::Update(Entity& entity, Level& level, Camera& camera, sf::RenderWindow& window)
{
	Enemy* enemy = dynamic_cast<Enemy*>(&entity);
	if (!enemy) return; // Could'nt cast entity to enemy

	enemy->velocity.y += getGravity();
	if (enemy->velocity.y > getMaxFallSpeed()) 
		enemy->velocity.y = getMaxFallSpeed(); // Max fallspeed


	// Move player in x-axis
	enemy->Move(enemy->velocity.x, 0);
	// Check collision to map
	if (Collision(window, level, camera, *enemy, collisionRectangle, collisionTile))
	{
		CollisionResponseXAxis(*enemy, camera, level); // Resolve X-axis collision
		enemy->Direction = !enemy->Direction;
	}

	// Move player in y-axis
	enemy->Move(0, enemy->velocity.y);
	// Check collision to map
	if (Collision(window, level, camera, *enemy, collisionRectangle, collisionTile))
	{
		CollisionResponseYAxis(*enemy, camera, level); // Resolve Y-axis collision
	}

	// Check collision on objects
	if (ObjectCollision(window, level, camera, *enemy, collisionObject))
	{
		CollisionResponseObject(*enemy, camera, level);
	}

}
void EnemyPhysicsComponent::CollisionResponseObject(Entity& entity, Camera &camera, Level &level)
{
	Enemy* enemy = dynamic_cast<Enemy*>(&entity);
	if (!enemy) return; // Couldn't cast entity to enemy

	if (enemy->velocity.y > 0) enemy->Direction = !enemy->Direction;
}
