#pragma once

#include <iostream>
#include <string>

class world
{
	std::string n;
	bool status=false;
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

	void update(size_t t)
	{
		if(t%600)
			return;
		status=!status;
		std::cout<<n<<':'<<(status?"day":"night")<<std::endl;
	}

};