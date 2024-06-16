#include "Player.h"

Player::Player(b2World* world)
{


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.5, 0.5);
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
	b2Vec2 vel = playerBody->GetLinearVelocity();
	b2Vec2 goal{ xspeed , -yspeed };

	if (xspeed == 0)
		goal.x = vel.x;
	if (yspeed == 0)
		goal.y = vel.y;

	printf("New velocity : (%f, %f)\n", goal.x, goal.y);
	playerBody->SetLinearVelocity(goal);

}

void Player::testTeleport(float xpos, float ypos)
{
	playerBody->SetTransform(b2Vec2(xpos, ypos),0);

}

bool Player::isGrounded() const
{

	b2Vec2 center = playerBody->GetPosition();
	b2Vec2 bottom = center + b2Vec2(0, 40.f);

	b2RayCastInput input;
	input.p1 = center;
	input.p2 = bottom;
	input.maxFraction = 1;

	b2RayCastOutput output;

	bool ret = playerBody->GetFixtureList()->RayCast(&output, input, 0);

	printf("grounded : %d\n", ret);

	return ret;
}

b2Body* Player::getBody() {
	return playerBody;
}

