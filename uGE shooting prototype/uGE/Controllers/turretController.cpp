#include "turretController.hpp"
#include "Utils/glm.hpp"
#include <iostream>
#include <windows.h>
#include <Time.hpp>

#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "bulletController.hpp"
#include "Colliders/SphereCollider.hpp"
#include "../uGE/SceneManager.hpp"
#include "../uGE/AssetManager.hpp"
#include "../uGE/Body.hpp"
#include "../uGE/Camera.hpp"
#include "../uGE/Controller.hpp"

#include "../uGE/Light.hpp"
#include "../uGE/Mesh.hpp"
#include "../uGE/Texture.hpp"


namespace uGE {

    float maxLeftSpeed = 0.03f;
    float maxRightSpeed = -0.03f;
    float startLeftSpeed = 0.01f;
    float startRightSpeed = -0.01f;

    float bulletTimer = 0.0f;
    float reloadTimer = 5.0f;
    bool hasShot = false;



    turretController::turretController(uGE::GameObject * parent)
    :	Controller( parent ), window(0)
    {
        window = SceneManager::getWindowClient();
    }

    turretController::~turretController()
    {
        //dtor
    }

    void turretController::startClock(int timeMilli){



    }

    void turretController::update()
	{

	    if(hasShot == true){
            //timer.restart();
            sf::Time elapsed = timer.getElapsedTime();
            std::cout << elapsed.asSeconds() << std::endl;
            if(elapsed.asMilliseconds() >= 20){
                hasShot = false;
                std::cout << elapsed.asMilliseconds() << std::endl;
            }
	    }
		glm::mat4 & transform = _parent->transform;
        if(hasShot == false){
            if (sf::Keyboard::isKeyPressed( sf::Keyboard::Space )){
                std::cout << "key pressed" << std::endl;
                uGE::GameObject * bullet = new uGE::GameObject( "Bullet" );
                bullet->setPosition( glm::vec3( 0, 0, 0 ) );
                uGE::Body * bulletBody = new uGE::Body( bullet );
                    bulletBody->setMesh( uGE::AssetManager::loadMesh( "Assets/bullet.obj" ) );
                    bulletBody->setTexture1( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
                bullet->setBody( bulletBody );
                _parent->addChild(bullet);
                bullet->setController( new uGE::bulletController( bullet ) );
                bullet->setCollider( new uGE::SphereCollider( bullet , 1.0f ) );
                hasShot = true;
                sf::Clock timer;
            }
        }

		if (sf::Keyboard::isKeyPressed( sf::Keyboard::Left )){
            transform = glm::rotate( transform, startLeftSpeed, glm::vec3( 0,1,0 ) );
            if(startLeftSpeed <= maxLeftSpeed){
                startLeftSpeed *= 1.05f;
            }
		}
		else if(sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) == false){
            if(startLeftSpeed >= 0.01f){
                transform = glm::rotate( transform, startLeftSpeed, glm::vec3( 0,1,0 ) );
                startLeftSpeed *= 0.9f;
            }
            else if(startLeftSpeed <= 0.01f) startLeftSpeed = 0.009f;
		}

		if (sf::Keyboard::isKeyPressed( sf::Keyboard::Right )){
            transform = glm::rotate( transform, startRightSpeed, glm::vec3( 0,1,0 ) );
            if(startRightSpeed >= maxRightSpeed){
                startRightSpeed *= 1.1f;
            }
		}

		else if(sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) == false){
		    //std::cout << "key is not pressed" << std::endl;
            if(startRightSpeed <= -0.01f){
                transform = glm::rotate( transform, startRightSpeed, glm::vec3( 0,1,0 ) );
                startRightSpeed *= 0.9f;
            }
            else if(startRightSpeed >= -0.01f) startRightSpeed = -0.009f;
		}
		/*std::cout << startRightSpeed << std::endl;
		POINT p;
		if(GetCursorPos(&p)){
            std::cout << p.x << std::endl;

		}*/
	}

}
