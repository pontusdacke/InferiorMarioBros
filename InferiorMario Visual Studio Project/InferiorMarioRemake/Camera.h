#pragma once
#include <SFML\Graphics.hpp>

class Camera
{
private:
	// Objects and classes
	sf::View view;

public:
	// Constructors & Destructors
	Camera(void);
	~Camera(void);

	// Functions
	void Zoom(float f, sf::RenderWindow& window);
	void Rotate(float f, sf::RenderWindow& window);

	// Getters & Setters
	void SetView(sf::RenderWindow& window);
	void SetCenter(sf::RenderWindow& window, const sf::Vector2f& center);
	const sf::Vector2f& GetCenter(void) const;
	sf::IntRect GetTileBounds(sf::RenderWindow& window, int tileSize) const;
	
};

