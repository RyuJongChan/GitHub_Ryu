#pragma once

#include "GameObject.h"

class Enemy :	public GameObject
{
private:
	float fireRate;  
	float fireTime;  

	float speedH;	//Horizontal �̵� �ӵ�
	float speedV;	//Vertical   �̵� �ӵ�

	int hp;          

	float Temppx;	//�ʱ� px�ӽ� ����
	bool isRight;

public:
	Enemy(float px, float py);
	virtual ~Enemy();

	virtual void init();
	virtual void update();

	void moveHor();
	void moveVer();
	void fireLaser();

	
	virtual void OnCollision(GameObject * other, Collider * otherCol, Collider * myCol);	
	virtual void DoDamage(GameObject * fromObj, float d);
};