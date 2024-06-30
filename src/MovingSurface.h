#pragma once
#include "Surface.h"

class MovingSurface : public Surface {
private:
	b2Vec2 coord;
	b2Vec2 maxCoord;
	b2Vec2 speed;
public:
	explicit MovingSurface(b2Vec2 coord, b2Vec2 coordMax, b2Vec2 size, SurfaceType surfaceType, b2World& world);
	void changeDirection() override;


};