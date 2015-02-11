#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>

#include "Body.hpp"
#include "GameObject.hpp"


namespace uGE {

    //class Hud;
	class GameObject;
	class Shader;

	class Game
	{
		protected:
			sf::Window * _window;
        private:
            //Hud * hud;
		public:
			Game();
			virtual ~Game();

			virtual bool load() = 0;
			bool run();

	};
}
#endif // GAME_H
