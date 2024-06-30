#include "Bullet.h"

Bullet::Bullet(b2Vec2 position, b2Vec2 direction, b2World& world) : Enemy{ position.x, position.y, world }, direction{ direction } {

	direction.Normalize();
	direction *= speed;

	//body.position.Set(x+direction.x*speed, y+ direction.y * speed);


	
	enemyBody->SetLinearVelocity(direction);
	target.setPosition(sf::Vector2f(position.x - 0.2f / 2,position.y - 0.2f / 2));
	target.setRadius(0.2f);

	target.setFillColor(sf::Color::Yellow);
}

void Bullet::act() {
	printf("wait)");
	//
}