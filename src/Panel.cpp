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
	
	


	b2PolygonShape groundBox;
	groundBox.SetAsBox(h, w);
	body->CreateFixture(&groundBox, 0.0f);

	
	Surface surf(h,w, surfaceType, body);

	level.push_back(surf);
}

SurfaceType Panel::checkPlayerTouch( const b2Body* playerBody) const {
	for (auto c : level) {
		if (c.getBody()->GetContactList() != nullptr) {
			//printf("coucou %p , %p \n", playerBody, c.getBody()->GetContactList()->other);
		}
		
		if (c.getBody()->GetContactList() != nullptr && c.getBody()->GetContactList()->other == playerBody) {
			//printf("oui \n");
				return c.getType();
		}
	}
	return SurfaceType::TOUCHABLE;
}