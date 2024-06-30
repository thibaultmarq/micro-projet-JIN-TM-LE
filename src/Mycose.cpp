#include "Mycose.h"


using namespace std;

Mycose::Mycose(float x, float y, float spd, b2Vec2 direction, b2World& world)
	: Enemy{ x,y,world },
	speed{ spd },
	world { world },
	direction { direction }

{

	target.setFillColor(sf::Color::Blue);
}

void Mycose::act()
{
	frameBeforeNextSpawn--;
	if (frameBeforeNextSpawn < 0) {
		frameBeforeNextSpawn = 300;
		b2Vec2 position = enemyBody->GetPosition();

		bullets.push_back(make_unique<Bullet>(position, direction, world));
	}

}

void Mycose::render(sf::RenderWindow& window) {
	b2Vec2 pos = enemyBody->GetPosition();
	target.setPosition(pos.x, pos.y);
	window.draw(target);

	for (auto const& child : bullets) {
		child->render(window);
	}
}