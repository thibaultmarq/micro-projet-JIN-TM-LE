#pragma once
#include <vector>
#include "Surface.h"
#include "player.h"
#include "pugixml.hpp"

class Panel {
private:
	std::vector<Surface> level;
public:
	Panel() = default;
	Panel(const pugi::xml_node& node, b2World& world);
	void Render(sf::RenderTarget& window) const;
	void AddSurface(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world);
	SurfaceType checkPlayerTouch(Player* playerBody) const;
	SurfaceType Panel::typeFromString(std::string  const& s);
	void Panel::AddSurfaceBlock(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world);
};