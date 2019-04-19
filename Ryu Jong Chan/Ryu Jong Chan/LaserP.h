#pragma once

#include "GameObject.h"

class LaserP : public GameObject
{
private:
	float speed;
	float laserPDamage;

public:
	LaserP(float px, float py);
	virtual ~LaserP();
	
	virtual void init();
	virtual void update();
	
    void OnCollision(GameObject * other, Collider * otherCol, Collider * myCol);
};
