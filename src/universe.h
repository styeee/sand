#pragma once

#include <string>
#include <unordered_map>

#include "world.h"

class universe
{
	//be careful with world* !
	std::unordered_map<std::string,world*> worlds;
	world* cur=nullptr;

public:

	~universe()
	{
		for(auto& [n,w]:worlds)
			delete w;
	}
	//rule of 5
	universe()=default;
	universe(const universe&)=delete;
	universe(universe&&)=delete;
	universe& operator=(const universe&)=delete;
	universe& operator=(universe&&)=delete;

	bool create(const std::string& name)
	{
		if(worlds.count(name))
			return false;
		
		worlds[name]=new world(name);
		return true;
	}

	bool remove(const std::string& name)
	{
		auto it=worlds.find(name);
		
		if(it==worlds.end())
			return false;

		if(it->second==cur)
			cur=nullptr;

		delete it->second;
		worlds.erase(it);
		return true;
	}

	world* find(const std::string& name)
	{
		auto it=worlds.find(name);
		
		if(it==worlds.end())
			return nullptr;

		return it->second;
	}

	bool rename(const std::string& old,const std::string name)
	{
		if(worlds.count(name))
			return false;
		
		auto it=worlds.find(old);
		
		if(it==worlds.end())
			return false;
		
		worlds[name]=it->second;
		it->second->rename(name);
		worlds.erase(it);
		return true;
	}

	template <typename caller>
	void each(caller&& f)
	{
		for(auto& [n,w]:worlds)
			f(*w);	
	}

	size_t count()const
	{return worlds.size();}

	world* current()
	{return cur;}
	bool change(const std::string& name)
	{
		world* w=find(name);
		
		if(!w)
			return false;
		
		cur=w;
		return true;
	}
};
