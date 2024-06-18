#pragma once
#include "SurfaceType.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Surface abstract {
public:
	sf::Vector2f size;
	SurfaceType surfaceType;
	b2Body* body;
	sf::RectangleShape target;
	
	Surface()= default;
	explicit Surface( float h, float w, SurfaceType surfaceType);
	virtual ~Surface() = default;



	void render(sf::RenderTarget& window);
	SurfaceType getType() const;
	b2Body* getBody() const;
	sf::RectangleShape getTarget() const; 

};