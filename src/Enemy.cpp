#include "Enemy.h"

Enemy::Enemy(float x, float y, b2World& world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(x, y);
	enemyBody = world.CreateBody(&bodyDef);
	enemyBody->SetFixedRotation(true);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.45f, 0.45f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	enemyBody->CreateFixture(&fixtureDef);

	float size = 2;

	target.setPosition(sf::Vector2f(enemyBody->GetPosition().x - size / 2, enemyBody->GetPosition().y - size / 2));
	target.setRadius(size);


}

void Enemy::render(sf::RenderWindow& window)
{
	b2Vec2 pos = enemyBody->GetPosition();
	target.setPosition(pos.x, pos.y);
	window.draw(target);
}

b2Body* Enemy::getBody() {
	return enemyBody;
}