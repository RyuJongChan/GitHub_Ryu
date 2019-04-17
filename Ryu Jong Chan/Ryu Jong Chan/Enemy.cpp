#include "Enemy.h"
#include "timer.h"
#include "LaserE1.h"
#include "ObjectPool.h"
#include "graphic.h"
#include "Collider_Circle.h"
#include "Exp_Enemy.h"

Enemy::Enemy(float px, float py) : GameObject("enemy", 1, px, py)
{
}


Enemy::~Enemy()
{
}


void Enemy::init()
{
	readDDS("asset/Enemy1.dds", &sprite);

	speedH = 100;
	speedV = 150;
	
	fireRate = 1.5;  
	fireTime = 0;     
	
	addCollider(new Collider_Circle(0, 0, 50, "col", 0));
	
	hp = 100;

	Temppx = px;
	isRight = true;
}

void Enemy::update()
{
	moveVer();
	moveHor();
	fireLaser();

	//화면 밖 삭제
	if (py > HEIGHT)
	{
		ObjectPool::delGameObject(this);
		GameScore++;
	}
}

void Enemy::OnCollision(GameObject * other, Collider * otherCol, Collider * myCol)
{
	if (strcmp(other->getName(), "player") == 0)
	{		
		other->DoDamage(this, 50);
	}
}

void Enemy::DoDamage(GameObject * fromObj, float d)
{
	hp = hp - (int)d;    

	if (hp <= 0)
	{
		//적기 폭발
		float x = px;
		float y = py;
		ObjectPool::addGameObject(new Exp_Enemy(x, y));
	
		ObjectPool::delGameObject(this);
		GameScore += 10;
	}
}

void Enemy::moveHor()
{
	float dt = getDeltaTime();
	
	float d = dt * speedH;

	//좌로이동
	if (px > Temppx + 100 || !isRight) 
	{
		isRight = false;
		if (!isRight)
		{
			translate(-d, 0);
		}
	}

	//우로이동
	if (px < Temppx - 100 || isRight)	
	{
		isRight = true;
		if (isRight)
		{
			translate(d, 0);
		}
	}
}

void Enemy::moveVer()
{
	float dt = getDeltaTime();
	float d = dt * speedV;

	translate(0, d);	
}

void Enemy::fireLaser()
{
	float dt = getDeltaTime();
	
	fireTime = fireTime + dt;

	if (fireTime >= fireRate)
	{		
		ObjectPool::addGameObject(new LaserE1(px + 25, py + 50));
		
		fireTime = 0;
	}
}