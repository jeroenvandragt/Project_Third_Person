#include "FollowController.hpp"
#include "GameObject.hpp"
namespace uGE {
	FollowController::FollowController( uGE::GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
	}

	FollowController::~FollowController()
	{
		//dtor
	}

	void FollowController::update()
	{
		glm::mat4 & transform = _parent->transform;
		transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
	}
}
