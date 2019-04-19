#include "Clock.h"
#include "TimeIcon.h"
#include "Label.h"
#include "timer.h"

Clock::Clock(float px, float py) : GameObject("clock",3, px, py)
{
	time = 0;
}

Clock::~Clock()
{
}

void Clock::init()
{
	addChildObject(new TimeIcon(0, 0), 2); 
	
	label = new Label("00:00", "asset/godoMaum.ttf", 48, 0xffffff, 70, 10, 3);
	addChildObject(label, 2);              
}

void Clock::update()
{
	char buff[64];
	time = time + getDeltaTime();	

	int min = (int)time / 60;
	int sec = (int)time % 60;
	int ms = (int)(time - time) * 100;

	sprintf_s(buff, "%02d:%02d:%02d", min, sec, ms);
	label->setText(buff);
}