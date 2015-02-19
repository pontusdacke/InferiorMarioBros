#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"

class UI
{

public:
	// Constructors & Destructors
	UI(void);
	UI(const std::string& fontPath);
	~UI(void);

	// Functions
	void Update(float gameTime, const Player& player);
	void Draw(sf::RenderWindow& window);
private:
	// Objects
	sf::Font font;
	sf::Text text;
	sf::Vector2f offset;

	// Variables
	std::string name;
	int score;
	int coins;
	int world;
	int time;

	// Functions
	void DrawString(int x, int y, const std::string& value, sf::RenderWindow& window);
};

