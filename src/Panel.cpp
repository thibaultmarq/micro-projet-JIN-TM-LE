#include "Panel.h"



void Panel::Render(sf::RenderTarget& window) const {
	for (auto const& c : level) {
		c.Render(window);
	}
}

void Panel::AddSurface(float x, float y, float h, float w ,SurfaceType surfaceType, b2World& world) {
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;

	bodyDef.type = b2_staticBody;

		
	bodyDef.position.Set(x,y);

	b2Body * body = world.CreateBody(&bodyDef);
	
	
	dynamicBox.SetAsBox(h, w);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	body->CreateFixture(&groundBox, 0.0f);

	
	Surface surf(x, y,h,w, surfaceType, body);
	level.push_back(surf);
}