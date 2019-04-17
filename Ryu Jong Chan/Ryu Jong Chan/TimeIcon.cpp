#include "TimeIcon.h"

TimeIcon::TimeIcon(float px, float py) : GameObject("timeIcon",3, px, py)
{
}

TimeIcon::~TimeIcon()
{
}

void TimeIcon::init()
{
	readDDS("asset/Timeicon.dds", &sprite);
}