#include "bulletController.hpp"
#include "GameObject.hpp"

namespace uGE {

    bulletController::bulletController(uGE::GameObject * parent)
    :	Controller( parent )
    {
        //ctor
    }

    bulletController::~bulletController()
    {
        //dtor
    }

    void bulletController::update(){
        glm::mat4 & transform = _parent->transform;
        glm::vec3 translate;
        translate += glm::vec3( 0,0,0.11 );

		transform = glm::translate( transform, translate );
    }
}
