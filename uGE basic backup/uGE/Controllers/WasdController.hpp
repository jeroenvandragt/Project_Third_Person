#ifndef WASDCONTROLLER_HPP
#define WASDCONTROLLER_HPP
#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

	class WasdController : public Controller
	{
        private:
            static glm::vec3 oldPosition;

		public:
			WasdController( uGE::GameObject * parent );
			virtual ~WasdController();

			void update();
			void onCollision( GameObject * otherGameObject );
	};
}
#endif // WASDCONTROLLER_HPP
