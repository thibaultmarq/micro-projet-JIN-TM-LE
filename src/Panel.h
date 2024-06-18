#pragma once
#include <vector>

#include "player.h"
#include "pugixml.hpp"
#include "StaticSurface.h"
#include "MovingSurface.h"

class Panel {
private:
	std::vector<std::unique_ptr<Surface>> level;
public:
	Panel() = default;
	Panel(const pugi::xml_node& node, b2World& world);
	void render(sf::RenderTarget& window) const;
	void addSurface(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world);
	void addSurface(b2Vec2 coord, b2Vec2 maxCoord, b2Vec2 size, SurfaceType surfaceType, b2World& world);
	void test();
	SurfaceType checkPlayerTouch(Player* playerBody) const;
	SurfaceType typeFromString(std::string  const& s) const;
	void addStaticBlock(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world);
	void addMovingBlock(b2Vec2 coord, b2Vec2 maxCoord, b2Vec2 size, SurfaceType surfaceType, b2World& world);
};