#include "Surface.h"



Surface::Surface(float x, float y, float h, float w, SurfaceType surfaceType, b2Body* body) : size{ sf::Vector2f(h,w) }, surfaceType{ surfaceType }, body{body} {}


void Surface::Render(sf::RenderTarget& window) const{
	sf::RectangleShape block;
	block.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
	block.setSize(sf::Vector2f(size.x, size.y));
	block.setFillColor(sf::Color::Red);
	window.draw(block);
}