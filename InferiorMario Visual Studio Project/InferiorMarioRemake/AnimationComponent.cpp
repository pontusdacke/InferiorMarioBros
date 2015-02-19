#include "AnimationComponent.h"
#include "Entity.h"

AnimationComponent::AnimationComponent(void)
	: interval(60),
	  currentFrame(0)
{
}
AnimationComponent::~AnimationComponent(void) { }

void AnimationComponent::Initialize(Entity& entity, const std::string& filePath)
{
	if(!texture.loadFromFile(filePath))
	{
		// This shouldnt happend, so we want to terminate program if it does.
		throw "Couldn't load the texture :("; 
	}
	// Initialize the sprite
	entity.sprite.setTexture(texture);
}
void AnimationComponent::Update(Entity& entity)
{
	// Update animation data when clock ticks above interval
	if (animationClock.getElapsedTime().asMilliseconds() > interval)
	{
		// Restart the animation clock
		animationClock.restart();
	}
}