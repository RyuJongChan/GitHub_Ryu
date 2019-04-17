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

	//player 재소환 방지
	int   only;
	
	GameObject * shield;          
	float        shieldLifeTime;
	bool ShieldState;
	
	//플레이어 재소환 시 상태
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