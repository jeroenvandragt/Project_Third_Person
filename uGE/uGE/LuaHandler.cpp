#include "LuaHandler.hpp"
#include "GameObject.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "Body.hpp"
#include "lua.hpp"

namespace uGE {

	LuaHandler::LuaHandler()
	{

	}

	LuaHandler::~LuaHandler()
	{
		//dtor
	}

    int say(lua_State *L)
    {
        if(lua_isstring(L, -1))
        {
            std::string message = lua_tostring(L,-1);
            printf("Say: %s\n",message.c_str());
        }
        return 1;
    }

    int createObject(lua_State * L)
    {
        if(lua_isstring(L, -1))
        {
            std::string name = lua_tostring(L,-1);
            printf("Initiated object: %s\n",name.c_str());

            uGE::GameObject * object = new uGE::GameObject( name );
            uGE::Body * objectBody = new uGE::Body( object );
            uGE::SceneManager::add( object );
        }
    }


	int LuaHandler::start()
	{
        lua_State * lua = luaL_newstate();
        luaL_openlibs(lua);
        luaL_loadfile(lua, "HelloWorld.lua");

//-------------------------------------------------------------------------
//                  SAY FUNCTION
//-------------------------------------------------------------------------
        lua_pushcfunction(lua,say);
        lua_setglobal(lua, "say");

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//                  CREATEOBJECT FUNCTION
//-------------------------------------------------------------------------
        lua_pushcfunction(lua,createObject);
        lua_setglobal(lua, "createObject");

//-------------------------------------------------------------------------


        lua_call(lua,0,0);
        lua_close(lua);

        return 0;
	}
}
