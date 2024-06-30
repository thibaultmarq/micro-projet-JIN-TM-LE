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
		direction.Normalize();
		direction *= size;
		b2Vec2 position = enemyBody->GetPosition() + direction;

		bullets.push_back(make_unique<Bullet>(position, direction, world));
	}
	for (auto const& child : bullets) { // voir getPlayerContact: on n'arrive pas à faire en sorte de les détruires quand ils touchent des murs, donc on doit hardcoder
		if (child->getBody()->GetPosition().x < 0 || child->getBody()->GetPosition().x > 30 || child->getBody()->GetPosition().y < -20 || child->getBody()->GetPosition().y > 350) {
			auto it = ranges::find(bullets.begin(), bullets.end(),child);
			if (it != bullets.end()) {
				bullets.erase(it);
				break;
			}
		}
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

bool Mycose::getPlayerContact(Player* player) {


	for (auto const& child : bullets) {
		b2ContactEdge const* contactList = child->getBody()->GetContactList();

		if (contactList != nullptr && contactList->other == player->getBody()) {
			auto it = ranges::find(bullets.begin(), bullets.end(),
				child);
			if (it != bullets.end()) {
				bullets.erase(it);
			}
			return true;

		}

		if (contactList != nullptr) { // Ce bout de code de fonctionne pas: la contactlist est vide même lorsqu'un mur est touché, et on ne comprend pas pourquoi
			auto it = ranges::find(bullets.begin(), bullets.end(),
				child);

			if (it != bullets.end()) {
				bullets.erase(it);
			}
		}
	}
	b2ContactEdge const* contactList = enemyBody->GetContactList();

	if (contactList != nullptr && contactList->other == player->getBody()) {
		return true;

	}
	return false;


}