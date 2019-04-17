#include "Collider_AABB.h"
#include "graphic.h"

Collider_AABB::Collider_AABB(float px, float py, float width, float height, const char *name, int tag) : Collider(name, tag, px, py)
{
	this->width = width;
	this->height = height;
	this->colType = CTAABB;
}

Collider_AABB::~Collider_AABB()
{
}

void Collider_AABB::getBB(float *x0, float *y0, float *x1, float *y1)
{
	*x0 = px;
	*y0 = py;

	*x1 = px + width;
	*y1 = py + height;
}

void Collider_AABB::draw()
{
	float x0, y0;   //바운딩 박스의 왼쪽 상단좌표
	float x1, y1;   //바운딩 박스의 오른쪽 하단 좌표

	x0 = px;
	y0 = py;

	x1 = x0 + width;
	y1 = y0 + height;

	//개발환경에서 보이게//
	//drawLine(x0, y0, x1, y0, 0, 0, 0);  //윗변
	//drawLine(x0, y1, x1, y1, 0, 0, 0);  //아랫변
	//drawLine(x0, y0, x0, y1, 0, 0, 0);  //좌변
	//drawLine(x1, y0, x1, y1, 0, 0, 0);  //우변
}