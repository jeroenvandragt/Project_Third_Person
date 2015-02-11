#ifndef LUAENVIRONMENT_HPP
#define LUAENVIRONMENT_HPP

#include <iostream> // std::cout
#include <stdexcept> // std::invalid_argument
#include <windows.h> //

#include <lua.hpp>

#include "utils/glm.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "Body.hpp"
#include "../Colliders/SphereCollider.hpp"
#include "../Controllers/FollowController.hpp"
#include "../Controllers/WasdController.hpp"
#include "../Controllers/RotateController.hpp"
#include "time.hpp"



namespace uGE {

    class luaEnvironment
    {
        private:
            static lua_State * _lua;

        public:
            luaEnvironment();
            virtual ~luaEnvironment();
            static void start();
            static void update();
    };

}


#endif // LUAENVIRONMENT_HPP
