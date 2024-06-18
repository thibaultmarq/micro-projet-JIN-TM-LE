#include "Panel.h"
#include <string>
#include "string_view"



using namespace std;
using namespace literals;


Panel::Panel(const pugi::xml_node& node, b2World& world) {
	for (pugi::xml_node nnode : node.children())
	{
		float x=nnode.attribute("x").as_float();
		float y = nnode.attribute("y").as_float();
		float h = nnode.attribute("h").as_float();
		float w = nnode.attribute("w").as_float();
		SurfaceType surfaceType = typeFromString(nnode.attribute("type").as_string());
		string na = nnode.name();
		if (na == "S") {
			addStaticBlock(x,y,h,w,surfaceType,world);
		}
		else if (na ==  "M") {
			float maxX = nnode.attribute("mx").as_float();
			float maxY = nnode.attribute("my").as_float();
			addMovingBlock(b2Vec2(x, y),b2Vec2(maxX, maxY), b2Vec2(h, w), surfaceType, world);
		}
		
	}
}

void Panel::test() {
	for (auto const& surf : level) {
		if (dynamic_cast<MovingSurface*>(surf.get())) {
			static_cast<MovingSurface*>(surf.get())->changeDirection();
		}
	}
	
}


SurfaceType Panel::typeFromString(std::string  const& s) const{
	if (s == "SWIM") {
		return SurfaceType::SWIMMABLE;
	} 
	if (s == "DRY") {
		return SurfaceType::DRY;
	}
	return SurfaceType::TOUCHABLE;
}


void Panel::render(sf::RenderTarget& window) const {
	for (auto const& c : level) {
		c->render(window);
	}
}
void Panel::addStaticBlock(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world) {
	float thickness;
	if (surfaceType == SurfaceType::SWIMMABLE) {
		thickness = 1.f;
		addSurface(x, y, h, w-thickness, surfaceType, world);
		addSurface(x-0.5f, y +w- thickness, h+1,  thickness, SurfaceType::TOUCHABLE, world);

	}
	else {
		thickness = 0.01f;

		addSurface(x, y, h, w, SurfaceType::TOUCHABLE, world);
		addSurface(x, y, h, thickness, surfaceType, world);
		//AddSurface(x, y + thickness, -thickness, -thickness, SurfaceType::TOUCHABLE, world);
		//AddSurface(x + h + thickness, y + thickness, -thickness, -thickness, SurfaceType::TOUCHABLE, world);

	}
}

void Panel::addMovingBlock(b2Vec2 coord, b2Vec2 maxCoord, b2Vec2 size, SurfaceType surfaceType, b2World & world) {
	float thickness;
	if (surfaceType == SurfaceType::SWIMMABLE) {
		thickness = 1.f;
		addSurface(coord, maxCoord, b2Vec2(size.x,size.y- thickness), surfaceType, world);
		addSurface(coord + b2Vec2(-0.5f,size.y- thickness),maxCoord+ b2Vec2(-0.5,size.y-thickness),  b2Vec2(size.x+1.f,thickness), SurfaceType::TOUCHABLE, world);

	}
	else {
		thickness = 0.01f;

		addSurface(coord, maxCoord,size, SurfaceType::TOUCHABLE, world);
		addSurface(coord, maxCoord, b2Vec2(size.x,thickness), surfaceType, world);
		//AddSurface(x, y + thickness, -thickness, -thickness, SurfaceType::TOUCHABLE, world);
		//AddSurface(x + h + thickness, y + thickness, -thickness, -thickness, SurfaceType::TOUCHABLE, world);

	}
}
	
	


void Panel::addSurface(float x, float y, float h, float w ,SurfaceType surfaceType, b2World& world) {

	level.push_back(make_unique<StaticSurface>(x, y, h, w, surfaceType, world));
}

void Panel::addSurface(b2Vec2 coord, b2Vec2 maxCoord, b2Vec2 size, SurfaceType surfaceType, b2World& world) {
	level.push_back(make_unique<MovingSurface>(coord, maxCoord, size, surfaceType, world));
}

SurfaceType Panel::checkPlayerTouch( Player* player) const {
	SurfaceType res = SurfaceType::VOID;
	for (auto const& c : level) {

		b2ContactEdge const* contactList = c->getBody()->GetContactList();

		if ( contactList != nullptr && contactList->other == player->getBody()) {
			if (c->getType() == SurfaceType::SWIMMABLE)

			{
				return c->getType();
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
			res = c->getType();
			
		}
		else if (c->getTarget().getGlobalBounds().intersects(player->getTarget().getGlobalBounds()) && c->getType() == SurfaceType::SWIMMABLE) {
			
			return SurfaceType::SWIMMABLE;
		}
	}
	return res;
}