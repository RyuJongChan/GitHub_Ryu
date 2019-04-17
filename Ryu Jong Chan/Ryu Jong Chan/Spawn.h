#pragma once

#include "GameObject.h"

class Spawn : public GameObject
{
private:
	float spawnRate;  
	float spawnTime;  

public:
	Spawn(float px, float py, float Rate);
	virtual ~Spawn();

	virtual void init();
	virtual void update();
};