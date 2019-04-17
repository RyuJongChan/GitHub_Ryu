#pragma once

#include "Animation.h"

class Exp_Player :	public Animation
{
private:
	float lifeTime;

public:
	Exp_Player(float px, float py);
	virtual ~Exp_Player();
	
	virtual void init();
	virtual void update();
};

