#include <SFML/Window.hpp>
#include "WasdController.hpp"
#include "GameObject.hpp"

namespace uGE {

    glm::vec3 WasdController::oldPosition;

	WasdController::WasdController( uGE::GameObject * parent )
	:	Controller( parent )
	{
	}

	WasdController::~WasdController()
	{

	}

	void WasdController::update()
	{
		glm::mat4 & transform = _parent->transform;
		glm::vec3 translate;
		// set position into oldPosition, in case of collision, reset to this
		oldPosition = _parent->getPosition();
		float rotate = 0.0f;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) translate += glm::vec3( 0,0,0.11 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) translate -= glm::vec3( 0,0,0.11 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) rotate += 0.05;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) rotate -= 0.05;

        if(translate != glm::vec3(0,0,0))
        {
            _parent->setCycle("drive");
        }
        else _parent->setCycle("TestChange");

		// note, does not check collision, just moves on xz plane !
		transform = glm::translate( transform, translate );
		transform = glm::rotate( transform, rotate, glm::vec3( 0,1,0 ) );
	}

	void WasdController::onCollision( GameObject * otherGameObject )
	{
        _parent->setPosition( oldPosition );
	}
}
