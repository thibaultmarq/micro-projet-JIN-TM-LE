#include "Player.h"

Player::Player(b2World* world)
{


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(50, 50);
	playerBody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(20, 20);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	playerBody->CreateFixture(&fixtureDef);

	target.setPosition(sf::Vector2f(50,50));
	target.setRadius(20);
	target.setFillColor(sf::Color::White);

}

void Player::render(sf::RenderTarget &window) const
{

	window.draw(target);

}


b2Vec2 Player::getCoordinates() const
{
	return playerBody->GetPosition();
}


void Player::setCoordinates(float xpos, float ypos)
{
	target.setPosition(xpos, ypos);

}

