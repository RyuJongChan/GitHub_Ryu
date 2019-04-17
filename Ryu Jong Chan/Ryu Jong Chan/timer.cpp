#include <Windows.h>
#include "timer.h"

int    tick;
float  prevTime;
float  currTime;
float  deltaTime;

void initTimer()
{
	tick = GetTickCount();
	prevTime = (float)tick / 1000.0f;
	currTime = (float)tick / 1000.0f;
}

void updateTimer()
{
	tick = GetTickCount();
	currTime = (float)tick / 1000.0f;
	deltaTime = currTime - prevTime;
	prevTime = currTime; 
}

float getDeltaTime()
{
	return deltaTime;
}

void  exitTimer()
{
}
