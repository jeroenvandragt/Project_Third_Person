#include "MyGame.hpp"
#include "uGE/Colliders/SphereCollider.hpp"
#include "uGE/SceneManager.hpp"
#include "uGE/AssetManager.hpp"
#include "uGE/Body.hpp"
#include "uGE/Camera.hpp"
#include "uGE/Controller.hpp"
#include "uGE/GameObject.hpp"
#include "uGE/Light.hpp"
#include "uGE/Mesh.hpp"
#include "uGE/Texture.hpp"
#include "LuaHandler.hpp"
#include "uGE/Controllers/FollowController.hpp"
#include "uGE/Controllers/WasdController.hpp"
#include "uGE/Controllers/RotateController.hpp"


MyGame::MyGame()
{
	//ctor
}

MyGame::~MyGame()
{
	//dtor
}

bool MyGame::load()
{
	uGE::SceneManager::add( uGE::Shader::load( "Shaders/basic.vs", "Shaders/basic.fs") );
		uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 10, -10 ) );
		uGE::Light * light = new uGE::Light( "Sun" , glm::vec3( 0 , 5 , 0 ) );

        //uGE::LuaHandler * lua = new uGE::LuaHandler();
		uGE::GameObject * floor = new uGE::GameObject( "Floor" );
			uGE::Body * floorBody = new uGE::Body( floor );
				floorBody->setMesh( uGE::AssetManager::loadMesh( "Assets/plane20x20_3200tris.obj" ) );
                floorBody->setShader( uGE::Shader::load( "Shaders/Terrain shader.vs", "Shaders/Terrain shader.fs" ) );
				floorBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/dirt_1.jpg") );//Red channel
				floorBody->setTexture2( uGE::AssetManager::loadTexture( "Assets/water.jpg") );//Green channel
				floorBody->setTexture3( uGE::AssetManager::loadTexture( "Assets/stone_2.jpg") );//Blue channel
				floorBody->setTexture4( uGE::AssetManager::loadTexture( "Assets/ice_3.jpg") );//Alpha channel
				floorBody->setHeightMap( uGE::AssetManager::loadTexture( "Assets/heightmap.png" ) );
				floorBody->setSplatMap( uGE::AssetManager::loadTexture( "Assets/splat.png" ) );
			floor->setBody( floorBody );

        uGE::GameObject * floor2 = new uGE::GameObject( "Floor2" );
			uGE::Body * floorBody2 = new uGE::Body( floor2 );
				floorBody2->setMesh( uGE::AssetManager::loadMesh( "Assets/plane20x20_3200tris.obj" ) );
                floorBody2->setShader( uGE::Shader::load( "Shaders/basic.vs", "Shaders/basic.fs" ) );
				floorBody2->setTexture1( uGE::AssetManager::loadTexture( "Assets/water.jpg") );//Red channel
			floor2->setBody( floorBody2 );
			floor2->setPosition( glm::vec3( 0 , 0 , 20 ) );


//--------------------------------------------------------------------------------------------------------------------------------
//                          Teapot
//--------------------------------------------------------------------------------------------------------------------------------
        uGE::GameObject * teapot = new uGE::GameObject( "Teapot" );
			uGE::Body * teapotBody = new uGE::Body( teapot );
				teapotBody->setMesh( uGE::AssetManager::loadMesh( "Assets/teapot.obj" ) );
                teapotBody->setShader( uGE::Shader::load( "Shaders/phong.vs", "Shaders/phong.fs" ) );
				teapotBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/dirt_1.jpg") );//Red channel
			teapot->setBody( teapotBody );
			teapot->setPosition( glm::vec3( -3, 3, 3 ) );
			teapot->setController( new uGE::RotateController(teapot));



//--------------------------------------------------------------------------------------------------------------------------------
//                          PLAYER
//--------------------------------------------------------------------------------------------------------------------------------
			uGE::GameObject * player = new uGE::GameObject( "Player" );
			uGE::Body * playerBody = new uGE::Body( player );
				playerBody->setMesh( uGE::AssetManager::loadMesh( "Assets/teapot.obj" ) );
				playerBody->setShader( uGE::Shader::load( "Shaders/phong.vs", "Shaders/phong.fs" ) );
				playerBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/dirt_1.jpg") );
			player->setBody( playerBody );
			player->setPosition( glm::vec3( 0, 1, 0 ) );
            player->setController( new uGE::WasdController( player ) );
            player->setCollider( new uGE::SphereCollider( player , 1.0f ) );




//--------------------------------------------------------------------------------------------------------------------------------
//                          ENEMY
//--------------------------------------------------------------------------------------------------------------------------------
            uGE::GameObject * enemy = new uGE::GameObject( "Enemy" );
			uGE::Body * enemyBody = new uGE::Body( enemy );
				enemyBody->setMesh( uGE::AssetManager::loadMesh( "Assets/suzanna.obj" ) );
				enemyBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/stone_2.jpg") );//Red channel
				enemyBody->setShader( uGE::Shader::load( "Shaders/floating.vs", "Shaders/floating.fs" ) );
			enemy->setBody( enemyBody );
			enemy->setPosition( glm::vec3( 4 , 1 , 0 ) );
			enemy->setCollider ( new uGE::SphereCollider( enemy , 1.0f ) );
			//enemy->setController( new uGE::RotateController ( enemy ) );

		camera->setController( new uGE::FollowController( camera, player ) );

	uGE::SceneManager::add( camera );
	uGE::SceneManager::add( light );
	uGE::SceneManager::add( floor );
	uGE::SceneManager::add( floor2 );
	uGE::SceneManager::add( teapot );
	uGE::SceneManager::add( player );
	uGE::SceneManager::add( enemy );

	uGE::SceneManager::setPlayer( player );

	return true; // success
}
