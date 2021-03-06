#include "bulletController.hpp"
#include "GameObject.hpp"
#include <Time.hpp>

namespace uGE {

    //glm::mat4 transform;
    float bulletLifetime = 4.0f;
    sf::Clock clock;

    bulletController::bulletController(uGE::GameObject * parent )
    :	Controller( parent )
    {
       // transform = _transform;

    }

    bulletController::~bulletController()
    {
        //dtor
    }

    void bulletController::update(){
        //glm::mat4 & transform = _parent->transform;
        glm::vec3 translate;
        translate += glm::vec3( 0,0,0.11 );

        //_parent->setPosition(translate);
		_parent->transform = glm::translate( _parent->transform, translate );
        //std::cout << _parent->getName() << std::endl;
		sf::Time elapsed = clock.getElapsedTime();
		if(elapsed.asSeconds() >= 5.0f){
            //std::cout << "time" << std::endl;
		}
    }
}
