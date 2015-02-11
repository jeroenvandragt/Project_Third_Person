#include <iostream>

#include "FPS.hpp"
#include "Time.hpp"

float FPS::startTime = 0.0f;
unsigned int FPS::count = 0;
unsigned int FPS::fps = 0;

void FPS::update()
{
	float time = Time::now();
	FPS::count++;
	if ( time - startTime >= 1.0f ) {
		fps = count;
		//std::cout << "FPS " << fps << std::endl;
		count = 0;
		startTime = time;
	}
}

unsigned int FPS::getFPS()
{
	return fps;
}
