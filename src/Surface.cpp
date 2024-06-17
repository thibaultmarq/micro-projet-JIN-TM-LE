#include "Surface.h"



Surface::Surface(float h, float w, SurfaceType surfaceType, b2Body* body) : size{ sf::Vector2f(h,w) }, surfaceType{ surfaceType }, body{body} {

	
	
	if (surfaceType == SurfaceType::SWIMMABLE) {
		float thickness = 0.5f;
		target.setPosition(sf::Vector2f(body->GetPosition().x - h / 2 - thickness, body->GetPosition().y - w / 2 - thickness));
		target.setSize(sf::Vector2f(size.x + 2* thickness, size.y + thickness));
		
		target.setFillColor(sf::Color::White);
	}
	else {
		target.setPosition(sf::Vector2f(body->GetPosition().x - h / 2, body->GetPosition().y - w / 2));
		target.setSize(sf::Vector2f(size.x, size.y));
		target.setFillColor(sf::Color::Red);
	}
	if (surfaceType == SurfaceType::TOUCHABLE) {
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

sf::RectangleShape Surface::getTarget() const {
	return target;
}