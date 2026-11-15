#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <mutex>

#include <lua.hpp>

#include "lua/util.h"

class inter
{
	std::deque<std::vector<char>> buffer;
	std::mutex busy;
	lua_State* lua;
public:
	inter(const char* first=nullptr):
		lua(luaL_newstate())
	{
		setvbuf(stdout,nullptr,_IOLBF,0);//fix console out
		luaL_openlibs(lua);
		if(first)
			luaL_dostring(lua,first);
		luaopen_util(lua);

		//shall register new functional there...

	}
	~inter()
	{lua_close(lua);}

	void capture(std::ostream& out,std::istream& in)
	{		
		lua_Writer writer=
		[](lua_State*,const void* from,size_t size,void* dest)
		{
			std::vector<char>* d=(std::vector<char>*)dest;
			d->insert(d->end(),(const char*)from,(const char*)from+size);
			return 0;
		};
		
		while(true)
		{			
			std::string code;
			if(!std::getline(in,code))
				break;
			if(code.empty())
				continue;
			
			busy.lock();
			
			if(luaL_loadstring(lua,code.c_str()))
			{
				out<<lua_tostring(lua,-1)<<std::endl;
				lua_pop(lua,1);
			}
			else
			{
				buffer.push_back(std::vector<char>());
				lua_dump(lua,writer,&buffer.back());
				lua_pop(lua,1);
			}
			
			busy.unlock();
		}
	}

	bool run()
	{
		if(!busy.try_lock())
			return false;
		
		if(buffer.empty())
		{
			busy.unlock();
			return false;
		}
		
		luaL_loadbuffer(lua,buffer.front().data(),buffer.front().size(),"console");
		if(lua_pcall(lua,0,0,0))
		{
			std::cout<<lua_tostring(lua,-1)<<std::endl;
			lua_pop(lua,1);
		}
		buffer.pop_front();
		
		busy.unlock();
		
		return true;
	}
};