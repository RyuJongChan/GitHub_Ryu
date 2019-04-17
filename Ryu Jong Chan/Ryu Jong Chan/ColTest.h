#pragma once

#include "Collider_AABB.h"
#include "Collider_Circle.h"

/////////�簢�� ���� �����/////////////
class RectE : public Collider_AABB
{
private:

public:
	RectE(float px, float py, float width, float height);
	virtual ~RectE();
};

/////////�簢�� �÷��̾� �����/////////////
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

/////////�� ���� �����/////////////
class CircleE : public Collider_Circle
{
private:

public:
	CircleE(float px, float py, float r);
	virtual ~CircleE();
};

/////////�� �÷��̾� �����/////////////
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
