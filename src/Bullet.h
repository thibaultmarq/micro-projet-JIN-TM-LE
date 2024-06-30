#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Enemy.h"

class Bullet : public Enemy {
public:
	explicit Bullet(b2Vec2 position, b2Vec2 direction, b2World& world);
	void act() override;
private:
	float speed = 2.;
	b2Vec2 direction;

};