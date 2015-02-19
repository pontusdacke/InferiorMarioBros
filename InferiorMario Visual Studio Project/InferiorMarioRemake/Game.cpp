#include "Game.h"


Game::Game(int width, int height, int tileSize)
	: videoSize(width, height),
	player(new PlayerInputComponent(6.0f, 12.0f), new PlayerPhysicsComponent(), new PlayerAnimationComponent())
{
	textureHandler.SetTileSize(tileSize);
}


Game::~Game(void)
{
	if (gameInitialized)
	{
		delete window;
		delete menu;
		delete ui;
	}
}
void Game::Start(void)
{
	if(!Initialize())
		throw "Game Initialization Failed";
	
	MainLoop();
}
void Game::Restart(void)
{
	/* Unfinished and very buggy.
	 * Do not use
	 */
	delete ui;
	ui = new UI("SuperMarioBros.ttf");

	player.Initialize();

	gameFinished = false;
	gameTime.restart();
	player.sprite.setPosition(0, 0);
	gameMusic.play();
	level.LoadLevel("Level1-1.xml", textureHandler);
}
void Game::MainLoop(void)
{
	gameMusic.play(); // Play the mario bros song, yo!

	while(window->isOpen()) // Standard loop. 
	{
		menu->MainLoop(*window); // Display and update menu
		
		gameTime.restart(); // Make sure the timer starts at 0
		while(menu->GetStartGame(*window)) // If we started game from the menu
		{
			HandleEvents(); // Handle events
			Update();		// Update game logic
			Draw();			// Render a frame
		}
	}
}
bool Game::Initialize(void)
{
	// Window initialization
	window = new sf::RenderWindow(sf::VideoMode(videoSize.x, videoSize.y, tileSize), "Inferior Mario");
	if(!window) return false;
	window->setFramerateLimit(30);

	// Camera initialization
	camera.SetView(*window);

	// Menu initialization
	menu = new Menu();
	menu->Initialize("menu.png", "marker.png", "SuperMarioBros.ttf");

	// Level initialization
	level.LoadLevel("Level1-1.xml", textureHandler);

	// Player initialization
	player.Initialize();

	// UI initialization
	ui = new UI("SuperMarioBros.ttf");

	// Sound initialization
	gameMusic.openFromFile("smb1-1.wav");
	gameOverBuffer.loadFromFile("smb_mariodie.wav");
	gameOver.setBuffer(gameOverBuffer);
	gameWonBuffer.loadFromFile("smb_stage_clear.wav");
	gameWon.setBuffer(gameWonBuffer);

	gameFinished = false;
	gameInitialized = true;
	return true;
}
void Game::HandleEvents(void)
{
	// Standard event loop
	sf::Event evt;
	while(window->pollEvent(evt)) // Poll event from the OS event queue
	{
		switch(evt.type) // Act upon the event type.
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				Pause();	
			}
			break;
		}
	}
}
void Game::Update(void)
{
	if (player.IsAlive() && player.IsVisible())
	{
		level.UpdateEnemies(*window, camera); // Update level ( And anything level related )
		ui->Update((float)(999 - (gameTime.getElapsedTime().asMilliseconds() / 200)), player); // Update UI
	}
	else if (!player.IsAlive() || !player.IsVisible()) // Win or lose conditions
	{
		if (!gameFinished)
		{
			gameMusic.stop();
			if (!player.IsAlive())
				gameOver.play();
			else
				gameWon.play();
			player.AddScore(999 - gameTime.getElapsedTime().asMilliseconds() / 200);
		}
		//else if (gameOver.getStatus() == gameOver.Stopped) 
		//{ 
		//	menu->Pause();
		//	Restart();
		//}
		gameFinished = true;
	}

	player.Update(camera, level, *window); // Update Player
	camera.SetCenter(*window, sf::Vector2f(player.getPosition().x, window->getSize().y / 2)); // Update camera

	// Playing with camera settings. Q and W for rotate
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		camera.Zoom(1.03f, *window);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		camera.Zoom(0.97f, *window);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		camera.Rotate(1.0f, *window);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		camera.Rotate(-1.0f, *window);
}
void Game::Draw(void)
{
	window->clear(); // Clear the windowbuffer

	// Start drawing here
	window->draw(sprite);
	level.Draw(*window, camera);
	level.DrawEnemies(*window, camera);
	player.Draw(*window);
	ui->Draw(*window);
	// Stop drawing here

	window->display(); // Display the newly drawn buffer
}
void Game::Pause(void)
{
	menu->Pause();
	player.Pause();
}
