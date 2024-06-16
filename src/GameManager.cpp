#include "GameManager.h"


const float GameManager::playerSpeed = 500.f;
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
	if (left)
		player.setVelocity(-playerSpeed,0);
	if (right)
		player.setVelocity(playerSpeed, 0);
	if (jump)
		player.setVelocity(0, 30000);

	b2Vec2 cur_coords = player.getCoordinates();

	player.setCoordinates(cur_coords.x , cur_coords.y);

	if (panel.checkPlayerDryTouch(player.getBody())) {
		
		window.close();
	}
}

void GameManager::render()
{
	window.clear();
	player.render(window);
	panel.Render(window);
	window.display();
}

void GameManager::handleInputs(sf::Keyboard::Key key, bool keyState)
{
	//if (player.isGrounded()) {

	if (key == sf::Keyboard::Space || key == sf::Keyboard::Z)
		jump = keyState;
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
	

	panel.AddSurface(0, 500, 500, 10, SurfaceType::SWIMMABLE, world);
	panel.AddSurface(0, 500, 500, 10, SurfaceType::DRY, world);


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

		b2Vec2 vel = player.getVelocity();
		printf("Player velocity : (%f, %f) \n", vel.x, vel.y);
		render();

	}

}
