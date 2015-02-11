#include "Game.hpp"
#include "SceneManager.hpp"

namespace uGE {

	Game::Game()
	:	_window ( new sf::RenderWindow( sf::VideoMode( 800, 600), "Saxion uGE Game" ) )
	{
		_window->setVerticalSyncEnabled( true );
		std::cout << "Init Glew " << glewInit() << " GL : " << glGetString( GL_VERSION ) << std::endl;
		std::cout << "Max textures size " << GL_MAX_TEXTURE_SIZE << std::endl;
		std::cout << "GLSL version " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;


		glEnable( GL_DEPTH_TEST );
		glClearColor( 0.1f, 0.1f, 0.3f, 1.0f );
	}

	Game::~Game()
	{
		_window->close();
	}

	bool Game::run()
	{
		bool running = true;
		while ( running ) {
			running = SceneManager::control( _window );
			SceneManager::update();
			SceneManager::render( _window );

			if (sf::Keyboard::isKeyPressed( sf::Keyboard::Escape )) running = false;

		}
		return true;
	}
}
