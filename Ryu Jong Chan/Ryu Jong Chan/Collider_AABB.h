#pragma once

#include "Collider.h"

class Collider_AABB : public Collider
{
private:
	float width;  
	float height;  

public:
	Collider_AABB(float px, float py, float width, float height, const char *name, int tag);
	virtual ~Collider_AABB();

	//�ڽ����� ��ǥ get�Լ�
	void getBB(float *x0, float *y0, float *x1, float *y1);

	virtual void draw();
};

