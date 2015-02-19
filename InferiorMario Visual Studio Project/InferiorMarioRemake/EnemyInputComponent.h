#pragma once
#include "InputComponent.h"

class EnemyInputComponent :
	public InputComponent
{
public:
	// Constructors & Destructors
	EnemyInputComponent(float walkAcceleration);
	~EnemyInputComponent(void);

	// Functions
	virtual void Update(Entity& entity);
};

