#pragma once

#include "Animation.h"

class Shield : public Animation
{
public:
	Shield(float px, float py);
	virtual ~Shield();

	virtual void init();
	virtual void OnCollision(GameObject * other, Collider * otherCol, Collider * myCol);
};