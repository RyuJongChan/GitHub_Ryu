#pragma once

#include "Collider_AABB.h"
#include "Collider_Circle.h"

/////////사각형 적기 만들기/////////////
class RectE : public Collider_AABB
{
private:

public:
	RectE(float px, float py, float width, float height);
	virtual ~RectE();
};

/////////사각형 플레이어 만들기/////////////
class RectP : public Collider_AABB
{
private:

	float speed;

public:
	RectP(float px, float py, float width, float height);
	virtual ~RectP();

	void init();
	void update();
};

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

/////////원 적기 만들기/////////////
class CircleE : public Collider_Circle
{
private:

public:
	CircleE(float px, float py, float r);
	virtual ~CircleE();
};

/////////원 플레이어 만들기/////////////
class CircleP : public Collider_Circle
{
private:

	float speed;

public:
	CircleP(float px, float py, float r);
	virtual ~CircleP();

	void init();
	void update();
};
