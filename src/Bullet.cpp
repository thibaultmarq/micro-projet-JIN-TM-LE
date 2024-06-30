#include "Bullet.h"

Bullet::Bullet(b2Vec2 position, b2Vec2 direction, b2World& world) : Enemy{position.x, position.y, world} {

	direction.Normalize();
	direction *= speed;

	//body.position.Set(x+direction.x*speed, y+ direction.y * speed);



	body->SetLinearVelocity(direction);
	float size = 0.2f;
	target.setPosition(sf::Vector2f(body->GetPosition().x - size / 2, body->GetPosition().y - size / 2));
	target.setRadius(size);

	target.setFillColor(sf::Color::Blue);
}

void Bullet::act() {
	printf("wait)");
	//
}