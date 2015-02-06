#ifndef LUA_H
#define LUA_H

#include "GameObject.hpp"

namespace uGE {


	class LuaHandler
	{
		public:
			LuaHandler( );
			virtual ~LuaHandler();

			int start( );
	};
}
#endif // LUA_H
