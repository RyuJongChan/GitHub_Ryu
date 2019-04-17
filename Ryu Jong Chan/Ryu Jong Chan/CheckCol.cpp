#include "CheckCol.h"
#include <math.h>

bool CheckCol::checkAABB(Collider_AABB * o1, Collider_AABB * o2)
{
	float x0, y0, x1, y1;  //첫번째 사각형 영역
	float a0, b0, a1, b1;  //두번째 사각형 영역

	o1->getBB(&x0, &y0, &x1, &y1);
	o2->getBB(&a0, &b0, &a1, &b1);

	if (a0 < x1 && a1 > x0)
	{
		if (b0 < y1 && b1 > y0)
		{
			return true;   //충돌 했음
		}
	}

	return false;  //충돌 안했음
}

bool CheckCol::checkCircle(Collider_Circle *o1, Collider_Circle *o2)
{
	float cx1, cy1, r1;    //첫번째 원의 중심과 반지름
	float cx2, cy2, r2;    //두번째 원의 중심과 반지름

	o1->getBC(&cx1, &cy1, &r1);
	o2->getBC(&cx2, &cy2, &r2);

	////충돌조건 : (cx1, cy1)과 (cx2, cy2)거리가 r1+r2보다 작다
	float d = (float)sqrt((cx1 - cx2)*(cx1 - cx2) + (cy1 - cy2)*(cy1 - cy2));

	if (d < r1 + r2)
	{
		return true;   //2개의 원이 충돌함
	}

	return false;      //2개의 원이 충돌하지 않음
}

bool CheckCol::checkAABBCircle(Collider_AABB * o1, Collider_Circle *o2)
{
	//(1)사각형 AABB의 좌표를 가져옴
	float x0, y0, x1, y1;
	//(2)원의 중심과 반지름을 가져옴
	float cx, cy, r;

	o1->getBB(&x0, &y0, &x1, &y1);
	o2->getBC(&cx, &cy, &r);

	//원이 사각형의 수직 또는 수평 방향으로 이동할경우..
	if ((x1 > cx && cx > x0) || (y1 > cy && cy > y0))
	{
		//원의 반지름 r 만큼 확장된 사각형 좌표 구하기
		float ex0, ey0, ex1, ey1;

		ex0 = x0 - r; ey0 = y0 - r;
		ex1 = x1 + r; ey1 = y1 + r;

		//원의 중심이 확장된 사각형의 내부에 있는지를 검사함
		if ((ex1 > cx && cx > ex0) && (ey1 > cy && cy > ey0))
		{
			return true;
		}
		else {
			return false;
		}

	}

	else 
	{   //원이 사각형의 대각선 방향으로 이동함

		float d0 = (float)sqrt((x0 - cx)*(x0 - cx) + (y0 - cy)*(y0 - cy));//왼쪽   상단 꼭지점과 원의 중심간의 거리
		float d1 = (float)sqrt((x1 - cx)*(x1 - cx) + (y0 - cy)*(y0 - cy));//오른쪽 상단 꼭지점과 원의 중심간의 거리
		float d2 = (float)sqrt((x0 - cx)*(x0 - cx) + (y1 - cy)*(y1 - cy));//왼쪽   하단 꼭지점과 원의 중심간의 거리
		float d3 = (float)sqrt((x1 - cx)*(x1 - cx) + (y1 - cy)*(y1 - cy));//오른쪽 하단 꼭지점과 원의 중심간의 거리

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