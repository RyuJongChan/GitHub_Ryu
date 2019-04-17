#include "ObjectPool.h"

std::vector<GameObject *> ObjectPool::objs[MAX_LAYER];
std::vector<GameObject *> ObjectPool::dels;

void ObjectPool::addGameObject(GameObject * o, int order)
{
	objs[order].push_back(o);     
	o->init();               
}

void ObjectPool::delGameObject(GameObject * o)
{
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < objs[layer].size(); i++)
		{
			if (objs[layer][i] == o)    
			{
				dels.push_back(o);      //지울 오브젝트를 보관함

				objs[layer].erase(objs[layer].begin() + i); 

				return;   
			}
		}
	}
}

void ObjectPool::clearDelObject()
{
	for (int i = 0; i < dels.size(); i++)
	{
		delete dels[i];   
	}

	dels.clear();        
}

int  ObjectPool::size(int order)  
{
	return objs[order].size();   
}

GameObject * ObjectPool::at(int i, int order)
{
	return objs[order].at(i);
}

void ObjectPool::clearAll()
{
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < objs[layer].size(); i++)
		{
			delete objs[layer][i];
		}
		objs[layer].clear();
	}
}