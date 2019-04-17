#include "LaserE1.h"
#include "timer.h"
#include "graphic.h"
#include "ObjectPool.h"
#include "Collider_Circle.h"

LaserE1::LaserE1(float px, float py) : GameObject("lasere",1, px, py)
{
}

LaserE1::~LaserE1()
{
}

void LaserE1::init()
{
	readDDS("asset/LaserE1.dds", &sprite);
	speed = 300;
	
	addCollider(new Collider_Circle(5, 5, 20, "lasere1", 0));
}

void LaserE1::update()
{
	float d = getDeltaTime() * speed;
	
	translate(0, d);
	
	if (py > HEIGHT)
	{
		ObjectPool::delGameObject(this);
	}
}

void LaserE1::OnCollision(GameObject * other, Collider * otherCol, Collider * myCol)
{
	if (strcmp(other->getName(), "player") == 0)
	{				
		other->DoDamage(this, 10);
	}
}

void LaserE1::DoDamage(GameObject * fromObj, float d)
{
	ObjectPool::delGameObject(this);
}