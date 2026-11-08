#pragma once

#include <functional>
#include "timer.h"

class loop
{
	timer t;
	float duty=0;
	float delta=.016;
	float last=t.now();
	size_t count=0;
	std::function<bool(size_t)> f=
		[](size_t){return false;};
	
public:

	float rate()const
	{return delta;}
	void rate(float x)
	{delta=x;}

	void handle(std::function<bool(size_t)> x)
	{f=x;}
	
	void run()
	{
		while(true)
		{
			duty+=(t.now()-last);
			last=t.now();
			
			if(duty<delta)
			{
				timer::wait(.001);
				continue;
			}
			
			while(duty>=delta)
			{
    				duty-=delta;
    				if(!f(++count))
					return;
			}
		}
	}
};
