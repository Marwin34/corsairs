#include "game.hpp"
#include <time.h>

int main()
{
	std::srand(std::time(NULL));

	Game game;
	game.start();

	return 0;
}