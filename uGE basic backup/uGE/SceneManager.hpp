#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <SFML/Window.hpp>
#include "Utils/glm.hpp"

namespace uGE {

	class Camera;
	class GameObject;
	class Light;
	class Shader;
	class SceneManager
	{
		private:
			static Camera * _camera;
			static Light * _light;
			static Shader * _shader;
			static Shader * shaderToUse;
			static GameObject * _player;
			static std::vector< GameObject * > _objects;




		public:
			SceneManager();
			virtual ~SceneManager();
			static float clock;


			static void add( Camera * camera );
			static void add( GameObject * object );
			static void add( Light * light );
			static void add( Shader * shader );
			static void setPlayer( GameObject * player );

			static bool control( sf::Window * window );

			static void render( sf::Window * window );
			static void update();

	};
}
#endif // SCENEMANAGER_H
