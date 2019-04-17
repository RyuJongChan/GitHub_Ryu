#include "Exp_Player.h"
#include "timer.h"
#include "ObjectPool.h"

Exp_Player::Exp_Player(float px, float py) : Animation(px, py, "exp_player", 3)
{
}

Exp_Player::~Exp_Player()
{
}

void Exp_Player::init()
{
	DDS_IMAGE image;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			readDDSRect("asset/Expplayer.dds", i * 96, j * 96, 96, 96, &image);
			addAniSprite(image);
		}
	}
	
	lifeTime = 2.0;
	
	setBlendMode(1);	//°¡»ê ºí·»µù
}

void Exp_Player::update()
{
	lifeTime = lifeTime - getDeltaTime();

	if (lifeTime <= 0)
	{
		ObjectPool::delGameObject(this);
	}
}