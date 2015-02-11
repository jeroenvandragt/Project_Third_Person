#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>

#include <vector>
#include <SFML/Window.hpp>
#include "Utils/glm.hpp"
#include <GL/glew.h>

#include "luaEnvironment.hpp"

#include "Camera.hpp"
#include "GameObject.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "time.hpp"
#include "body.hpp"

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


		public:
			SceneManager();
			virtual ~SceneManager();
			static float clock;
			static std::vector< GameObject * > _objects;

			static void add( Camera * camera );
			static void add( GameObject * object );
			static void add( Light * light );
			static void add( Shader * shader );
			static void setPlayer( GameObject * player );
			static void setRenderText(std::string _renderText);

			static bool control( sf::RenderWindow * window );

			static void render( sf::RenderWindow * window );
			static void update();

	};
}
#endif // SCENEMANAGER_H
