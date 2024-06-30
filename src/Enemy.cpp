#include "Enemy.h"

Enemy::Enemy(float x, float y, b2World& world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(x, y);
	enemyBody = world.CreateBody(&bodyDef);
	enemyBody->SetFixedRotation(true);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size,size);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	enemyBody->CreateFixture(&fixtureDef);


	target.setPosition(sf::Vector2f(enemyBody->GetPosition().x - size / 2, enemyBody->GetPosition().y - size / 2));
	target.setRadius(size*1.6f);


}

void Enemy::render(sf::RenderWindow& window)
{
	b2Vec2 pos = enemyBody->GetPosition();
	target.setPosition(pos.x - size/2, pos.y - size / 2);
	window.draw(target);
}

b2Body* Enemy::getBody() {
	return enemyBody;
}

bool Enemy::getPlayerContact(Player* player) {

	b2ContactEdge const* contactList = enemyBody->GetContactList();

	if (contactList != nullptr && contactList->other == player->getBody()) {
		return true;

	}
}