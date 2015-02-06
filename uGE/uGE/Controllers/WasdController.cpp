#include <SFML/Window.hpp>
#include "WasdController.hpp"
#include "GameObject.hpp"
namespace uGE {

    //glm::vec3 WasdController::oldPosition;

	WasdController::WasdController( uGE::GameObject * parent )
	:	Controller( parent )
	{
	}

	WasdController::~WasdController()
	{

	}

	//void WasdController::onCollision( GameObject * otherGameObject )
    //{
    //    _parent->setPosition( oldPosition );
    //}

	void WasdController::update()
	{
	    //oldPosition = _parent->getPosition();
		glm::mat4 & transform = _parent->transform;
		glm::vec3 translate;
		float rotate = 0.0f;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) translate += glm::vec3( 0,0,0.1 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) translate -= glm::vec3( 0,0,0.1 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) rotate += 0.05;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) rotate -= 0.05;

		// note, does not check collision, just moves on xz plane !
		transform = glm::translate( transform, translate );
		transform = glm::rotate( transform, rotate, glm::vec3( 0,1,0 ) );
	}
}
