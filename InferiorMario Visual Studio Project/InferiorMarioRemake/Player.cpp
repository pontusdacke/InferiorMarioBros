#include "Player.h"

// Initialize the player with the components needed, and set default values to variables
Player::Player(InputComponent* inputComponent, PhysicsComponent* physicsComponent, AnimationComponent* animationComponent)
	: Entity(inputComponent, physicsComponent, animationComponent), 
	  isJumping(false),
	  canJump(true),
	  hasWon(false),
	  score(0),
	  coins(0)
{ }
// Empty destructor. Memory handled in baseclass
Player::~Player(void) { }

// Getters & Setters
int Player::GetScore(void) const { return score; }	// Return value of score
void Player::AddScore(int x) { score += x; }		// Add x to score
int Player::GetCoins(void) const { return coins; }	// Return value of Coins
void Player::AddCoins(int x)						// Add coins and 100 score for each coin
{
	coins += x;
	AddScore(100 * x);
}
// End of Getters & Setters

void Player::Initialize(void)
{
	isJumping = false;
	canJump = true;
	hasWon = false;
	score = 0;
	coins = 0;
	alive = true;
	visible = true; 
	// Tell the animation component which spritesheet to use
	animation->Initialize(*this, "spritesheet.png"); 
}
void Player::Pause(void)
{
	temporaryPosition = sprite.getPosition();
	sprite.setPosition(0, 0);
}
void Player::UnPause(void)
{
	sprite.setPosition(temporaryPosition);
}
void Player::Update(Camera& camera, Level& level, sf::RenderWindow& window)
{
	temporaryPosition = getPosition();

	// Update components
	if (IsAlive())
		input->Update(*this); // Update input logic
	physics->Update(*this, level, camera, window); // Update physics (movement, gravity)
	animation->Update(*this); // Update animation ( does NOT draw player )
	
	if (deathTimer.getElapsedTime().asMilliseconds() < 700)
	{
		sprite.setPosition(temporaryPosition);
	}
	else if (!IsAlive())
	{
		velocity.y = -9; // Rocket into the air
	}
}
/* This function is used to switch the input component for the player.
 * It enables us to change the controlls to AI when needed.
 * Ex: When player has reached goal, he is no longer in control of the character, 
 * and the player walks to the castle with AI.
 */
void Player::ChangeInputComponent(InputComponent* component)
{
	if(input) delete input; // Delete our previous component
	input = component; // Install the new component
}
