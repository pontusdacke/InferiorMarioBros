#pragma once
#include <SFML\Graphics.hpp>

// Preventing Circular dependecy
class Entity;

class InputComponent
{
public:
	// Constructors & Deconstructors
	InputComponent(float walkAcceleration, float jumpAcceleration);
	virtual ~InputComponent(void);

	// Functions
	virtual void Update(Entity& entity);

	// Getters & Setters
	float getWalkAcceleration(void) const { return walk_acceleration; }
	float getJumpAcceleration(void) const { return jump_acceleration; }

private:
	// Variables
	float walk_acceleration;
	float jump_acceleration;
};

