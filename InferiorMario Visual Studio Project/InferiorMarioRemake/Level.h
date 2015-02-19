#pragma once
#include <vector>
#include <fstream>
#include "rapidxml.hpp"
#include "TextureHandler.h"
#include "CollisionTile.h"
#include "Camera.h"

class Enemy;

class Level
{
public:
	// Constructors & Destructors
	Level(void);
	~Level(void);
	
	// Getters & Setters
	CollisionTile* GetTile(unsigned int x, unsigned int y) const;
	BaseTile* GetObject(unsigned int x, unsigned int y) const;
	Enemy* GetEnemy(unsigned int x) const;

	// Functions
	void AddObject(int x, int y, BaseTile* obj);
	void LoadLevel(const std::string& fileName, TextureHandler& textureHandler);
	const sf::Vector2i& GetDimensions(void) const;
	void DeleteObject(int x, int y);
	void DeleteEnemy(int x);
	void Draw(sf::RenderWindow& window, Camera& camera);
	void DrawEnemies(sf::RenderWindow& window, Camera& camera);
	void UpdateEnemies(sf::RenderWindow& window, Camera& camera);

private:
	// Variabels & Objects 
	std::vector<std::vector<CollisionTile*>> map;
	std::vector<std::vector<BaseTile*>> objectMap;
	std::vector<Enemy*> enemyList;
	sf::Vector2i dimensions;
	int enemyCount;

	// Functions
	void SetDimensions(int width, int height);
	void AddEnemy(int x, Enemy* enemy);
	void AddTile(int x, int y, CollisionTile* tile);
	void DeleteTile(int x, int y);
};