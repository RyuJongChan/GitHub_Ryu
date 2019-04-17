#include "Spawn.h"
#include "timer.h"
#include "Enemy.h"
#include "ObjectPool.h"

Spawn::Spawn(float px, float py, float Rate) : GameObject("½ºÆ÷³Ê", 1, px, py)
{
	this->spawnRate = Rate;
}

Spawn::~Spawn()
{
}

void Spawn::init()
{	
	spawnTime = 1;	
}

void Spawn::update()
{
	spawnTime = spawnTime + getDeltaTime();		

	if (spawnTime >= spawnRate)
	{	   
		ObjectPool::addGameObject(new Enemy(px, py));
	   
		spawnTime = 1;
	}
}
