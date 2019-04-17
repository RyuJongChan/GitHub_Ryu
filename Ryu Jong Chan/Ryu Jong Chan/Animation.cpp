#include "Animation.h"
#include "timer.h"

Animation::Animation(float px, float py) : GameObject("ani",0, px, py)
{
	aniRate   = (float)0.1;  
	aniTimer  = 0;
	aniIndex   = 0; 
	blendMode = 0;			 //기본세팅 = 알파블렌딩
}

Animation::Animation(float px, float py, const char * name, int tag) : GameObject(name, tag, px, py)
{
	aniRate   = (float)0.1;  
	aniTimer  = 0;
	aniIndex   = 0;
	blendMode = 0;			 //기본세팅 = 알파블렌딩
}

Animation::~Animation()
{	
	for (int i = 0; i < (int)aniSprite.size(); i++)
	{
		delete[] aniSprite[i].argb;
	}

	aniSprite.clear();
}

void Animation::init()
{
	
}

void Animation::update()
{
}

void Animation::draw()
{
	aniTimer = aniTimer + getDeltaTime();

	if (aniTimer >= aniRate)
	{
		aniIndex++;
		if (aniIndex >= (int)aniSprite.size())
		{
			aniIndex = 0;
		}

		aniTimer = 0;
	}

	//알파 블렌딩 (Alpha Blending)
	if (blendMode == 0)
	{
		drawDDS((int)px, (int)py, &aniSprite[aniIndex]);        
	}

	//가산 블렌딩(Additive Blending)
	else if (blendMode == 1)
	{
		drawDDSAdditiveBlending((int)px, (int)py, &aniSprite[aniIndex]);
	}

	//충돌체 개발환경에서 보이게
	for (int i = 0; i < (int)colliders.size(); i++)
	{
		colliders[i]->draw();
	}
}

void Animation::addAniSprite(DDS_IMAGE image)
{
	aniSprite.push_back(image);
}

void Animation::setAniRate(float aniRate)
{
	this->aniRate = aniRate;
}

void Animation::setBlendMode(int mode)
{
	this->blendMode = mode;
}