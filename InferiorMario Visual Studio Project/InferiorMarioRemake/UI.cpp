#include "UI.h"


UI::UI(const std::string& fontPath)
{
	font.loadFromFile(fontPath);
	text.setFont(font);
	text.setCharacterSize(25);
	text.setColor(sf::Color::White);
}
UI::~UI(void) { }
void UI::Update(float gameTime, const Player& player)
{
	score = player.GetScore();
	coins = player.GetCoins();
	time = (int)gameTime;
	offset.x = player.sprite.getPosition().x - 300;
	if (offset.x < 5) offset.x = 5;
}
void UI::Draw(sf::RenderWindow& window)
{
	// Draw name
	DrawString(5 + offset.x, 5, "PMN12003", window);

	// Draw Score
	DrawString(5 + offset.x, 30, std::to_string(score), window);

	// Draw Coins
	std::string str = "COINS: ";
	str.append(std::to_string(coins));
	DrawString(180 + offset.x, 5, str, window);

	// Draw World
	DrawString(360 + offset.x, 5, "WORLD", window);
	DrawString(382 + offset.x, 30, "1-1", window);

	// Draw Time
	DrawString(window.getSize().x - 70 + offset.x, 5, "TIME", window);
	DrawString(window.getSize().x - 60 + offset.x, 30, std::to_string(time), window);
}
void UI::DrawString(int x, int y, const std::string& value, sf::RenderWindow& window)
{
	text.setString(value);
	text.setPosition((float)x, (float)y);
	window.draw(text);
}