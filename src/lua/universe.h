#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"

#include "../universe.h"

extern "C" int luaopen_universe(lua_State* lua)
{
	lua_newtable(lua);

	luabridge::getNamespaceFromStack(lua)
		.beginClass<universe>("universe")
			.addFunction("create",&universe::create)
			.addFunction("remove",&universe::remove)
			.addFunction("find",&universe::find)
			.addFunction("rename",&universe::rename)
			.addFunction("change",&universe::change)
			.addFunction("current",&universe::current)
			.addFunction("count",&universe::count)
		.endClass();

	return 1;
}