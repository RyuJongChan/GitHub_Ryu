#include "CheckCol.h"
#include <math.h>

bool CheckCol::checkAABB(Collider_AABB * o1, Collider_AABB * o2)
{
	float x0, y0, x1, y1;  //ù ��° AABB
	float a0, b0, a1, b1;  //�� ��° AABB

	o1->getBB(&x0, &y0, &x1, &y1);
	o2->getBB(&a0, &b0, &a1, &b1);

	if (a0 < x1 && a1 > x0)
	{
		if (b0 < y1 && b1 > y0)
		{
			return true;   //�浹
		}
	}

	return false;  //�浹x
}

bool CheckCol::checkCircle(Collider_Circle *o1, Collider_Circle *o2)
{
	float cx1, cy1, r1;    //ù ��° Circle �߽���ǥ, ������
	float cx2, cy2, r2;    //�� ��° Circle �߽���ǥ, ������

	o1->getBC(&cx1, &cy1, &r1);
	o2->getBC(&cx2, &cy2, &r2);
	
	float d = (float)sqrt((cx1 - cx2)*(cx1 - cx2) + (cy1 - cy2)*(cy1 - cy2));

	if (d < r1 + r2)
	{
		return true;   //�浹
	}

	return false;      //�浹x
}

bool CheckCol::checkAABBCircle(Collider_AABB * o1, Collider_Circle *o2)
{
	//AABB ��ǥ
	float x0, y0, x1, y1;
	//Circle�� �߽���ǥ, ������
	float cx, cy, r;

	o1->getBB(&x0, &y0, &x1, &y1);
	o2->getBC(&cx, &cy, &r);
	
	if ((x1 > cx && cx > x0) || (y1 > cy && cy > y0))
	{		
		float ex0, ey0, ex1, ey1;

		ex0 = x0 - r; ey0 = y0 - r;
		ex1 = x1 + r; ey1 = y1 + r;

		if ((ex1 > cx && cx > ex0) && (ey1 > cy && cy > ey0))
		{
			return true;	//�浹
		}
		else 
		{
			return false;	//�浹x
		}
	}

	else 
	{   
		float d0 = (float)sqrt((x0 - cx)*(x0 - cx) + (y0 - cy)*(y0 - cy));	//AABB�� �»�� ��ǥ�� Circle�� �߽ɰ��� �Ÿ�
		float d1 = (float)sqrt((x1 - cx)*(x1 - cx) + (y0 - cy)*(y0 - cy));	//AABB�� ���� ��ǥ�� Circle�� �߽ɰ��� �Ÿ�
		float d2 = (float)sqrt((x0 - cx)*(x0 - cx) + (y1 - cy)*(y1 - cy));	//AABB�� ���ϴ� ��ǥ�� Circle�� �߽ɰ��� �Ÿ�
		float d3 = (float)sqrt((x1 - cx)*(x1 - cx) + (y1 - cy)*(y1 - cy));	//AABB�� ���ϴ� ��ǥ�� Circle�� �߽ɰ��� �Ÿ�

		if (d0 < r || d1 < r || d2 < r || d3 < r)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
}