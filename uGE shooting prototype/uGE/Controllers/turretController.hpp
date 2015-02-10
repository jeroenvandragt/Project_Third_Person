#ifndef TURRETCONTROLLER_HPP
#define TURRETCONTROLLER_HPP

#include "Controller.hpp"
#include <SFML/Window.hpp>

namespace uGE {

    class GameObject;
    class turretController : public Controller
    {
         private:
            sf::Window * window;

        public:
            turretController(uGE::GameObject * parent);
            virtual ~turretController();

            void update();
        protected:
        private:
    };
}

#endif // TURRETCONTROLLER_HPP
