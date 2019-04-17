#pragma once

#include "GameObject.h"

class Enemy :	public GameObject
{
private:
	float fireRate;  
	float fireTime;  

	float speedH;	//Horizontal 이동 속도
	float speedV;	//Vertical   이동 속도

	int hp;          

	float Temppx;	//초기 px임시 저장
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