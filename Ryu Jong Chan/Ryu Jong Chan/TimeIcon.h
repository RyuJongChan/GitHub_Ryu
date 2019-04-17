#pragma once

#include "GameObject.h"

class TimeIcon : public GameObject
{
public:
	TimeIcon(float px, float py);
	virtual ~TimeIcon();

	virtual void init();
};