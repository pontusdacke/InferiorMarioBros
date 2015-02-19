#pragma once
#include <SFML\Graphics.hpp>

class Menu
{

public:
	// Constructors & Destructors
	Menu(void);
	~Menu(void);

	// Functions
	void MoveMarkerUp(void);
	void MoveMarkerDown(void);
	void Exit(sf::RenderWindow& window);
	void Pause(void) { startGame = false; }
	void Resume(void) { startGame = true; }
	void MainLoop(sf::RenderWindow& window);
	void Initialize(const std::string& backgroundPath, const std::string& markerPath, const std::string& fontPath);
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	// Getters & Setters
	bool GetStartGame(sf::RenderWindow& window);

private:
	// Objects
	std::string play;
	std::string exit;
	sf::Font font;
	sf::Text tPlay;
	sf::Text tExit;
	sf::Sprite background;
	sf::Sprite marker;
	sf::Texture backgroundTexture;
	sf::Texture markerTexture;

	// Variabels
	int option;
	bool keyPressed;
	bool startGame;
};

