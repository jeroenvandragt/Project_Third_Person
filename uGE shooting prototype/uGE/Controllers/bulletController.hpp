#ifndef BULLETCONTROLLER_HPP
#define BULLETCONTROLLER_HPP

#include "Controller.hpp"

namespace uGE {

    class GameObject;
    class bulletController : public Controller
    {
        public:
            bulletController(uGE::GameObject * parent);
            virtual ~bulletController();

            void update();
        protected:
        private:
    };
}

#endif // BULLETCONTROLLER_HPP
