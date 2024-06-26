#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"


class Enemy {

protected:
	b2Body* enemyBody;
	sf::CircleShape target;
	sf::Texture texture;

public:

	explicit Enemy(float x, float y, b2World& world);
	virtual void render(sf::RenderWindow& window);
	virtual void move() = 0;
	virtual ~Enemy() = default;



};