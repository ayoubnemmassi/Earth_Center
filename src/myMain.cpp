#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include <time.h>
#include "Game.h"
using namespace sf;
using namespace std;


int myMain()
{

srand(time_t(static_cast<time_t>(0)));
Game game;
game.run();
return 0;
}
	