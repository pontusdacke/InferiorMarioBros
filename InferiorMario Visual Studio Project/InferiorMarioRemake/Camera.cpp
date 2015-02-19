#include "Camera.h"


Camera::Camera(void)
	: view(sf::FloatRect(0, 0, 600, 480)) { }
Camera::~Camera(void) { }
void Camera::Zoom(float f, sf::RenderWindow& window)
{
	view.zoom(f); // Set view zoom
	SetView(window); // Refresh view
}
void Camera::Rotate(float f, sf::RenderWindow& window)
{
	view.rotate(f);
	SetView(window);
}

// Getters & Setters
void Camera::SetView(sf::RenderWindow& window)
{
	window.setView(view);
}
const sf::Vector2f& Camera::GetCenter(void) const
{
	return view.getCenter();
}
sf::IntRect Camera::GetTileBounds(sf::RenderWindow& window, int tileSize) const
{
	int x = static_cast<int>((GetCenter().x - window.getSize().x / 2) / tileSize);
	int y = static_cast<int>((GetCenter().y - window.getSize().y / 2) / tileSize);

	int w = static_cast<int>(x + window.getSize().x / tileSize + 2);
	int h = static_cast<int>(y + window.getSize().y / tileSize);

	return sf::IntRect(x, y, w, h);
}
void Camera::SetCenter(sf::RenderWindow& window, const sf::Vector2f& center)
{
	sf::Vector2f temp(center);
	if (temp.x < window.getSize().x / 2) temp.x = window.getSize().x / 2;
	view.setCenter(temp);
	SetView(window);
}

