#include "MovingSurface.h"



MovingSurface::MovingSurface(b2Vec2 coord, b2Vec2 coordMax, b2Vec2 size, SurfaceType surfaceType, b2World& world) : Surface{   size.x,  size.y,  surfaceType }, coord{ coord } , maxCoord { coordMax + b2Vec2(size.x/2, size.y/2)} {
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	coord += b2Vec2(size.x / 2, size.y / 2);
	bodyDef.position.Set(coord.x, coord.y);
	body = world.CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x/2, size.y/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	
	speed = (maxCoord - coord);
	speed.Normalize();
	speed *= 5;

	body->SetLinearVelocity(speed);

}

void MovingSurface::changeDirection() {
	if (abs(maxCoord.x  - coord.x) - abs(maxCoord.x - (body->GetPosition().x-size.x/2)) < 0 || abs(maxCoord.x - coord.x) - abs(coord.x - (body->GetPosition().x)) < 0 || abs(maxCoord.y - coord.y) - abs(maxCoord.y - (body->GetPosition().y - size.y / 2)) < 0 || abs(maxCoord.y - coord.y) - abs(coord.y - (body->GetPosition().y)) < 0) {
		speed = -speed;
		body->SetLinearVelocity(speed);
	}	
}

