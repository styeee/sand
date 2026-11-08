#include <iostream>
#include <stdlib.h>//atoi
#include "../loop.h"

int end=10;
float r=.0001;

bool f(size_t t)
{
	int x;
	std::cin>>x;
	std::cout<<t<<':'<<(x*x)<<std::endl;
	return t<end;
}

int main(int argc,char** argv)
{
	if(argc>1)
	{
		end=atoi(argv[1]);
		if(argc>2)
			r=atof(argv[2]);
	}
	
	
	loop l;
	l.rate(r);
	l.handle(f);
	l.run();
	
	return 0;
}