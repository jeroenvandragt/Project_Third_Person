#include <iostream>

#include "MyGame.hpp"

int main()
{

	MyGame * game = new MyGame();
	game->load();
	game->run();
	std::cout << "Hello Devs UGE Running" << std::endl;
	return 0;
}
