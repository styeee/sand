#pragma once

#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"

#include "../world.h"

extern "C" int luaopen_world(lua_State* lua)
{
	lua_newtable(lua);

	luabridge::getNamespaceFromStack(lua)
		.beginClass<world>("world")
			.addFunction("name",&world::name)
			.addFunction("rename",&world::rename)
			.addFunction("info",&world::info)
		.endClass();

	return 1;
}