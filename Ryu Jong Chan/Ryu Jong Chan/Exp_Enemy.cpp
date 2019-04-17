#include "Exp_Enemy.h"
#include "Collider_Circle.h"
#include "Jet.h"
#include "timer.h"
#include "ObjectPool.h"

Exp_Enemy::Exp_Enemy(float px, float py) : Animation(px, py, "exp_enemy", 3)
{
}


Exp_Enemy::~Exp_Enemy()
{
}

void Exp_Enemy::init()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			DDS_IMAGE image;

			readDDSRect("asset/Expenemy.dds", j * 128, i * 128, 128, 128, &image);
			addAniSprite(image);
		}
	}
	
	lifeTime = 1;  
}

void Exp_Enemy::update()
{
	lifeTime = lifeTime - getDeltaTime();

	if (lifeTime <= 0)
	{
		ObjectPool::delGameObject(this);
	}
}