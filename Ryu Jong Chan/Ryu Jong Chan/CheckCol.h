#pragma once

#include "ColTest.h"

class CheckCol
{
public:
	//AABB �浹 üũ
	static bool checkAABB(Collider_AABB * o1, Collider_AABB* o2);
	
	//Circle �浹 üũ
	static bool checkCircle(Collider_Circle *o1, Collider_Circle *o2);

	//AABB <-> Circle �浹üũ
	static bool checkAABBCircle(Collider_AABB * o1, Collider_Circle *o2);
};