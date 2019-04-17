#include "GameObject.h"
#include "ObjectPool.h"

int GameObject::GameScore = 0;
int GameObject::Life = 3;


/*----------------------
 ��� : GameObject ������
 �Ķ���� �� : �̸��ο�, �±�, ��ǥx, ��ǥy

 ��
 (1)�⺻ ���� = 0
 (2)�⺻ ������ = (1,1)
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
 ��� : GameObject �Ҹ���

 ��
 (1)�ε��� �̹��� �޸� ����
 (2)�߰��� �浹ü�� ����
 (3)�浹ü ������ ���� �迭 ����
 (4)�ڽ� ������Ʈ ����(ObjectPool�� ��ϵ� �ڽ� ������Ʈ)
 (5)�ڽ� ������Ʈ ���� ����Ʈ �ϰ� ����
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
 ��� : GameObject�� drawDDS�� �׸�

 ��
 (1)���ӿ�����Ʈdraw
 (2)�浹üdraw - (����ȯ�濡���� ���)
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
 ��� : GameObject �̸� ����
 return �� : name
----------------------*/
char * GameObject::getName()
{
	return name;
}


/*----------------------
 ��� : GameObject �±� ����
 return �� : tag
----------------------*/
int GameObject::getTag()
{
	return tag;
}


/*----------------------
 ��� : GameObject �浹ü �߰��Լ�
 �Ķ���� �� : �ݶ��̴� ����(Collider_AABB OR Collider_Circle)

 ��
 (1)colliders�� stl���Ϳ� �浹ü �߰�
 (2)�θ��� ��ǥ��(0, 0)���� �ڽ��� ��ǥ�� ���� (localPosition)
----------------------*/
void GameObject::addCollider(Collider * col)
{
	colliders.push_back(col);
	
	col->setOwnerPosition(px, py);
}


/*----------------------
 ��� : GameObject �̵��Լ�
 �Ķ���� �� : �̵���x��ǥ, �̵���y��ǥ

 ��
 (1)�浹ü �̵�
 (2)�ڽ� ������Ʈ �̵�
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
 ��� : �ڽ� ������Ʈ�� ������ �� stl vector���� �浹ü ������ �޾ƿ��� �Լ� 
 return �� : colliders.size();
 ��
----------------------*/
int GameObject::colSize() 
{
	return colliders.size();
}


/*----------------------
 ��� : �浹ü ������ �ޱ����� stl vector�� ��ȣ�� �������� �Լ�
 �Ķ���� �� : stl vector�� i��°
 return �� : colliders[i];
----------------------*/
Collider * GameObject::colAt(int i)
{
	return colliders[i];
}


/*----------------------
 ��� : ���� �ٸ� GameObject ������ �浹 ó�� �Լ�
 �Ķ���� �� : �ٸ� ���ӿ�����Ʈ, �ٸ� ���ӿ�����Ʈ�� �浹ü ����, ���� �浹ü ����
----------------------*/
void GameObject::OnCollision(GameObject * other, Collider * otherCol, Collider * myCol)
{
}


/*----------------------
 ��� : �ڽ��� �ٸ� GameObject�� �������� �ִ� �Լ�
 �Ķ���� �� : �������� ���� GameObject, �������� 
----------------------*/
void GameObject::DoDamage(GameObject * fromObj, float d)
{
}


/*----------------------
 ��� : �ڽ� ������Ʈ �߰� �Լ�
 �Ķ���� �� : �ڽ� ������Ʈ, order��

 ��
 (1)�ڽĿ�����Ʈ�� childObjs�� stl Vector�� �߰���
 (2)�θ��� ��ǥ��(0, 0)���� �ڽ��� ��ǥ�� ���� (localPosition)
 (3)ObjectPool�� �߰�
----------------------*/
void GameObject::addChildObject(GameObject * o, int order)
{	
	childObjs.push_back(o);
	
	o->setParentPosition(px, py); 
	
	ObjectPool::addGameObject(o, order);
}


/*----------------------
 ��� : �ڽ� ������Ʈ ���� �Լ�
 �Ķ���� �� : �ڽ� ������Ʈ

 ��
 (1)childObjs�� stl vector���� ����
 (2)ObjectPool���� �ڽĿ�����Ʈ�� ����
----------------------*/
void GameObject::delChildObject(GameObject * o)
{
	for (int i = 0; i < (int)childObjs.size(); i++)
	{
		//(1)�θ��� �ڽĿ�����Ʈ stl vector���� ������
		if (childObjs[i] == o)
		{
			childObjs.erase(childObjs.begin() + i);
			
			ObjectPool::delGameObject(o);
		}
	}
}


/*----------------------
 ��� : ���� ������Ʈ�� �ڽ�,�浹ü �߰� �Լ����� ȣ��� (localPosition���� ����ϱ� ���� �Լ�)
 �Ķ���� �� : localPosition.x��ǥ, localPosition.y��ǥ
----------------------*/
void GameObject::setParentPosition(float parentx, float parenty)
{
	px = parentx + px; 
	py = parenty + py;
}