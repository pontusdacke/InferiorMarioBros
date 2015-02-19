#pragma once
#include <SFML\Graphics.hpp>

//Components
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

class Entity
{
protected:
	// Variables
	bool visible;	// Should the entity be drawn?
	bool inAir;		// Is the entity in air?
	
public:
	// Constructors & Destructors
	Entity(void);
	Entity(InputComponent* input, PhysicsComponent* physicsComponent, AnimationComponent* animationComponent);
	virtual ~Entity(void);

	// Components (Pointer to enable different kind of components)
	InputComponent* input; 
	PhysicsComponent* physics;
	AnimationComponent* animation; 

	// Variables
	bool alive;		// Is the entity alive?

	// Objects
	sf::Sprite sprite;				// The sprite
	sf::Vector2f velocity;			// X and Y velocity
	sf::Clock deathTimer;			// Timer that helps when entities dies.
	AnimationState currentState;	// The state of animation

	// Functions
	virtual void Initialize(void);
	virtual void ProcessInput(void);
	virtual void Update(Camera& camera, Level& level, sf::RenderWindow& window);
	virtual void Draw(sf::RenderWindow& window);
	void Move(float x, float y);
	void Hide(void) { visible = false; }
	void Show(void) { visible = true; }
	void Idle(void);
	void Kill(void) { alive = false; deathTimer.restart(); }
	
	// Getters & Setters
	const sf::Vector2f& getPosition(void) const { return sprite.getPosition(); }
	const sf::IntRect& getRect(void) const { return sprite.getTextureRect(); }
	bool IsInAir(void) { return inAir; }
	void setAirState(bool b) { inAir = b; }
	bool IsAlive(void) { return alive; }
	bool IsVisible(void) { return visible; }
};

