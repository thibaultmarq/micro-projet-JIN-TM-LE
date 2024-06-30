#include "Mycose.h"

Mycose::Mycose(float x, float y, float spd, b2Vec2 direction, b2World& world)
	: Enemy{ x,y,world },
	speed{ spd },
	world { world },
	direction { direction }
{

	target.setFillColor(sf::Color::Blue);
}

void Mycose::act()
{
	frameBeforeNextSpawn--;
	if (frameBeforeNextSpawn < 0) {
		frameBeforeNextSpawn = 300;
		b2Vec2 position = enemyBody->GetPosition();
		Bullet bullet(position, direction, world);
	}
}