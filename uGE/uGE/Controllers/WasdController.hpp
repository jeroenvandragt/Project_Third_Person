#ifndef WASDCONTROLLER_HPP
#define WASDCONTROLLER_HPP
#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

	class WasdController : public Controller
	{
		public:
		    //static glm::vec3 oldPosition;
			WasdController( uGE::GameObject * parent );
			virtual ~WasdController();



            //void onCollision(GameObject * otherGameObject);
			void update();
	};
}
#endif // WASDCONTROLLER_HPP
