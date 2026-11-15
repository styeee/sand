#include <iostream>
#include <thread>

#include "../loop.h"
#include "../universe.h"
#include "../inter.h"

universe u;
inter i;

bool handle(size_t t)
{
	u.current()->update(t);
	
	if(i.run())
		return true;
	
	return true;
}

int main()
{
	i.shared<universe>(u,"R");
	
	std::thread
	(
		&inter::capture,
		&i,
		std::ref(std::cout),
		std::ref(std::cin)
	)
	.detach();
	
	u.create("first");
	u.change("first");
		
	loop l;
	l.handle(handle);
	l.run();
	
	return 0;
}
