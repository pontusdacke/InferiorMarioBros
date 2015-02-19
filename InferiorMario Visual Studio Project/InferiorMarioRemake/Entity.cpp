#include "Entity.h"

Entity::Entity(void)
	: velocity(0, 0),
	visible(true)
{
	// Initialize the standard components
	input = new InputComponent(0.0f, 0.0f);
	physics = new PhysicsComponent();
	animation = new AnimationComponent();

	alive = true;
}
Entity::Entity(InputComponent* inputComponent, PhysicsComponent* physicsComponent, AnimationComponent* animationComponent)
	: velocity(0, 0),
	  inAir(true),
	  visible(true),
	  currentState(AnimationState::idleRight)
{
	// Initialize the custom components
	input = inputComponent;
	physics = physicsComponent;
	animation = animationComponent;

	alive = true;
}
Entity::~Entity(void)
{
	// Destroy the dynamic memory through their pointers
	delete input;
	delete physics;
	delete animation;
}
void Entity::Move(float x, float y)
{
	sprite.move(x, y);
}
void Entity::Initialize(void) { }
void Entity::ProcessInput(void) { }
void Entity::Update(Camera& camera, Level& level, sf::RenderWindow& window)
{
	// Update Components
	input->Update(*this);
	physics->Update(*this, level, camera, window);
	animation->Update(*this);
}
void Entity::Draw(sf::RenderWindow& window)
{
	// Draw sprite to window, if visible.
	if (visible)
		window.draw(sprite);
}
void Entity::Idle(void)
{
	// Set the animationstate to the currect idle state.
	if (currentState == AnimationState::jumpLeft || currentState == AnimationState::breakLeft) currentState = AnimationState::idleLeft;
	else if (currentState == AnimationState::jumpRight || currentState == AnimationState::breakRight) currentState = AnimationState::idleRight;
}