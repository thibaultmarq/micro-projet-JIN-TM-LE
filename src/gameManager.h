#pragma once
#include "SFML/Graphics.hpp"
#include <Player.h>
#include "box2d/box2d.h"
#include "Panel.h"

class GameManager {
private:

	b2World world{b2Vec2(0.f,200.f)};

	Player player{ &world };
	Panel panel;

	bool jump{ false };
	bool left{ false };
	bool right{ false };

	static const float playerSpeed;


	void processEvents();
	void update(sf::Time elapsedTime);
	void render();
	void handleInputs(sf::Keyboard::Key key, bool keyState);

	static const sf::Time TimePerFrame;

	sf::RenderWindow window{ sf::VideoMode{800,600}, "Splerm", sf::Style::Close };

public:
	void run();




};