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
			save.saveToDisk();
			window.close();
			break;

		default:
			break;
		}

	}


}

void GameManager::update(sf::Time elapsedTime)
{	
	SurfaceType surface = panel.checkPlayerTouch(&player);
	panel.test();
	player.getBody()->SetGravityScale(1);

	if (player.getCoordinates().y < -300 ) {
		if (victory.getStatus()==sf::Sound::Stopped)
			victory.play();
		save.addScore(-player.getCoordinates().y);

		std::string res = "Best scores :\n";
		std::vector<float> scores = save.getScores();

		for (auto const& score : scores) {

			res.append(std::to_string(score));
			res.append("\n");

		}

		scoreText.setString(res);

		displayTime = 0;
		player.testTeleport(10, -0.5);
	}
	printf("%d\n", shoulddie);
	b2Vec2 vel = player.getVelocity();
	switch (surface)
	{
	case SurfaceType::DRY:


		

		if (vel.x == 0 && vel.y == 0) {
			if ( death[soundState].getStatus() == sf::Sound::Stopped) {
				death[soundState].play();

			}
			float y = player.getCoordinates().y;
			save.addScore(-y);
			
			std::string res = "Best scores :\n";
			std::vector<float> scores = save.getScores();

			for (auto const& score : scores) {

				res.append(std::to_string(score));
				res.append("\n");

			}

			scoreText.setString(res);

			displayTime = 0;
			player.testTeleport(10, -0.5);

			break;
		}
		break;

	case SurfaceType::SWIMMABLE:
		shoulddie = 0;
		if (lastSurface != SurfaceType::SWIMMABLE && splurch[soundState].getStatus() == sf::Sound::Stopped) {
			splurch[soundState].play();

		}
		
		
		/*
		for (auto const& input : inputList) {
			
			if (commandMap.find(input) != commandMap.end())
				commandMap[input]->execute(player, playerSpeed);
				
		}
		
		*/
		player.getBody()->SetGravityScale(0.5);
		if (left)
			player.setVelocity(-playerSpeed, 0);
		if (right)
			player.setVelocity(playerSpeed, 0);
		if (jump)
			player.setVelocity(0,playerSpeed*4);
			
		break;

	case SurfaceType::TOUCHABLE:


		if (vel.x == 0 && vel.y == 0) {
			shoulddie++;
			
		}
		if (shoulddie > 60) {
			if (lastSurface != SurfaceType::DRY && death[soundState].getStatus() == sf::Sound::Stopped) {
				death[soundState].play();

			}
			float y = player.getCoordinates().y;
			save.addScore(-y);

			std::string res = "Best scores :\n";
			std::vector<float> scores = save.getScores();

			for (auto const& score : scores) {

				res.append(std::to_string(score));
				res.append("\n");

			}

			scoreText.setString(res);

			displayTime = 0;
			player.testTeleport(10, -0.5);
			
			shoulddie = 0;
			
		}
		if (lastSurface != SurfaceType::TOUCHABLE && bump.getStatus() == sf::Sound::Stopped) {
			bump.play();
		}

		break;
	}

	//inputList.clear();

	lastSurface = surface;

	b2Vec2 cur_coords = player.getCoordinates();

	player.setCoordinates(cur_coords.x, cur_coords.y);

}

void GameManager::render()
{
	window.clear();
	
	panel.render(window);
	player.render(window);
	b2Vec2 pos = player.getCoordinates();
	view.setCenter(10, pos.y);

	window.setView(view);

	if (displayTime < 3) {
		window.draw(scoreText);
		displayTime += TimePerFrame.asSeconds();
	}

	window.display();
}

void GameManager::handleInputs(sf::Keyboard::Key key, bool keyState)
{
	/*
	if (keyState)
		inputList.insert(key);
	else
		inputList.erase(key);
	*/

	if (key == sf::Keyboard::Q)
		left = keyState;
	else if (key == sf::Keyboard::D)
		right = keyState;
	else if (key == sf::Keyboard::Z || key == sf::Keyboard::Space)
		jump = keyState;
	else if (key == sf::Keyboard::N)
		soundState = 0;
	else if (key == sf::Keyboard::W)
		soundState = 1;

}


void GameManager::run()
{

	sf::Font font;
	font.loadFromFile("resources/arial.ttf");
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::Blue);
	scoreText.setCharacterSize(10);
	scoreText.setScale(sf::Vector2f(0.1f, 0.1f));
	scoreText.setPosition(5, -10);

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	view.setSize(20,20);

	commandMap[sf::Keyboard::Q] = std::make_unique<MoveLeftCommand>();
	commandMap[sf::Keyboard::D] = std::make_unique<MoveRightCommand>();
	commandMap[sf::Keyboard::Z] = std::make_unique<JumpCommand>();
	commandMap[sf::Keyboard::Space] = std::make_unique<JumpCommand>();
	
	pugi::xml_document doc;
	auto result = doc.load_file("resources/level.xml");
	if ( !result)
	{
		std::cerr << "Could not open file visage.xml because " << result.description() << std::endl;
		return ;
	}
	panel= Panel{ doc.child("Level"), world};


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
	splurch[0].setVolume(50);

	splurch[1].setBuffer(bufferSplurch.second);
	splurch[1].setVolume(30);

	if (!bufferBump.loadFromFile("resources/bump.mp3")) {
		printf("Bump didn't load !\n");
		window.close();
	}
	bump.setBuffer(bufferBump);
	bump.setVolume(30);

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
	


	while (window.isOpen()) {

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(timeSinceLastUpdate);
			world.Step(TimePerFrame.asSeconds(), 6, 2);
		}

		render();

	}

}

