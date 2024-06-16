#include "Surface.h"



Surface::Surface(float h, float w, SurfaceType surfaceType, b2Body* body) : size{ sf::Vector2f(h,w) }, surfaceType{ surfaceType }, body{body} {
	target.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
	target.setSize(sf::Vector2f(size.x * 100, size.y*100));
	target.setFillColor(sf::Color::Red);
}


void Surface::Render(sf::RenderTarget& window) const{
	
	
	window.draw(target);
}

b2Body* Surface::getBody() {
	return body;
}

SurfaceType Surface::getType() {
	return surfaceType;
}