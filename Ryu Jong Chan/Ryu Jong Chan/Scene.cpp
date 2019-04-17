#include "Scene.h"
#include "ObjectPool.h"
#include "Collider_AABB.h"
#include "CheckCol.h"
#include "Collider_Circle.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::init()
{
}

void Scene::update()
{	
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < ObjectPool::size(layer); i++)
		{
			GameObject * o = ObjectPool::at(i, layer);  
			o->update();
		}
	}
}

void Scene::checkCol()
{	
	std::vector<GameObject *> tempObj;
	
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < ObjectPool::size(layer); i++)
		{
			GameObject * o = ObjectPool::at(i, layer);
			tempObj.push_back(o);
		}
	}

	for (int i = 0; i < tempObj.size(); i++)
	{
		for (int j = 0; j < tempObj.size(); j++)
		{
			if (i < j)
			{
				GameObject *o1 = tempObj.at(i);  //첫 번째 게임오브제트
				GameObject *o2 = tempObj.at(j);  //두 번째 게임오브젝트 

				for (int h = 0; h < o1->colSize(); h++)     //첫 번째 게임오브젝트의 충돌체들
				{
					for (int k = 0; k < o2->colSize(); k++) //두 번째 게임오브젝트의 충돌체들
					{
						Collider * c1 = o1->colAt(h); //첫 번째 게임오브젝트 충돌체
						Collider * c2 = o2->colAt(k); //두 번째 게임오브젝트 충돌체

						int t1 = c1->getColType();
						int t2 = c2->getColType();

						bool checkCol = false;

						if (t1 == CTCircle && t2 == CTCircle) 
						{
							checkCol = CheckCol::checkCircle((Collider_Circle*)c1, (Collider_Circle*)c2);
						}

						else if (t1 == CTAABB && t2 == CTAABB)
						{ 
							checkCol = CheckCol::checkAABB((Collider_AABB*)c1, (Collider_AABB*)c2);
						}

						else if (t1 == CTCircle && t2 == CTAABB)
						{ 
							checkCol = CheckCol::checkAABBCircle((Collider_AABB*)c2, (Collider_Circle*)c1);
						}

						else if (t1 == CTAABB && t2 == CTCircle)
						{ 
							checkCol = CheckCol::checkAABBCircle((Collider_AABB*)c1, (Collider_Circle*)c2);
						}

						//충돌 확인
						if (checkCol == true)
						{							
							o1->OnCollision(o2, c2, c1);							
							o2->OnCollision(o1, c1, c2);
						}
					}
				}
			}
		}
	}	
	tempObj.clear();  
}

void Scene::draw()   
{	
	for (int layer = 0; layer < MAX_LAYER; layer++) 
	{
		for (int i = 0; i < ObjectPool::size(layer); i++)
		{
			GameObject * o = ObjectPool::at(i, layer);
			o->draw();
		}
	}
}

void Scene::clear()   
{	
	ObjectPool::clearDelObject();
}

void Scene::exit()
{
	ObjectPool::clearAll();  
}