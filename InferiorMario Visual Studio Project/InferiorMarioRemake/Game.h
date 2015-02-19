#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Camera.h"
#include "Level.h"
#include "UI.h"
#include "Menu.h"

#include "Player.h"
#include "PlayerAnimationComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"

#include "Enemy.h"
#include "EnemyAnimationComponent.h"
#include "EnemyInputComponent.h";
#include "EnemyPhysicsComponent.h";

/* Game process:
 * 1. Initialize window and other components
 * 2. Start the main loop
 * 3. Handle input
 * 4. Update logic
 * 5. Render a frame
 * 6. Display frame
 * 7. Goto 3 ☺
 */

class Game
{
public:
	Game(int width, int height, int tileSize);
	~Game(void);
	void Start(void);
	void Restart(void);
private:
	void MainLoop(void);
	bool Initialize(void);
	void HandleEvents(void);
	void Update(void);
	void Draw(void);
	void Pause(void);
		
	// Objects & Pointers
	Camera camera;
	TextureHandler textureHandler;
	Level level;
	Player player;
	UI* ui;
	Menu* menu;
	sf::RenderWindow* window;
	sf::Clock gameTime;
	sf::Vector2i videoSize;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::SoundBuffer buffer, gameOverBuffer, gameWonBuffer;
	sf::Sound gameOver, gameWon;
	sf::Music gameMusic;

	// Variables
	int tileSize;
	bool gameInitialized;
	bool gameFinished;
};