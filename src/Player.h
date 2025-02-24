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
	b2Vec2 getVelocity() const;


	b2Body* getBody();
	void setCoordinates(float xpos, float ypos);
	void setVelocity(float xspeed, float yspeed);

	void testTeleport(float xpos, float ypos);

	sf::CircleShape getTarget() const;

};