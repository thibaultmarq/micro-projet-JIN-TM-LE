#pragma once

#include "Enemy.h"

class Spermicide : public Enemy {

public:

	explicit Spermicide(float x, float y, float endx, float endy, float spd, b2World& world);
	void move() override;

private:

	b2Vec2 start;
	b2Vec2 end;
	b2Vec2 direction;
	float speed;

};