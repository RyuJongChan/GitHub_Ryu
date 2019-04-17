#pragma once
#include "Animation.h"
class Exp_Enemy : public Animation
{
private:
	float lifeTime;

public:
	Exp_Enemy(float px, float py);
	virtual ~Exp_Enemy();
	
	virtual void init();
	virtual void update();
};

