#pragma once
#include <vector>
#include "Surface.h"
#include "player.h"

class Panel {
private:
	std::vector<Surface> level;
public:
	Panel() = default;
	void Render(sf::RenderTarget& window) const;
	void AddSurface(float x, float y, float h, float w, SurfaceType surfaceType, b2World& world);
	SurfaceType checkPlayerTouch(Player* playerBody) const;
};