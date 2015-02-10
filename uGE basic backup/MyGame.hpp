#ifndef MYGAME_H
#define MYGAME_H

#include "uGE\Game.hpp"

class MyGame : public uGE::Game
{
	public:
		MyGame();
		virtual ~MyGame();

		bool load();

};

#endif // MYGAME_H
