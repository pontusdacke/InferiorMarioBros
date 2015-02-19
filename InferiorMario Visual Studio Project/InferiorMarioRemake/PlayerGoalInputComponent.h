#pragma once
#include "inputcomponent.h"
class PlayerGoalInputComponent :
	public InputComponent
{
public:
	// Constructors & Destructors
	PlayerGoalInputComponent(void);
	~PlayerGoalInputComponent(void);

	// Functions
	virtual void Update(Entity& entity);
};

