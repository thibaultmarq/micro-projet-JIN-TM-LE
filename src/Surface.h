#pragma once
#include "SurfaceType.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Surface {
private:
	sf::Vector2f size;
	SurfaceType surfaceType;
	b2Body* body;
public:
	void Render(sf::RenderTarget& window) const;
	Surface(float x, float y, float h, float w, SurfaceType surfaceType, b2Body* body);
};