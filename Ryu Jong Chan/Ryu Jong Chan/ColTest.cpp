#include "ColTest.h"
#include "timer.h"
#include "input.h"

RectE::RectE(float px, float py, float width, float height)	: Collider_AABB(px, py, width, height, "적기", 1)
{
}
RectE::~RectE()
{
}

RectP::RectP(float px, float py, float width, float height)	: Collider_AABB(px, py, width, height, "플레이어", 1)
{
}
RectP::~RectP()
{
}

void RectP::init()
{
	speed = 200;
}

void RectP::update()
{
	float d = getDeltaTime() * speed;

	//키입력으로 이동
	if (GetKey(VK_LEFT) == true)
	{
		px = px - d;
	}

	if (GetKey(VK_RIGHT) == true)
	{
		px = px + d;
	}

	if (GetKey(VK_UP) == true)
	{
		py = py - d;
	}

	if (GetKey(VK_DOWN) == true)
	{
		py = py + d;
	}
}

//원 적기
CircleE::CircleE(float px, float py, float r) : Collider_Circle(px, py, r, "적기", 1)
{
}
CircleE::~CircleE()
{

}

//원 플레이어
CircleP::CircleP(float px, float py, float r) : Collider_Circle(px, py, r, "플레이어", 0)
{
}
CircleP::~CircleP()
{
}

void CircleP::init()
{
	speed = 200;
}

void CircleP::update()
{
	float d = getDeltaTime() * speed;
	
	if (GetKey(VK_LEFT) == true)
	{
		px = px - d;
	}

	if (GetKey(VK_RIGHT) == true)
	{
		px = px + d;
	}

	if (GetKey(VK_UP) == true)
	{
		py = py - d;
	}

	if (GetKey(VK_DOWN) == true)
	{
		py = py + d;
	}
}