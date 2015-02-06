#ifndef FOLLOWCONTROLLER_H
#define FOLLOWCONTROLLER_H

#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

	class FollowController : public Controller
	{
		private:
			GameObject * _followee;
		public:
			FollowController( GameObject * parent, GameObject * followee );
			virtual ~FollowController();

			void update();
	};
}
#endif // FOLLOWCONTROLLER_H
