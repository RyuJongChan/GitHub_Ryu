#include "Jet.h"
#include "Collider_AABB.h"

Jet::Jet(float px, float py):Animation(px, py, "jet", 0)
{
}

Jet::~Jet()
{
}

void Jet::init()
{	
	DDS_IMAGE image;

	readDDS("asset/Jet1.dds", &image);
	addAniSprite(image);

	readDDS("asset/Jet2.dds", &image);
	addAniSprite(image);

	readDDS("asset/Jet3.dds", &image);
	addAniSprite(image);
	
	addCollider(new Collider_AABB(0, 0, 10, 30, "jet", 0));
	
	setAniRate((float)0.1);
}