#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

class Player {

private :

	b2Body* playerBody;

	sf::Texture	texture;
	sf::CircleShape	target;

public :

	explicit Player(b2World* world);

	void render(sf::RenderTarget& window) const;
	
	
	b2Vec2 getCoordinates() const;

	void setCoordinates(float xpos, float ypos);
	

};