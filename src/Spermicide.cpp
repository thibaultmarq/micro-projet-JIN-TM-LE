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

void Spermicide::act()
{
	b2Vec2 pos = enemyBody->GetPosition();

	if (abs(end.x - start.x) - abs(end.x - pos.x ) < 0 || abs(end.y - start.y) - abs(end.y - pos.y) < 0) {
		direction *= -1;
		enemyBody->SetLinearVelocity(direction);
	}
}
