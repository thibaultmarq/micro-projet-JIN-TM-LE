#include "myMain.h"
#include <iostream>
#include "pugixml.hpp"
#include "string_view"
#include "Panel.h"
#include "Player.h"

using namespace std;
using namespace literals;


int myMain() {
	sf::RenderWindow mWindow;
	mWindow.create(sf::VideoMode(800, 600), "My window");
    Panel panel;
    b2Vec2 gravity(0.0f,1.0f);
    b2World world(gravity);
    //panel.AddSurface(5, 5, 50,50, SurfaceType::DRY, world);
    panel.AddSurface(0, 500,500,10, SurfaceType::SWIMMABLE, world);
    Player player;
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    while (mWindow.isOpen())
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }
        mWindow.clear(sf::Color::White);
        panel.Render(mWindow);
        mWindow.display();
    }
	return 0;
}
