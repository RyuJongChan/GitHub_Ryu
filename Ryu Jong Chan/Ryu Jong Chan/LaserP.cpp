#include "LaserP.h"
#include "timer.h"
#include "Collider_AABB.h"
#include "ObjectPool.h"
#include "Sound.h"

LaserP::LaserP(float px, float py) : GameObject("laserp",0, px, py)
{
}

LaserP::~LaserP()
{
}

void LaserP::init()
{
	readDDS("asset/LaserP.dds", &sprite);
	speed = 450;

	addCollider(new Collider_AABB(0, 0, 9, 54, "colp", 0));

    //발사 사운드
    addChildObject(new Sound("asset/Sound/LaserP.wav", false));
}

void LaserP::update()
{
	float d = getDeltaTime() * speed;
	translate(0, -d);

	if (py < 0)
	{
		ObjectPool::delGameObject(this);
	}
}

void LaserP::OnCollision(GameObject * other, Collider * otherCol, Collider * myCol)
{
	if (other->getTag() == 1)  
	{		
		other->DoDamage(this, 20);
		
		ObjectPool::delGameObject(this);  
	}
}