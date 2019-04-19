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
	float cx = px + r;  //원의 x-축 중심위치
	float cy = py + r;  //원의 y-축 중심위치

	////개발환경에서 보이게//
	//drawCircle(cx, cy, r, 255, 255, 255);
}