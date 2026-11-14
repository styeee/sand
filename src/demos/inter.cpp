#include <iostream>
#include <thread>
#include "../inter.h"
#include "../timer.h"

int main(int argc,char** argv)
{
	setvbuf(stdout,nullptr,_IONBF,0);

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
		if(!i.run());
	
	return 0;
}