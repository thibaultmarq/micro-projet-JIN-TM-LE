#include "myMain.h"
#include "box2d/box2d.h"
#include <iostream>
#include "pugixml.hpp"
#include "string_view"
#include "Panel.h"
#include "Player.h"
#include <GameManager.h>

using namespace std;
using namespace literals;


int myMain() {
	
	GameManager game;
	game.run();
	return 0;
}
