#include "Shield.h"
#include "Collider_Circle.h"

Shield::Shield(float px, float py) : Animation(px, py, "shield", 0)
{
}

Shield::~Shield()
{
}

void Shield::init()
{
	DDS_IMAGE image;	

	readDDS("asset/Shield/Shield1.dds", &image); addAniSprite(image);
	readDDS("asset/Shield/Shield2.dds", &image); addAniSprite(image);
	readDDS("asset/Shield/Shield3.dds", &image); addAniSprite(image);
	readDDS("asset/Shield/Shield4.dds", &image); addAniSprite(image);
	readDDS("asset/Shield/Shield5.dds", &image); addAniSprite(image);
	readDDS("asset/Shield/Shield6.dds", &image); addAniSprite(image);
	readDDS("asset/Shield/Shield7.dds", &image); addAniSprite(image);
	readDDS("asset/Shield/Shield8.dds", &image); addAniSprite(image);

	addCollider(new Collider_Circle(5, 10, 70, "shield", 0));
}

void Shield::OnCollision(GameObject * other, Collider * otherCol, Collider * myCol)
{
	if (other->getTag() == 1)
	{		
		other->DoDamage(this, 200);
	}
}
