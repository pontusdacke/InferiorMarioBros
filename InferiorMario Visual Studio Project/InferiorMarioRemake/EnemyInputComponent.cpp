#include "EnemyInputComponent.h"
#include "Enemy.h"

EnemyInputComponent::EnemyInputComponent(float walkAcceleration)
	: InputComponent(walkAcceleration, 18) { }
EnemyInputComponent::~EnemyInputComponent(void) { }

void EnemyInputComponent::Update(Entity& entity)
{
	Enemy* enemy = dynamic_cast<Enemy*>(&entity);
	if (!enemy) return; // Couldn't cast enemy

	// Gravity
	enemy->velocity.y = getJumpAcceleration();

	// Movement
	if (enemy->Direction)
		enemy->velocity.x = getWalkAcceleration();
	else
		enemy->velocity.x = -getWalkAcceleration();

}