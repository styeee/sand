#pragma once
#include <iostream>

#include <string>

class world
{
	std::string n;
public:
	world(const std::string& n)
	:
		n(n)
	{}

	const std::string& name()const
	{
		return n;
	}
	void rename(const std::string& name)
	{n=name;}
};