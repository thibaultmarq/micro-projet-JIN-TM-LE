#include "Surface.h"



Surface::Surface(float h, float w, SurfaceType surfaceType, b2Body* body) : size{ sf::Vector2f(h,w) }, surfaceType{ surfaceType }, body{body} {

	target.setPosition(sf::Vector2f(body->GetPosition().x-h/2, body->GetPosition().y-w/2));
	
	if (surfaceType == SurfaceType::SWIMMABLE) {
		target.setSize(sf::Vector2f(size.x, size.y));
		target.setFillColor(sf::Color::White);
	}
	else {
		target.setSize(sf::Vector2f(size.x, size.y));
		target.setFillColor(sf::Color::Red);
	}

}


void Surface::Render(sf::RenderTarget& window) const{
	
	
	window.draw(target);
}

b2Body* Surface::getBody() const{
	return body;
}

SurfaceType Surface::getType() const {
	return surfaceType;
}