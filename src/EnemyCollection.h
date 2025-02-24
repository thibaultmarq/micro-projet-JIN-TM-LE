#pragma once

#include <vector>
#include <box2d/box2d.h>
#include <pugixml.hpp>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Enemy.h>
#include "Mycose.h"

class EnemyCollection {

public:
	EnemyCollection() = default;
	EnemyCollection(const pugi::xml_node& node, b2World& world);
	void render(sf::RenderWindow& window) const;
	//void addEnemy(float x, float y, b2World& world);
	bool playerContact(Player* player) const;
	void update() const;

private:

	std::vector<std::unique_ptr<Enemy>> enemies;



};