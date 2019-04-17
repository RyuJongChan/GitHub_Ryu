#pragma once

#include "Animation.h"

class Jet : public Animation
{
public:
	Jet(float px, float py);
	virtual ~Jet();

	virtual void init();
};