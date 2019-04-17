#pragma once

#include "GameObject.h"
#include "Label.h"

class Clock : public GameObject
{
private:	
	Label * label;
	float time;

public:
	Clock(float px, float py);
	virtual ~Clock();

	virtual void init();
	virtual void update();
};