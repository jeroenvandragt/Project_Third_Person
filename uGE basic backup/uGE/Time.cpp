#include "Time.hpp"

#include <iostream>

sf::Clock Time::clock;
float Time::currentTime = 0.0f;
float Time::deltaTime = 0.0f;

void Time::update()
{
	float newTime = clock.getElapsedTime().asSeconds();
	deltaTime = newTime - currentTime;
	currentTime = newTime;
}

float Time::now()
{
	return currentTime;
}

float Time::step()
{
	return deltaTime;
}
