#pragma once

#include "GameObject.h"

class StartBG : public GameObject
{
public:
	StartBG(float px, float py);
	virtual ~StartBG();

	virtual void init();
};