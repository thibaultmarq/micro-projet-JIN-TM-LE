#include "Surface.h"




Surface::Surface( float h, float w, SurfaceType surfaceType) : size{ sf::Vector2f(h,w) }, surfaceType{ surfaceType } {

	if (surfaceType == SurfaceType::SWIMMABLE) {
		target.setFillColor(sf::Color::White);
	}
	else {
		target.setFillColor(sf::Color::Red);
	}

}


void Surface::render(sf::RenderTarget& window){
	
	if (surfaceType == SurfaceType::SWIMMABLE) {
		float thickness = 0.5f;
		target.setPosition(sf::Vector2f(body->GetPosition().x - size.x / 2 - thickness, body->GetPosition().y - size.y / 2 - thickness));
		target.setSize(sf::Vector2f(size.x + 2 * thickness, size.y + thickness));
	}
	else {
		target.setPosition(sf::Vector2f(body->GetPosition().x - size.x / 2, body->GetPosition().y - size.y / 2));
		target.setSize(sf::Vector2f(size.x, size.y));
	}
	window.draw(target);
}

b2Body* Surface::getBody() const{
	return body;
}

SurfaceType Surface::getType() const {
	return surfaceType;
}

sf::RectangleShape Surface::getTarget() const {
	return target;
}
