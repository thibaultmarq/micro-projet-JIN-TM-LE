#include "GameManager.h"


const float GameManager::playerSpeed = 0.f;
const sf::Time GameManager::TimePerFrame = sf::seconds(1.f / 60.f);

void GameManager::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleInputs(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handleInputs(event.key.code, false);
			break;

		case sf::Event::Closed:
			window.close();
			break;

		default:
			break;
		}

	}


}

void GameManager::update(sf::Time elapsedTime)
{
	b2Vec2 new_speed(0,0);
	if (jump)
		new_speed.y += playerSpeed;
	if (right)
		new_speed.x += playerSpeed;
	if (left)
		new_speed.x -= playerSpeed;

	b2Vec2 cur_coords = player.getCoordinates();

	player.setCoordinates(cur_coords.x + new_speed.x * elapsedTime.asSeconds(), cur_coords.y + new_speed.y * elapsedTime.asSeconds());
}

void GameManager::render()
{
	window.clear();
	player.render(window);
	panel.Render(window);
	window.display();
}

void GameManager::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Space || key == sf::Keyboard::Z)
		jump = isPressed;
	else if (key == sf::Keyboard::D)
		right = isPressed;
	else if (key == sf::Keyboard::Q)
		left = isPressed;

}


void GameManager::run()
{
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	panel.AddSurface(0, 500, 500, 10, SurfaceType::SWIMMABLE, world);

	while (window.isOpen()) {

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
			world.Step(TimePerFrame.asSeconds(), 6, 2);
		}

		render();

	}

}
