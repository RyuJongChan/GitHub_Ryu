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
	float x0, y0;   //�ٿ�� �ڽ��� ���� �����ǥ
	float x1, y1;   //�ٿ�� �ڽ��� ������ �ϴ� ��ǥ

	x0 = px;
	y0 = py;

	x1 = x0 + width;
	y1 = y0 + height;

	//����ȯ�濡�� ���̰�//
	//drawLine(x0, y0, x1, y0, 0, 0, 0);  //����
	//drawLine(x0, y1, x1, y1, 0, 0, 0);  //�Ʒ���
	//drawLine(x0, y0, x0, y1, 0, 0, 0);  //�º�
	//drawLine(x1, y0, x1, y1, 0, 0, 0);  //�캯
}