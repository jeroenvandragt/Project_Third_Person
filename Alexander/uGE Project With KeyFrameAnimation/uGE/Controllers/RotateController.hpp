#ifndef ROTATECONTROLLER_H
#define ROTATECONTROLLER_H

#include "Controller.hpp"

namespace uGE {

	class GameObject;
	class RotateController : public Controller {
		public:
			RotateController( uGE::GameObject * parent );
			virtual ~RotateController();

			void update();
			void onCollision( GameObject * otherGameObject );

	};
}
#endif // ROTATECONTROLLER_H
