#include "Panel.h"
#include <string>
#include "string_view"


Panel::Panel(const pugi::xml_node& node, b2World& world) {
	for (pugi::xml_node node : node.children())
	{
		float x=node.attribute("x").as_float();
		float y = node.attribute("y").as_float();
		float h = node.attribute("h").as_float();
		float w = node.attribute("w").as_float();
		SurfaceType surfaceType = typeFromString(node.attribute("type").as_string());
		AddSurfaceBlock(x,y,h,w,surfaceType,world);
	}
}

SurfaceType Panel::typeFromString(std::string  const& s) {
	if (s == "SWIM") {
		return SurfaceType::SWIMMABLE;
	} 
	if (s == "DRY") {
		return SurfaceType::DRY;
	}
	return SurfaceType::TOUCHABLE;
}


void Panel::Render(sf::RenderTarget& window) const {
	for (auto const& c : level) {
		c.Render(window);
	}
}
void Panel::AddSurfaceBlock(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world) {
	float thickness;
	if (surfaceType == SurfaceType::SWIMMABLE) {
		thickness = 1.f;
		AddSurface(x, y, h,thickness, surfaceType, world);
		AddSurface(x, y+thickness, h, w - thickness, SurfaceType::TOUCHABLE, world);

	}else {
		thickness =0.01f;
		
		AddSurface(x, y, h, w, SurfaceType::TOUCHABLE, world);
		AddSurface(x , y, h , thickness, surfaceType, world);
		//AddSurface(x, y + thickness, -thickness, -thickness, SurfaceType::TOUCHABLE, world);
		//AddSurface(x + h + thickness, y + thickness, -thickness, -thickness, SurfaceType::TOUCHABLE, world);
		
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
	SurfaceType res = SurfaceType::VOID;
	for (auto const& c : level) {

		b2ContactEdge const* contactList = c.getBody()->GetContactList();

		if ( contactList != nullptr && contactList->other == player->getBody()) {
			if (c.getType() == SurfaceType::SWIMMABLE)
			{
				return c.getType();
			}/*
			if (res == SurfaceType::VOID) {

				res = c.getType();
			}
			else if (res == SurfaceType::DRY) {
				res = c.getType();
			}
			if (c.getType() == SurfaceType::DRY) {
				printf("salut\n");
			}*/
			res = c.getType();
			
		}
		else if (c.getTarget().getGlobalBounds().intersects(player->getTarget().getGlobalBounds()) && c.getType() == SurfaceType::SWIMMABLE) {
			
			return SurfaceType::SWIMMABLE;
		}
	}
	return res;
}