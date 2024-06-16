#pragma once
#include "SurfaceType.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Surface {
private:
	sf::Vector2f size;
	SurfaceType surfaceType;
	b2Body* body;
	sf::RectangleShape target;
public:
	void Render(sf::RenderTarget& window) const;
	Surface( float h, float w, SurfaceType surfaceType, b2Body* body);
	SurfaceType getType() const;
	b2Body* getBody() const;
};