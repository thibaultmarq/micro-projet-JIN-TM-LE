#include "Spermicide.h"

Spermicide::Spermicide(float x, float y, float endx, float endy, float spd, b2World& world) 
	: Enemy{x,y,world},
	start{b2Vec2(x,y)},
	end{b2Vec2(endx,endy)},
	speed{spd}
{
	direction = end - start;
	direction.Normalize();
	direction *= speed;

	enemyBody->SetLinearVelocity(direction);

	target.setFillColor(sf::Color::Green);
}

void Spermicide::move()
{
	b2Vec2 pos = enemyBody->GetPosition();
	if ( pos == end || pos == start) {
		direction *= -1;
		enemyBody->SetLinearVelocity(direction);
	}
}
