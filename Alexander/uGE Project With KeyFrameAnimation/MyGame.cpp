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
	uGE::SceneManager::add( uGE::Shader::load( "Shaders/basic.vs", "Shaders/basic.fs") ); // load other shader
		uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 10, -10 ) );
		uGE::Light * light = new uGE::Light( "Sun", glm::vec3( 0, 5, -17) );

		uGE::GameObject * floor = new uGE::GameObject( "Floor" );
			uGE::Body * floorBody = new uGE::Body( floor );
				floorBody->setMesh( uGE::AssetManager::loadMesh( "Assets/plane20x20_3200tris.obj" ) );
				floorBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/dirt_1.jpg") );//Red channel
				floorBody->setTexture2( uGE::AssetManager::loadTexture( "Assets/water.jpg") );//Green channel
				floorBody->setTexture3( uGE::AssetManager::loadTexture( "Assets/stone_2.jpg") );//Blue channel
				floorBody->setTexture4( uGE::AssetManager::loadTexture( "Assets/ice_3.jpg") );//Alpha channel
				floorBody->setHeightMap( uGE::AssetManager::loadTexture( "Assets/heightmap.png" ) );
				floorBody->setSplatMap( uGE::AssetManager::loadTexture( "Assets/splat.png" ) );
				floorBody->setShader(uGE::Shader::load( "Shaders/Terrain shader.vs", "Shaders/Terrain shader.fs"));
			floor->setBody( floorBody );

			uGE::GameObject * floor2 = new uGE::GameObject( "Floor2" );
			floor2->setPosition( glm::vec3( 0, 0, -20 ) );
			uGE::Body * floorBody2 = new uGE::Body( floor2 );
				floorBody2->setMesh( uGE::AssetManager::loadMesh( "Assets/plane.obj" ) );
				floorBody2->setTexture1( uGE::AssetManager::loadTexture( "Assets/dirt_1.jpg") );
			floor2->setBody( floorBody2 );
			glm::mat4 & transform = floor2->transform;
            transform = glm::scale( transform, glm::vec3( 10.0f, 1.0f, 10.0f ) );


		uGE::GameObject * player = new uGE::GameObject( "Player" );
		player->setPosition( glm::vec3( 0, 0, -10 ) );
			uGE::Body * playerBody = new uGE::Body( player );
				playerBody->setMesh( uGE::AssetManager::loadMesh( "Assets/teapot.obj" ) );
				playerBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
			player->setBody( playerBody );
			player->setController( new uGE::WasdController( player ) );
			player->setCollider( new uGE::SphereCollider( player , 1.0f ) );
			player->addFrame(uGE::AssetManager::loadMesh( "Assets/Building100.obj" ), 1.0f, "TestChangeStart", "TestChange");
			player->addFrame(uGE::AssetManager::loadMesh( "Assets/Building50.obj" ), 1.0f, "TestChange1", "TestChange");
			player->addFrame(uGE::AssetManager::loadMesh( "Assets/Building0.obj" ), 1.0f, "TestChange2", "TestChange");
			player->addFrame(uGE::AssetManager::loadMesh( "Assets/cube.obj" ), 0.33f, "driveStart", "drive");
			player->addFrame(uGE::AssetManager::loadMesh( "Assets/teapot.obj" ), 0.33f, "drive1", "drive");
			player->addFrame(uGE::AssetManager::loadMesh( "Assets/suzanna.obj" ), 0.33f, "drive2", "drive");


		uGE::GameObject * enemy = new uGE::GameObject( "Enemy" );
			enemy->setPosition( glm::vec3( 0, 0, -15 ) );
			uGE::Body * enemyBody = new uGE::Body( enemy );
				enemyBody->setMesh( uGE::Mesh::load( "Assets/Building100.obj") );
				enemyBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
				enemy->setBody( enemyBody );
				enemy->setController( new uGE::RotateController( enemy ) );
				enemy->setCollider( new uGE::SphereCollider( enemy , 1.0f ) );
				enemy->setPaused(true);
                enemy->addFrame(uGE::AssetManager::loadMesh( "Assets/Building100.obj" ), 1.0f, "FullHPStart", "FullHP");
                enemy->addFrame(uGE::AssetManager::loadMesh( "Assets/Building50.obj" ), 1.0f, "HalfHPStart", "HalfHP");
                enemy->addFrame(uGE::AssetManager::loadMesh( "Assets/Building0.obj" ), 1.0f, "LowHPStart", "LowHP");

		/*uGE::GameObject * enemy2 = new uGE::GameObject( "Enemy2" );
			enemy2->setPosition( glm::vec3( 0, 0, -20 ) );
			uGE::Body * enemyBody2 = new uGE::Body( enemy2 );
				enemyBody2->setMesh( uGE::Mesh::load( "Assets/suzanna.obj") );
				enemyBody2->setTexture1( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
				enemyBody2->setShader(uGE::Shader::load( "Shaders/basic.vs", "Shaders/basic.fs"));
				enemy2->setBody( enemyBody2 );
				enemy2->setController( new uGE::RotateController( enemy2 ) );
				enemy2->setCollider( new uGE::SphereCollider( enemy2 , 1.0f ) );
        */

		camera->setController( new uGE::FollowController( camera, player ) );


	uGE::SceneManager::add( camera );
	uGE::SceneManager::add( light );
	uGE::SceneManager::add( floor );
	uGE::SceneManager::add( floor2 );
	uGE::SceneManager::add( player );
	uGE::SceneManager::add( enemy );
	//uGE::SceneManager::add( enemy2 );

	uGE::SceneManager::setPlayer( player );

	return true; // success
}
