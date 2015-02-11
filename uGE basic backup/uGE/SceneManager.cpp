#include "SceneManager.hpp"


namespace uGE {

	Camera * SceneManager::_camera;
	Light * SceneManager::_light;
	Shader * SceneManager::_shader;
	GameObject * SceneManager::_player;
	Shader * SceneManager::shaderToUse;
	//float SceneManager::clock = 0;

	sf::Thread * myLuaThread;//variable cannot go out of scope
	std::string _renderText;

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

	void SceneManager::setRenderText( std::string renderText )
	{
	 _renderText = renderText;
	}


	bool SceneManager::control( sf::RenderWindow * window )
	{
		sf::Event event;
		while( window->pollEvent( event ) ) { // we must empty the event queue
			if ( event.type == sf::Event::Closed ) {
				return false; // stop the game asap
			}
		}
		return true; // continue running


	}

	void SceneManager::render( sf::RenderWindow * window )
	{
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

        // Render Window stuff
        // Declare and load a font
        sf::Font font;
        font.loadFromFile( "VTKS FUTURE.ttf" );
        // Create a text which uses our font
        sf::Text text;
        text.setString( std::string( "hello" ) );
        text.setFont( font );
        text.setCharacterSize( 20 );
        text.setStyle(sf::Text::Bold);
        text.setColor(sf::Color::Yellow);
        text.setPosition( 20, 15 );
        text.setString(_renderText);

        // Declare and set shape
        sf::RectangleShape rectangle( sf::Vector2f( 500, 70 ) );
        rectangle.setFillColor( sf::Color( 200, 200, 200, 200 ));
        rectangle.setOutlineThickness( 10 );
        rectangle.setOutlineColor( sf::Color( 100, 100, 100, 200 ) );
        rectangle.setPosition( 15, 15 );


        // adding text to screen
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glDisableVertexAttribArray( 0 );
        window->pushGLStates();
        if (text.getString() != "")
        {
            window->draw( rectangle );
        }

        window->draw( text );
        window->popGLStates();

        // -------------



		window->display();
	}

	void SceneManager::update()
	{
	    // luaEnvironment::update() in new thread
	    //myLuaThread = new sf::Thread(&uGE::luaEnvironment::update); // prepare thread
       // myLuaThread->launch(); // begin thread

        // Light rotation
	    //_light->setPosition(glm::vec3(4* cos(clock), 5 , 4* sin(clock)-20)) ;

		// update functions
		_camera->update();
		_light->update();
		Time::update();
        //clock = Time::now();

        // collision check between Player and "object"
		for ( auto i = _objects.begin(); i != _objects.end(); ++i )
        {
			GameObject * object = (GameObject*) *i;


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
            object->update();

		}

	}

}
