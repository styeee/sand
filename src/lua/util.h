#pragma once

#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"

class test_c
{
	int x;
public:
	test_c(int x)
	:
		x(x)
	{}
	
	int get()const
	{
		return x;
	}
};

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
	
	luabridge::getGlobalNamespace(lua)
		.beginClass<test_c>("test_c")
			.addConstructor<void(*)(int)>()
			.addFunction("get", &test_c::get)
		.endClass();
	
	return 0;
}