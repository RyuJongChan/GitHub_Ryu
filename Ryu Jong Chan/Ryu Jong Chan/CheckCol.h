#pragma once

#include "ColTest.h"

class CheckCol
{
public:
	//AABB 面倒 眉农
	static bool checkAABB(Collider_AABB * o1, Collider_AABB* o2);
	
	//Circle 面倒 眉农
	static bool checkCircle(Collider_Circle *o1, Collider_Circle *o2);

	//AABB <-> Circle 面倒眉农
	static bool checkAABBCircle(Collider_AABB * o1, Collider_Circle *o2);
};