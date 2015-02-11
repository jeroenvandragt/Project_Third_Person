#include <SFML/Window.hpp>
#include "RotateController.hpp"
#include "Utils/glm.hpp"

#include "GameObject.hpp"
namespace uGE {

	RotateController::RotateController( uGE::GameObject * parent )
	:	Controller( parent )
	{
		//ctor
	}

	RotateController::~RotateController()
	{
		//dtor
	}

	void RotateController::update()
	{
		glm::mat4 & transform = _parent->transform;
		transform = glm::rotate( transform, 0.01f, glm::vec3( 0,1,0 ) );

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::G ) ) _parent->setFrame("FullHP");
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::H ) ) _parent->setFrame("HalfHP");
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::J ) ) _parent->setFrame("LowHP");
	}

	void RotateController::onCollision( GameObject * otherGameObject )
	{
	    //delete this;
        std::cout << "collision part of " + _parent->getName() + "\n";

	}
}
