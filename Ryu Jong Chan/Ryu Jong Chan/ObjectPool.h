#pragma once

#include <vector>
#include "GameObject.h"

#define MAX_LAYER 3      

class ObjectPool
{
private:		
	static std::vector<GameObject *> objs[MAX_LAYER];	
	static std::vector<GameObject *> dels;				 

public:
	static void addGameObject(GameObject * o, int order=0);   
	static void delGameObject(GameObject * o);                
	static int  size(int order=0);
	static GameObject * at(int i, int order=0);

	//dels�� ������ ���ӿ�����Ʈ ���� ����
	static void clearDelObject();	

	//ObjectPool�� ���� ������Ʈ ���� ����
	static void clearAll();		    
};