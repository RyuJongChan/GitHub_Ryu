#pragma once

#include "GameObject.h"
#include "Label.h"

class Player : public GameObject
{
private:
	float speed;

	float fireRate;   
	float fireTime;

	int   hp;  

	//player ���ȯ ����
	int   only;
	
	GameObject * shield;          
	float        shieldLifeTime;
	bool ShieldState;
	
	//�÷��̾� ���ȯ �� ����
	int state; 

	Label *HpLabel;

public:	
	Player(float px, float py);
	virtual ~Player();	

	virtual void init();
	virtual void update();
		
	void PlayerController();	

	virtual void OnCollision(GameObject * other, Collider * otherCol, Collider * myCol);
	virtual void DoDamage(GameObject * fromObj, float d);
};