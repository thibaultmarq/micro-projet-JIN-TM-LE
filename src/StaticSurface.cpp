#include "StaticSurface.h"




StaticSurface::StaticSurface(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world) : Surface{   h,  w,  surfaceType} {
	b2BodyDef bodyDef;

	bodyDef.type = b2_staticBody;


	bodyDef.position.Set(x + h / 2, y + w / 2);

	body = world.CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(h / 2, w / 2);
	body->CreateFixture(&groundBox, 0.0f);

}

