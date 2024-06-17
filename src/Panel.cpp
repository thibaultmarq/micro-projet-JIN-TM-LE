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

		
	bodyDef.position.Set(x+h/2,y+w/2);

	b2Body * body = world.CreateBody(&bodyDef);
	
	

	
	b2PolygonShape groundBox;
	groundBox.SetAsBox(h/2, w/2);
	body->CreateFixture(&groundBox, 0.0f);
	
	
	Surface surf(h,w, surfaceType, body);

	level.push_back(surf);
}

SurfaceType Panel::checkPlayerTouch( Player* player) const {
	for (auto const& c : level) {

		if ( c.getBody()->GetContactList() != nullptr && c.getBody()->GetContactList()->other == player->getBody()) {
			
			return c.getType();

		}
		else if (c.getTarget().getGlobalBounds().intersects(player->getTarget().getGlobalBounds())) {
			
			return SurfaceType::SWIMMABLE;
		}
	}
	return SurfaceType::TOUCHABLE;
}