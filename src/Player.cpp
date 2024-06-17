#include "Player.h"

Player::Player(b2World* world)
{


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(1, -1);
	playerBody = world->CreateBody(&bodyDef);
	playerBody->SetFixedRotation(true);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.005f, 0.005f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	playerBody->CreateFixture(&fixtureDef);


	target.setPosition(sf::Vector2f(5,5));
	target.setRadius(0.5f);
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

b2Vec2 Player::getVelocity() const
{
	return playerBody->GetLinearVelocity();
}


void Player::setCoordinates(float xpos, float ypos)
{
	target.setPosition(xpos, ypos);

}

void Player::setVelocity(float xspeed, float yspeed)
{	
	b2Vec2 goal{ xspeed , -yspeed };

	goal *= playerBody->GetMass();
	playerBody->ApplyLinearImpulseToCenter(goal,true);

}

void Player::testTeleport(float xpos, float ypos)
{
	playerBody->SetTransform(b2Vec2(xpos, ypos),0);

}


b2Body* Player::getBody() {
	return playerBody;
}

sf::CircleShape Player::getTarget() const{
	return target;
}