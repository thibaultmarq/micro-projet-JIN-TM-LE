#pragma once
#include "Enemy.h"
#include "Bullet.h"

class Mycose : public Enemy {
public :
	explicit Mycose(float x, float y, float spd, b2Vec2 direction,  b2World& world);
	void act() override;
private:
	float speed;
	int frameBeforeNextSpawn=300;
	b2World& world;
	b2Vec2 direction;
};