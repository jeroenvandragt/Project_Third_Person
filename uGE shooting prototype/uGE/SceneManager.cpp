#include <iostream>
#include "SceneManager.hpp"
#include <GL/glew.h>

#include "Utils/glm.hpp"
#include "FPS.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "time.hpp"
#include "body.hpp"

namespace uGE {

	Camera * SceneManager::_camera;
	Light * SceneManager::_light;
	Shader * SceneManager::_shader;
	GameObject * SceneManager::_player;
	Shader * SceneManager::shaderToUse;
	float SceneManager::clock = 0;
	sf::Window * SceneManager::_window;

	std::vector< GameObject * > SceneManager::_objects;

	SceneManager::SceneManager()
	{
		//ctor
	}

	SceneManager::~SceneManager()
	{
		//dtor
	}

	void SceneManager::add( Camera * camera )
	{
		_camera = camera;
	}

	void SceneManager::add( GameObject * object )
	{
		_objects.push_back( object );
	}

	void SceneManager::add( Light * light )
	{
		_light = light;
	}

	void SceneManager::add( Shader * shader )
	{
		_shader = shader;
	}

    void SceneManager::setPlayer( GameObject * object )
	{
        _player = object;
	}


	bool SceneManager::control( sf::Window * window )
	{
		sf::Event event;
		while( window->pollEvent( event ) ) { // we must empty the event queue
			if ( event.type == sf::Event::Closed ) {
				return false; // stop the game asap
			}
		}
		return true; // continue running


	}

	sf::Window * SceneManager::getWindowClient(){
        return _window;
	}

	void SceneManager::render( sf::Window * window )
	{
	    _window = window;
        glEnable( GL_DEPTH_TEST ); // must be enabled after after use program
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glm::mat4 parent; // id
        for ( auto i = _objects.begin(); i != _objects.end(); ++i )
        {
            GameObject * object = ( GameObject* ) *i;
            Shader * shaderToUse = NULL;

            if ( object->getBody() != NULL )
            {
                shaderToUse = object->getBody()->getShader();
            }
            if ( shaderToUse == NULL ) shaderToUse = _shader;

            shaderToUse->use();
            shaderToUse->setUniform(shaderToUse->time, Time::now());
            if( _camera ) _camera->render( shaderToUse );
            if( _light ) _light->render( shaderToUse );

            object->render( shaderToUse, parent );


        }
		window->display();
	}



	void SceneManager::update()
	{
	    //_light->setPosition(glm::vec3(4* cos(clock), 5 , 4* sin(clock))) ;
		_camera->update();
		_light->update();
		Time::update();
		FPS::update();
		//std::cout << FPS::getFPS() << std::endl;
        clock = Time::now();
//		for ( auto i = _objects.begin(); i != _objects.end(); ++i )
        for ( int i = 0; i < _objects.size(); ++i )
        {
//			GameObject * object = (GameObject*) *i;
			GameObject * object = _objects[i];
			std::string s = object->getName();
			object->update();

            if( object->hasCollider() )
            {
                if( object->getName() != "Player" )
                {
                    if( _player->hasCollisionWith( object ) )
                    {
                         _player->onCollision(object);
                        object->onCollision(_player);
                        //std::cout << "Collision with: " + object->getName() <<std::endl;
                    }

                }


            }

		}

	}

}
