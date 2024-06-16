#include "GameManager.h"


const float GameManager::playerSpeed = 2.f;
const sf::Time GameManager::TimePerFrame = sf::seconds(1.f / 60.f);

void GameManager::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleInputs(event.key.code,true);
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
	SurfaceType surface = panel.checkPlayerTouch(player.getBody());
	switch (surface)
	{
	case SurfaceType::DRY:
			window.close();
			break;

	case SurfaceType::SWIMMABLE:
		if (left)
			player.setVelocity(-playerSpeed,0);
		if (right)
			player.setVelocity(playerSpeed, 0);
		if (jump) {
			player.setVelocity(0, playerSpeed * 10);
		}
		break;

	case SurfaceType::TOUCHABLE:
		break;

	default:
		break;
	}

	b2Vec2 cur_coords = player.getCoordinates();

	player.setCoordinates(cur_coords.x, cur_coords.y);

}

void GameManager::render()
{
	window.clear();
	player.render(window);
	panel.Render(window);

	b2Vec2 pos = player.getCoordinates();
	view.setCenter(pos.x, pos.y);

	window.setView(view);
	window.display();
}

void GameManager::handleInputs(sf::Keyboard::Key key, bool keyState)
{
	//if (player.isGrounded()) {

	if (key == sf::Keyboard::Space || key == sf::Keyboard::Z) {
		jump = keyState;
	}
	else if (key == sf::Keyboard::D)
		right = keyState;
	else if (key == sf::Keyboard::Q)
		left = keyState;
	else if (key == sf::Keyboard::K)
		player.testTeleport(150, 150);
	//}

}


void GameManager::run()
{
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	view.setSize(50,50);

	panel.AddSurface(0, 5, 5, 1, SurfaceType::SWIMMABLE, world);
	//panel.AddSurface(0, 500, 500, 10, SurfaceType::DRY, world);


	while (window.isOpen()) {

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(elapsedTime);
			world.Step(TimePerFrame.asSeconds(), 6, 2);
		}

		render();

	}

}
