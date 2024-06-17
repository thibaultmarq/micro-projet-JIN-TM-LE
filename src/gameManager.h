#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <Player.h>
#include "box2d/box2d.h"
#include "Panel.h"
#include <array>

class GameManager {
private:

	b2World world{b2Vec2(0.f,25.f)};

	Player player{ &world };
	Panel panel;

	bool jump{ false };
	bool left{ false };
	bool right{ false };

	static const float playerSpeed;


	void processEvents();
	void update();
	void render();
	void handleInputs(sf::Keyboard::Key key, bool keyState);

	static const sf::Time TimePerFrame;

	sf::RenderWindow window{ sf::VideoMode{800,600}, "Splerm", sf::Style::Close };
	sf::View view;

	std::array<sf::Sound,2> splurch;
	sf::Sound bump;
	std::array<sf::Sound,2> death;
	sf::Sound victory;
	int soundState{ 0 };


public:
	void run();




};