#include <iostream>
#include <thread>
#include "../inter.h"
#include "../timer.h"

int main(int argc,char** argv)
{
	inter i;
	std::thread
	(
		&inter::capture,
		&i,
		std::ref(std::cout),
		std::ref(std::cin)
	)
	.detach();
	
	while(true)
		if(!i.run())
			timer::wait(.001);
	
	return 0;
}