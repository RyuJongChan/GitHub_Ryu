#include "GameObject.h"
#include "ObjectPool.h"

int GameObject::GameScore = 0;
int GameObject::Life = 3;


/*----------------------
 기능 : GameObject 생성자
 파라미터 값 : 이름부여, 태그, 좌표x, 좌표y

 ※
 (1)기본 각도 = 0
 (2)기본 스케일 = (1,1)
-----------------------*/
GameObject::GameObject(const char * name, int tag, float px, float py)
{
	strcpy_s(this->name, name);
	this->tag   = tag;
	this->state = true;

	this->px = px;
	this->py = py;

	this->angle = 0;
	this->sx = 1;
	this->sy = 1;

	this->sprite.argb = NULL;	
}


/*----------------------
 기능 : GameObject 소멸자

 ※
 (1)로드한 이미지 메모리 제거
 (2)추가한 충돌체들 제거
 (3)충돌체 포인터 저장 배열 삭제
 (4)자식 오브젝트 제거(ObjectPool에 등록된 자식 오브젝트)
 (5)자식 오브젝트 저장 리스트 일괄 삭제
-----------------------*/
GameObject::~GameObject()
{	
	if (sprite.argb != NULL)
	{
		delete[] sprite.argb;
		sprite.argb = NULL;
	}

	for (int i = 0; i < (int)colliders.size(); i++)
	{
		delete colliders[i];
	}	

	colliders.clear(); 	

	for (int i = 0; i < (int)childObjs.size(); i++)
	{		
		ObjectPool::delGameObject(childObjs[i]);
	}	

	childObjs.clear();   
}


void GameObject::init()
{}
void GameObject::update()
{}


/*----------------------
 기능 : GameObject를 drawDDS로 그림

 ※
 (1)게임오브젝트draw
 (2)충돌체draw - (개발환경에서만 사용)
----------------------*/
void GameObject::draw()
{
	if (sprite.argb != NULL)
	{
		drawDDS((int)px, (int)py, &sprite);
	}

	for (int i = 0; i < (int)colliders.size(); i++)
	{
		colliders[i]->draw();
	}
}


/*----------------------
 기능 : GameObject 이름 게터
 return 값 : name
----------------------*/
char * GameObject::getName()
{
	return name;
}


/*----------------------
 기능 : GameObject 태그 게터
 return 값 : tag
----------------------*/
int GameObject::getTag()
{
	return tag;
}


/*----------------------
 기능 : GameObject 충돌체 추가함수
 파라미터 값 : 콜라이더 종류(Collider_AABB OR Collider_Circle)

 ※
 (1)colliders의 stl벡터에 충돌체 추가
 (2)부모의 좌표를(0, 0)으로 자신의 좌표를 받음 (localPosition)
----------------------*/
void GameObject::addCollider(Collider * col)
{
	colliders.push_back(col);
	
	col->setOwnerPosition(px, py);
}


/*----------------------
 기능 : GameObject 이동함수
 파라미터 값 : 이동할x좌표, 이동할y좌표

 ※
 (1)충돌체 이동
 (2)자식 오브젝트 이동
----------------------*/
void GameObject::translate(float tx, float ty)
{
	px = px + tx;
	py = py + ty;
	
	for (int i = 0; i < (int)colliders.size(); i++)
	{
		colliders[i]->translate(tx, ty);
	}
	
	for (int i = 0; i < (int)childObjs.size(); i++)
	{
		childObjs[i]->translate(tx, ty);
	}
}


/*----------------------
 기능 : 자식 오브젝트를 제거할 때 stl vector에서 충돌체 갯수를 받아오는 함수 
 return 값 : colliders.size();
 ※
----------------------*/
int GameObject::colSize() 
{
	return colliders.size();
}


/*----------------------
 기능 : 충돌체 정보를 받기위해 stl vector의 번호를 가져오는 함수
 파라미터 값 : stl vector의 i번째
 return 값 : colliders[i];
----------------------*/
Collider * GameObject::colAt(int i)
{
	return colliders[i];
}


/*----------------------
 기능 : 서로 다른 GameObject 끼리의 충돌 처리 함수
 파라미터 값 : 다른 게임오브젝트, 다른 게임오브젝트의 충돌체 종류, 나의 충돌체 종류
----------------------*/
void GameObject::OnCollision(GameObject * other, Collider * otherCol, Collider * myCol)
{
}


/*----------------------
 기능 : 자신이 다른 GameObject에 데미지를 주는 함수
 파라미터 값 : 데미지를 받을 GameObject, 데미지량 
----------------------*/
void GameObject::DoDamage(GameObject * fromObj, float d)
{
}


/*----------------------
 기능 : 자식 오브젝트 추가 함수
 파라미터 값 : 자식 오브젝트, order값

 ※
 (1)자식오브젝트를 childObjs의 stl Vector에 추가함
 (2)부모의 좌표를(0, 0)으로 자신의 좌표를 받음 (localPosition)
 (3)ObjectPool에 추가
----------------------*/
void GameObject::addChildObject(GameObject * o, int order)
{	
	childObjs.push_back(o);
	
	o->setParentPosition(px, py); 
	
	ObjectPool::addGameObject(o, order);
}


/*----------------------
 기능 : 자식 오브젝트 제거 함수
 파라미터 값 : 자식 오브젝트

 ※
 (1)childObjs의 stl vector에서 제거
 (2)ObjectPool에서 자식오브젝트를 제거
----------------------*/
void GameObject::delChildObject(GameObject * o)
{
	for (int i = 0; i < (int)childObjs.size(); i++)
	{
		//(1)부모의 자식오브젝트 stl vector에서 제거함
		if (childObjs[i] == o)
		{
			childObjs.erase(childObjs.begin() + i);
			
			ObjectPool::delGameObject(o);
		}
	}
}


/*----------------------
 기능 : 게임 오브젝트에 자식,충돌체 추가 함수에서 호출됨 (localPosition으로 사용하기 위한 함수)
 파라미터 값 : localPosition.x좌표, localPosition.y좌표
----------------------*/
void GameObject::setParentPosition(float parentx, float parenty)
{
	px = parentx + px; 
	py = parenty + py;
}