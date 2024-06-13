#pragma once
#include "box2d/box2d.h"
#include <vector>
#include "SFML/Graphics.hpp"

class Player {
public:
	b2Body* playerBody;
private:
	void Render(sf::RenderTarget& window) const;
	b2Vec2 getPosition() const;

};