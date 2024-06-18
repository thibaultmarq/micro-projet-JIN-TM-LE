#pragma once
#include "Surface.h"
class StaticSurface : public Surface {

public:
	explicit StaticSurface(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world);

};