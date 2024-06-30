#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Player.h"


class Enemy abstract{

protected:
	b2Body* enemyBody;
	sf::CircleShape target;
	sf::Texture texture;

	float size = 0.45f;

public:

	explicit Enemy(float x, float y, b2World& world);
	virtual void render(sf::RenderWindow& window);
	virtual void act()=0;
	virtual ~Enemy() = default;
	virtual bool getPlayerContact(Player* player);
	b2Body* getBody();


};