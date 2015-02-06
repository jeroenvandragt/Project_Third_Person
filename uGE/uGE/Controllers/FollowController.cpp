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

		glm::vec3 newTargetPos = _followee->getPosition();
		glm::vec3 oldCamPos = _parent->getPosition();
		glm::vec3 dir = newTargetPos - oldCamPos;
		glm::vec3 normDir = glm::normalize(dir);
		glm::vec3 newCam = newTargetPos - (10.0f * normDir);
        newCam.y = 8.0f;
		transform = glm::inverse(glm::lookAt(newCam, newTargetPos, glm::vec3(0,1,0)));

		// old lookat transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
		//std::cout << _followee->getPosition() << std::endl;
	}
}
