#include "GameManager.h"

#include <iostream>






const float GameManager::playerSpeed = 1.f;
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

void GameManager::update()
{	
	SurfaceType surface = panel.checkPlayerTouch(&player);
	player.getBody()->SetGravityScale(1);
	switch (surface)
	{
	case SurfaceType::DRY:
		if (death[soundState].getStatus() == sf::Sound::Stopped)
			death[soundState].play();

			
		b2Vec2 vel = player.getVelocity();
		if (vel.x ==0 && vel.y ==0)
			window.close();
		break;
	case SurfaceType::SWIMMABLE:
		player.getBody()->SetGravityScale(0.5);
		if (left)
			player.setVelocity(-playerSpeed,0);
		if (right)
			player.setVelocity(playerSpeed, 0);
		if (jump) {
			player.setVelocity(0, playerSpeed * 4.f);
		}
		splurch[soundState].play();
		break;

	case SurfaceType::TOUCHABLE:
		bump.play();
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
	
	panel.Render(window);
	player.render(window);
	b2Vec2 pos = player.getCoordinates();
	view.setCenter(12.5, pos.y);

	window.setView(view);
	window.display();
}

void GameManager::handleInputs(sf::Keyboard::Key key, bool keyState)
{

	if (key == sf::Keyboard::Space || key == sf::Keyboard::Z) {
		jump = keyState;
	}
	else if (key == sf::Keyboard::D)
		right = keyState;
	else if (key == sf::Keyboard::Q)
		left = keyState;
	else if (key == sf::Keyboard::N)
		soundState = 0;
	else if (key == sf::Keyboard::W)
		soundState = 1;

}


void GameManager::run()
{
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	view.setSize(20,20);

	
	pugi::xml_document doc;
	auto result = doc.load_file("resources/level.xml");
	if ( !result)
	{
		std::cerr << "Could not open file visage.xml because " << result.description() << std::endl;
		return ;
	}
	panel= Panel{ doc.child("Level"), world};
	//panel.AddSurface(0, 25, 1, 25, SurfaceType::SWIMMABLE, world);
	//panel.AddSurface(0, 50, 25, 1, SurfaceType::SWIMMABLE, world);

	std::pair<sf::SoundBuffer, sf::SoundBuffer> bufferSplurch;
	sf::SoundBuffer bufferBump;
	std::pair<sf::SoundBuffer, sf::SoundBuffer> bufferDeath;
	sf::SoundBuffer bufferVictory;
	
	if (!bufferSplurch.first.loadFromFile("resources/splurch1.mp3")) {
		printf("Splurch didn't load !\n");
		window.close();
	}
	if (!bufferSplurch.second.loadFromFile("resources/splurch2.mp3")) {
		printf("Splurch didn't load !\n");
		window.close();
	}
	splurch[0].setBuffer(bufferSplurch.first);

	splurch[1].setBuffer(bufferSplurch.second);
	splurch[1].setVolume(30);

	if (!bufferBump.loadFromFile("resources/bump.mp3")) {
		printf("Bump didn't load !\n");
		window.close();
	}
	bump.setBuffer(bufferBump);

	if (!bufferDeath.first.loadFromFile("resources/death1.mp3")) {
		printf("Death didn't load !\n");
		window.close();
	}
	if (!bufferDeath.second.loadFromFile("resources/death2.mp3")) {
		printf("Death didn't load !\n");
		window.close();
	}
	
	death[0].setBuffer(bufferDeath.first);
	death[0].setVolume(30);
	death[1].setBuffer(bufferDeath.second);


	if (!bufferVictory.loadFromFile("resources/victory.mp3")) {
		printf("Victory didn't load !\n");
		window.close();
	}

	victory.setBuffer(bufferVictory);
	
	//panel.AddSurfaceBlock(-2, -1000, 5, 1000, SurfaceType::TOUCHABLE, world);
//	panel.AddSurfaceBlock(22, -1000, 5, 1000, SurfaceType::TOUCHABLE, world);
//	panel.AddSurfaceBlock(13, -12, 2, 2, SurfaceType::SWIMMABLE, world);
//	panel.AddSurfaceBlock(0, 0, 25, 25, SurfaceType::SWIMMABLE, world);




	while (window.isOpen()) {

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update();
			world.Step(TimePerFrame.asSeconds(), 6, 2);
		}

		b2Vec2 vel = player.getVelocity();
		//printf("Player velocity : (%f, %f)\n", vel.x, vel.y);
		render();

	}

}
