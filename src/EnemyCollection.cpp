#include <EnemyCollection.h>
#include <Spermicide.h>

using namespace std;
using namespace literals;

EnemyCollection::EnemyCollection(const pugi::xml_node& node, b2World& world)
{
	for (auto child : node.children()) {
		float x = child.attribute("x").as_float();
		float y = child.attribute("y").as_float();

		if (child.name() == "Spermicide"sv) {
			
			float endx = child.attribute("endx").as_float();
			float endy = child.attribute("endy").as_float();
			float speed = child.attribute("speed").as_float();
			enemies.push_back(make_unique<Spermicide>(x,y,endx,endy,speed,world));
		}
		else {

			float dirx = child.attribute("dirx").as_float();
			float diry = child.attribute("diry").as_float();
			auto direction = b2Vec2(dirx, diry);
			float speed = child.attribute("speed").as_float();
			enemies.push_back(make_unique<Mycose>(x, y, speed, direction, world));
		}
	}

}


void EnemyCollection::render(sf::RenderWindow& window) const
{
	for (auto const& enemy : enemies) {
		enemy->render(window);
	}

}


bool EnemyCollection::playerContact(Player* player) const
{
	for (auto const& enemy : enemies) {


		if (enemy->getPlayerContact(player)) {
				return true;

		}
	}
	return false;
}

void EnemyCollection::update() const
{

	for (auto const& enemy : enemies) {
		enemy->act();
	}


}


