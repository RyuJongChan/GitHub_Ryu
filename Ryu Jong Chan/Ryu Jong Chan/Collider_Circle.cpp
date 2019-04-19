#include "Collider_Circle.h"
#include "graphic.h"


Collider_Circle::Collider_Circle(float px, float py, float r, const char * name, int tag) : Collider(name, tag, px, py)
{
	this->r = r;
	this->colType = CTCircle;
}


Collider_Circle::~Collider_Circle()
{
}

void Collider_Circle::getBC(float *cx, float *cy, float *rd)
{
	*cx = px + r;
	*cy = py + r;
	*rd = r;
}

void Collider_Circle::draw()
{
	float cx = px + r;  //���� x-�� �߽���ġ
	float cy = py + r;  //���� y-�� �߽���ġ

	////����ȯ�濡�� ���̰�//
	//drawCircle(cx, cy, r, 255, 255, 255);
}