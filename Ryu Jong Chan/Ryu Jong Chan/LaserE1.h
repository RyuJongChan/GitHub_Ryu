#pragma once

#include "GameObject.h"

class LaserE1 : public GameObject
{
private:
	float speed;

public:
	LaserE1(float px, float py);
	virtual ~LaserE1();

	virtual void init();
	virtual void update();
	
	virtual void OnCollision(GameObject * other, Collider * otherCol, Collider * myCol);	
	virtual void DoDamage(GameObject * fromObj, float d);
};