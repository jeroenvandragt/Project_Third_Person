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
#include "uGE/Controllers/turretController.hpp"


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
		uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 3, -10 ) );
		uGE::Light * light = new uGE::Light( "Sun", glm::vec3( 0, 5, 0) );

		uGE::GameObject * floor = new uGE::GameObject( "Floor" );
			uGE::Body * floorBody = new uGE::Body( floor );
				floorBody->setMesh( uGE::AssetManager::loadMesh( "Assets/plane20x20_3200tris.obj" ) );
				floorBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/dirt_1.jpg") );//Red channel
			floor->setBody( floorBody );



		uGE::GameObject * player = new uGE::GameObject( "Player" );
		player->setPosition( glm::vec3( 0, 0, -5 ) );
			uGE::Body * playerBody = new uGE::Body( player );
				playerBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Body.obj" ) );
				playerBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
			player->setBody( playerBody );
			player->setController( new uGE::WasdController( player ) );
			player->setCollider( new uGE::SphereCollider( player , 1.0f ) );

		uGE::GameObject * turret = new uGE::GameObject( "Turret" );
			turret->setPosition( glm::vec3( 0, 0.0f, 0 ) );
			uGE::Body * turretBody = new uGE::Body( turret );
				turretBody->setMesh( uGE::Mesh::load( "Assets/Turret.obj") );
				turretBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
				turret->setBody( turretBody );
				player->addChild(turret);
				turret->setController( new uGE::turretController( turret ) );
				turret->setCollider( new uGE::SphereCollider( turret , 1.0f ) );


		camera->setController( new uGE::FollowController( camera, player ) );


	uGE::SceneManager::add( camera );
	uGE::SceneManager::add( light );
	uGE::SceneManager::add( floor );
	uGE::SceneManager::add( player );
	//uGE::SceneManager::add( turret );


	uGE::SceneManager::setPlayer( player );

	return true; // success
}
