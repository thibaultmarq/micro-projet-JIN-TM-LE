#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <Player.h>
#include "box2d/box2d.h"
#include "Panel.h"
#include  "pugixml.hpp"
#include <array>
#include "SaveFile.h"
#include <unordered_map>
#include "Command.h"
#include <set>

class GameManager {
private:

	b2World world{ b2Vec2(0.f,25.f) };

	Player player{ &world };
	Panel panel;

	SurfaceType lastSurface = SurfaceType::VOID;

	std::unordered_map < sf::Keyboard::Key, std::unique_ptr<Command>> commandMap;

	
	std::set<sf::Keyboard::Key> inputList;
	bool left{ false };
	bool right{ false };
	bool jump{ false };

	float displayTime = 3;

	static const float playerSpeed;

	void processEvents();
	void update(sf::Time elapsedTime);
	void render();
	void handleInputs(sf::Keyboard::Key key, bool keyState);

	static const sf::Time TimePerFrame;

	sf::RenderWindow window{ sf::VideoMode{800,600}, "Splerm", sf::Style::Close };
	sf::View view;
	sf::Text scoreText;

	std::array<sf::Sound,2> splurch;
	sf::Sound bump;
	std::array<sf::Sound,2> death;
	sf::Sound victory;
	int soundState{ 0 };

	SaveFile save;


public:
	void run();




};