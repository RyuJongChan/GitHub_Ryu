#pragma once

#include "Collider.h"

class Collider_Circle :	public Collider
{
private:
	float r;

public:
	Collider_Circle(float px, float py, float r, const char * name, int tag);
	virtual ~Collider_Circle();

	virtual void draw();

	//�� ���� ��ǥ get�Լ�
	void getBC(float *cx, float *cy, float *rd);
};