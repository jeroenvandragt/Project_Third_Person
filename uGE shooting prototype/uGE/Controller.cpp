#include "Utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"

namespace uGE {

	Controller::Controller( GameObject * parent )
	:	_parent( parent )
	{
		parent->setController( this );
	}

	Controller::~Controller()
	{
	}

	void Controller::update()
	{
        std::cout << "Controller handles update. Should not be here!" << std::endl;
	}

	void Controller::onCollision( GameObject * otherGameObject )
    {
        std::cout << "Controller handles collision. Should not be here!" << std::endl;
    }
}
