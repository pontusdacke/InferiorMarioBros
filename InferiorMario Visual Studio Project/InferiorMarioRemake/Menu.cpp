#include "Menu.h"


Menu::Menu(void)
{
}
Menu::~Menu(void)
{
}
void Menu::MoveMarkerUp(void)
{
	option--;
	if(option < 0) option = 1;
	marker.setPosition(180, 310 + (option * 30));
}
void Menu::MoveMarkerDown(void)
{
	option++;
	if(option > 1) option = 0;
	marker.setPosition(180, 310 + (option * 30));
}
void Menu::Initialize(const std::string& backgroundPath, const std::string& markerPath, const std::string& fontPath)
{
	backgroundTexture.loadFromFile(backgroundPath);
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);
	markerTexture.loadFromFile(markerPath);
	marker.setTexture(markerTexture);
	marker.setPosition(180, 300);
	font.loadFromFile(fontPath);

	option = 0;
	keyPressed = false;
	startGame = false;
	play = "1 PLAYER GAME";
	exit = "EXIT GAME";
	tPlay.setString(play);
	tPlay.setFont(font);
	tPlay.setCharacterSize(30);
	tPlay.setPosition(200, 300); 
	tExit.setString(exit);
	tExit.setFont(font);
	tExit.setCharacterSize(30);
	tExit.setPosition(200, 330);

}
void Menu::Exit(sf::RenderWindow& window)
{
	startGame = false;
	window.close();
}
void Menu::Update(sf::RenderWindow& window)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !keyPressed)
	{
		keyPressed = true;
		MoveMarkerDown();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !keyPressed)
	{
		keyPressed = true;
		MoveMarkerUp();
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		keyPressed = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch(option)
		{
		case 0:
			startGame = true;
			break;
		case 1:
			Exit(window);
			break;
		}
	}

	sf::Event evt;
	while(window.pollEvent(evt))
	{
		switch(evt.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}
void Menu::Draw(sf::RenderWindow& window)
{
	// Perform a typical render process. (Clear screen, draw stuff, display it)
	window.clear();

	window.draw(background);
	window.draw(tPlay);
	window.draw(tExit);
	window.draw(marker);

	window.display();
} 
void Menu::MainLoop(sf::RenderWindow& window)
{
	Update(window);
	Draw(window);
}
bool Menu::GetStartGame(sf::RenderWindow& window) 
{
	if(window.isOpen())
		return startGame; 
	else
		return false;
}