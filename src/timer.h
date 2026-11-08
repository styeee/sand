#pragma once

#include <chrono>
#include <thread>

class timer
{
	typedef std::chrono::steady_clock::time_point point;
	typedef std::chrono::duration<float> duration;

	point start;
public:
	timer()
	:
		start(std::chrono::steady_clock::now())
	{}

	float now()const
	{
		const auto t=std::chrono::steady_clock::now();
		return duration(t-start).count();
	}
	
	static void wait(float t)
	{
		std::this_thread::sleep_for(duration(t));
	}
};