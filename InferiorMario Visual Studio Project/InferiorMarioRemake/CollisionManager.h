#pragma once
#include <SFML\Graphics.hpp>
#include "BaseTile.h"

// Circular dependency bypass
class Entity;
class Level;
class Camera;

// Global Functions
bool Collision(sf::RenderWindow &window, const Level &level, Camera &camera, Entity &entity, sf::FloatRect &collisionRectangle,  sf::Vector2i &baseTile);
bool ObjectCollision(sf::RenderWindow &window, Level& level, Camera &camera, Entity &entity, int &object);
bool Intersect(const sf::FloatRect &rectA, const sf::FloatRect &rectB);
