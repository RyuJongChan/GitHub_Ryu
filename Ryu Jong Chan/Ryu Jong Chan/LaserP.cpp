#include "LaserP.h"
#include "timer.h"
#include "Collider_AABB.h"
#include "ObjectPool.h"
#include "Sound.h"
#include "Player.h"

LaserP::LaserP(float px, float py) : GameObject("laserp",0, px, py)
{
}

LaserP::~LaserP()
{
}

void LaserP::init()
{
	laserPDamage = 20;
	readDDS("asset/LaserP.dds", &sprite);
	speed = 450;

	addCollider(new Collider_AABB(0, 0, 9, 54, "colp", 0));
    
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
		other->DoDamage(this, laserPDamage);
		
		ObjectPool::delGameObject(this);  
	}
}