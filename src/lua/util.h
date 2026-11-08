#pragma once

#include <lua.hpp>

extern "C" int luaopen_util(lua_State* lua)
{
	lua_register
	(
		lua,
		"test_f",
		[](lua_State* lua)
		{
			luaL_dostring(lua,"print([[test]])");
			return 0;
		}
	);
	
	return 0;
}