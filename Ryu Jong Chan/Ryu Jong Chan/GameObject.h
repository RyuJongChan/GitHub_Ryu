#pragma once

#include <vector>

#include "Collider.h"
#include "DDS.h"

class GameObject
{
protected:
	//���ӿ�����Ʈ �⺻ �Ӽ�
	char name[32];
	int  tag;
	bool state;

	//���ӿ�����Ʈ�� ������, ȸ��, ������
	float px, py;
	float angle;
	float sx, sy;		

	//DDS �̹��� ���� 
	DDS_IMAGE sprite;

	//�浹ü ����� stl vector
	std::vector<Collider *> colliders;

	//�ڽ� ���ӿ�����Ʈ ����� stl vector
	std::vector<GameObject *> childObjs;

public:
	//����, ���� ��������
	static int GameScore;
	static int Life;

	GameObject(const char * name, int tag, float px, float py);
	virtual ~GameObject();

	//�浹ü �߰� �Լ�
	void addCollider(Collider * col);

	//�ڽĿ�����Ʈ �߰�, ���� �Լ�
	void addChildObject(GameObject * o, int order=0);
	void delChildObject(GameObject * o);
	
	//�θ� ��ǥ �����Լ�(localPosition)
	void setParentPosition(float parentx, float parenty);

	//�浹�̺�Ʈ�� ���� �޴� �����Լ�
	virtual void OnCollision(GameObject * other, Collider * otherCol, Collider * myCol);

	//�ڽ��� Ư�� ������Ʈ�� �������� �ִ� �����Լ�
	virtual void DoDamage(GameObject * fromObj, float d);

	//����
	char * getName();
	int    getTag();

	virtual void init();
	virtual void update();
	virtual void draw();

	//���ӿ�����Ʈ �̵��Լ�
	void translate(float tx, float ty);

	//�浹ü ����
	int colSize();
	Collider * colAt(int i);
};