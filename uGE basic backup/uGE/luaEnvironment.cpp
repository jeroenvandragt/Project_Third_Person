#include "luaEnvironment.hpp"


namespace uGE {

    sf::Mutex mutex; // define mutex // used for locking threads
    lua_State * luaEnvironment::_lua; // set lua_State in the global scope so we can also use it in the update function.
    time_t currentTime; // create variable currentTime
    time_t timeOfActivation; // create variable timeOfActivation
    time_t waitTime; // create variable timeOfActivation
    std::string _message;

    luaEnvironment::luaEnvironment()
	{
		//ctor
	}

	luaEnvironment::~luaEnvironment()
	{
		//dtor
	}

	// String to renderWindow
    int say( lua_State * L )
    {
        // check if lua stack data is a string, if not, throw error
        if( !lua_isstring( L, -2 ) ) throw std::invalid_argument( "function say: expected: string" ); // text
        if( !lua_isnumber( L, -1 ) ) throw std::invalid_argument( "function say: expected: number" ); // timer

        // set lua stack data to actual std::string
        std::string message = lua_tostring( L, -2 );
        // set lua stack data to waitTime (int);
        waitTime = lua_tonumber( L, -1 );

        // set message to global scope
        _message = message;
        // remember when this function is called
        timeOfActivation = time(NULL);

         // there is nothing to return, so return 0;
         return 0;
    }

    // find object by name
    int getObject( lua_State *L )
    {
        // check is lua stack data is a string, if not, throw error
        if( !lua_isstring( L, -1 ) ) throw std::invalid_argument( "function Getobject: expected: string" ); // name

        // set lua stack data to actual std::string
        std::string objectName = lua_tostring( L, -1 );

        // check objects if entered string (from lua) exists, and if so, return the pointer to that object
        for ( auto i = SceneManager::_objects.begin(); i != SceneManager::_objects.end(); ++i )
        {
			GameObject * object = ( GameObject* ) *i;
			if ( object->getName() == objectName )
            {
                lua_pushlightuserdata(L, object);
                return 1;
            }

        }
        // if the object does not exists, return nothing.
        return 0;
    }

    // get X position of "object"
    int getx( lua_State *L )
    {
        if( !lua_islightuserdata( L, -1 ) ) throw std::invalid_argument( "function getx: object not found \n" );
        GameObject *object = (GameObject*)lua_touserdata(L, -1);
        lua_pushnumber(L, object->getPosition().x);
        return 1;
    }

    // Set position ( x,y,z ) of "object"
    int setPosition( lua_State *L )
    {
        // check if there are 4 parameters given, object( name ), x position( number ), y position( number ), z position( number )
       if( !lua_islightuserdata( L, -4 ) ) throw std::invalid_argument( "function setPosition: object not found \n" ); // name
       if( !lua_isnumber( L, -3 ) ) throw std::invalid_argument( "function setPosition: Expected: Value for X" ); // x
       if( !lua_isnumber( L, -2 ) ) throw std::invalid_argument( "function setPosition: Expected: Value for Y" ); // y
       if( !lua_isnumber( L, -1 ) ) throw std::invalid_argument( "function setPosition: Expected: Value for Z" ); // z

       // set lua Stack data to a GameObject * object
       GameObject * object = ( GameObject* )lua_touserdata( L, -4 );

       // create new vec 3 to store new position
       glm::vec3 newPos = glm::vec3 (0,0,0);
       newPos = object->getPosition();
       newPos.x = lua_tonumber( L, -3 ); // store x
       newPos.y = lua_tonumber( L, -2 ); // store y
       newPos.z = lua_tonumber( L, -1 ); // store z

       // set the actual position of the object to the newly stored position
       object->setPosition(newPos);
       return 0;
    }

    // set mesh of "object"
    int setMesh( lua_State *L )
    {
        if ( !lua_islightuserdata( L, -2 ) ) throw std::invalid_argument( "function setMesh: object not found \n" ); // name
        if ( !lua_isstring( L, -1 ) ) throw std::invalid_argument ( "function setMesh: Expected: string" );

        GameObject * object = ( GameObject* )lua_touserdata( L, -2 );
        uGE::Body * objectBody = new uGE::Body( object );

        std::string location = "Assets/";
        std::string fileEnd = ".obj";

        location.append( lua_tostring( L,-1 ) );
        location.append( fileEnd);

        objectBody->setMesh( uGE::AssetManager::loadMesh( location ) );
        //std::cout << object->getName() << "***\n";
        //std::cout << objectBody << "*****\n";
        object->setBody( objectBody );

        return 0;
    }

    // set texture of "object"
    int setTexture( lua_State *L )
    {
        if ( !lua_islightuserdata( L, -2 ) ) throw std::invalid_argument( "function setTexture: object not found \n" ); // name
        if ( !lua_isstring( L, -1 ) ) throw std::invalid_argument ( "function setTexture: Expected: string" );

        std::string location = "Assets/";
        std::string fileEnd = ".jpg";

        location.append( lua_tostring( L,-1 ) );
        location.append( fileEnd);

        GameObject * object = ( GameObject* )lua_touserdata( L, -2 );
        if (object->hasbody == true)
        {
            object->getBody()->setTexture1( uGE::AssetManager::loadTexture( location ) );
        }
        return 0;
    }

    // set Collider of "object"
    int setCollider( lua_State * L )
    {
        if( !lua_islightuserdata( L, -2 ) ) throw std::invalid_argument( "function setCollider: object not found \n" ); // name
        if( !lua_isnumber( L, -1 ) ) throw std::invalid_argument( "function setCollider: Expected: Value" ); // x
        GameObject * object = ( GameObject* )lua_touserdata( L, -2 );
        float colliderRange = lua_tonumber( L, -1);
        object->setCollider( new uGE::SphereCollider( object , colliderRange ) );
        return 0;
    }

    // set Controller of "object"
    int setController( lua_State * L )
    {
        if ( !lua_islightuserdata( L, -1 ) ) throw std::invalid_argument( "function setController: object not found \n" ); // name
        GameObject * object = ( GameObject* )lua_touserdata( L, -1 );
        object->setController( new uGE::RotateController( object ) );
        return 1;
    }

    // create new Object // and put it in _objects[] // array in SceneManager
    int createObject( lua_State *L )
    {
        if (!lua_isstring( L, -1 ) ) throw std::invalid_argument ( "function createObject: Expected: string" );
        std::string name = lua_tostring( L, -1 );
        GameObject * object = new GameObject( name );

        lua_pushlightuserdata( L, object ); // push userdata to lua so we get a pointer to the object
        uGE::SceneManager::add( object ); // put object in sceneManager _objects
        return 1;
    }

    // Destroy /*connection to*/ Object
    int destroyObject( lua_State *L )
    {
        if( !lua_islightuserdata( L, -1 ) ) throw std::invalid_argument ( "function destroyObject: Expected: Object" );
        GameObject * object = (GameObject*)lua_touserdata( L, -1 );
        //delete object;

        // hotFix, should be Delete Object and all pointers to it
        glm::vec3 newPos = glm::vec3 ( -100,-100,-100 );
        object->setPosition( newPos );

        // remove object from _objects and delete
        std::cout << "object removed\n";
        return 0;
    }

    // Pause Thread for given milliseconds
    int waitForSeconds( lua_State *L )
    {
        if( !lua_isnumber( L, -1 ) ) throw std::invalid_argument( "function WaitForSeconds: Expected: Value" );
        int time = lua_tonumber( L, -1 );
        sf::sleep(sf::milliseconds(time));
        return 0;
    }

    // Check collision between "object1" and "Object2"
    int collide( lua_State *L )
    {
        if( !lua_islightuserdata( L, -2 ) ) throw std::invalid_argument ( "function collide: Expected: Object" );
        if( !lua_islightuserdata( L, -1 ) ) throw std::invalid_argument ( "function collide: Expected: Object" );
        GameObject *object1 = (GameObject*)lua_touserdata(L, -2);
        GameObject *object2 = (GameObject*)lua_touserdata(L, -1);

        if( object1->hasCollider() && object2->hasCollider() )
        {
            if( object1->hasCollisionWithLua( object2, 0.5f ) )
            {
                //object1->onCollision(object2);
                //object2->onCollision(object1);
                return 1;
            }
        }
        return 0;
    }

    // Preparing functions for start in FrameWork.lua
    void luaEnvironment::start()
    {
        //mutex.lock(); // Lock thread

        // create new lua_State
        lua_State *lua = luaL_newstate ();
        luaL_openlibs( lua );
        luaL_loadfile( lua, "frameWork.lua" );

        // set lua_State in Global Scope
        _lua = lua;

        //run program and if an error occurs, print it with line and error code
        if ( int errorcode = lua_pcall( lua, 0, LUA_MULTRET, 0 ))
        {
            printf( "Error code: %i\n", errorcode );
            printf( "%s", lua_tostring( lua, -1 ) );
        }
        //------------------------- FUNCTIONS FOR LUA --------------------------------
        lua_pushcfunction( _lua, say );
        lua_setglobal( _lua, "say" );

        lua_pushcfunction( _lua, getObject );
        lua_setglobal( _lua, "getObject" );

        lua_pushcfunction( _lua, getx );
        lua_setglobal( _lua, "getx" );

        lua_pushcfunction( _lua, setPosition );
        lua_setglobal( _lua, "setPosition" );

        lua_pushcfunction( _lua, setMesh );
        lua_setglobal( _lua, "setMesh" );

        lua_pushcfunction( _lua, setTexture );
        lua_setglobal( _lua, "setTexture" );

        lua_pushcfunction( _lua, setCollider );
        lua_setglobal( _lua, "setCollider" );

        lua_pushcfunction( _lua, setController );
        lua_setglobal( _lua, "setController" );

        lua_pushcfunction( _lua, createObject );
        lua_setglobal( _lua, "createObject" );

        lua_pushcfunction( _lua, destroyObject );
        lua_setglobal( _lua, "destroyObject" );

        lua_pushcfunction( _lua, waitForSeconds );
        lua_setglobal( _lua, "waitForSeconds" );

        lua_pushcfunction( _lua, collide );
        lua_setglobal( _lua, "collide" );
        //------------------------- END FUNCTIONS FOR LUA --------------------------------

        // create a Start function in FrameWork.lua
        lua_getglobal( lua, "start" );
        lua_call( _lua, 0, 0 );
        //mutex.unlock(); // unlock Thread
        //lua_close( lua );
    }

    void luaEnvironment::update()
    {
        // create an update function in FrameWork.lua

        // set Current time
        currentTime = time(NULL);

        // Text to screen for say Function
        // if currentTime is less then timeOfActivation + waitTime
        // say to the sceneManager that there is a message to render
        if (currentTime < timeOfActivation + waitTime)
        {
            // tell the SceneManager to set the renderText to the message that was sent from lua
            SceneManager::setRenderText(_message);
        }else // there is no message to render
        {
            SceneManager::setRenderText("");
        }

        mutex.lock();
        lua_getglobal( _lua, "update" ); // ask lua of there is an update function // safety check, if there is no update function in lua, this will crash.
        lua_call( _lua, 0, 0 ); // call the update function
        mutex.unlock();

    }

}
