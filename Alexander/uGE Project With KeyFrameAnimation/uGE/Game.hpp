#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Body.hpp"
#include "GameObject.hpp"

namespace uGE {

	class GameObject;
	class Shader;

	class Game
	{
		protected:
			sf::RenderWindow * _window;
		public:
			Game();
			virtual ~Game();

			virtual bool load() = 0;
			bool run();

	};
}
#endif // GAME_H
