#include "Player.h"
#include "timer.h"
#include "input.h"
#include <stdio.h>
#include "LaserP.h"       
#include "ObjectPool.h"   
#include "Collider_AABB.h"         
#include "Collider_Circle.h"       
#include "Jet.h"
#include "Exp_Player.h"
#include "Shield.h"
#include "Label.h"
#include "Framework.h"
#include "Scene_EndGame.h"
#include "Score.h"
#include "graphic.h"

Player::Player(float px, float py) : GameObject("player",0, px, py)
{			
}

Player::~Player()
{
}

void Player::init()
{	
	readDDS("asset/Player.dds", &sprite);
	speed = 300;
	ShieldState = true;
	
	fireRate = (float)0.2;   
	fireTime = 0;     
	
	addChildObject(new Jet(45, 70));
	addChildObject(new Jet(55, 70));
	
	shield = new Shield(-20, -30);   
	addChildObject(shield);          

	shieldLifeTime = 5;             	
	
	hp = 100;
	only = 1;	
	state = 0;
	
	HpLabel = new Label("유종찬HP = ", "asset/godoMaum.ttf", 20, 0xffffff, 10, 100, 0);
	addChildObject(HpLabel);
}

void Player::update()
{		
	PlayerController();
}

    /*
	(1)Hp View
	(2)ESC 종료
	(3)재소환시 초기이동
	(4)Player 이동, 발사
	(5)Player 실드
	*/	
void Player::PlayerController()
{
	//Hp View
	char HpView[64];
	sprintf_s(HpView, "유종찬HP = %d", hp);
	HpLabel->setText(HpView);

	//게임 종료
	if (GetKey(VK_ESCAPE) == true)
	{
		Framework::LoadScene(new Scene_EndGame());
	}

	//이동속도
	float d = getDeltaTime() * speed;

	//플레이어 재소환 초기 이동
	if (state == 0)
	{
		translate(0, -d);

		if (py < 700)
		{
			state = 1;
		}
	}
	else if (state == 1)
	{
		fireTime = fireTime + getDeltaTime();

		//플레이어 이동
		//좌
		if (px <= (WIDTH - WIDTH))
		{
			px = (WIDTH - WIDTH);
		}
		else if (GetKey(VK_LEFT) == true && px > (WIDTH - WIDTH + 20))
		{
			translate(-d, 0);
		}

		//우
		if (px >= (WIDTH - 150))
		{
			px = (WIDTH - 150);

		}
		else if (GetKey(VK_RIGHT) == true && px < (WIDTH - 170))
		{
			translate(d, 0);
		}

		//상
		if (py <= (HEIGHT - HEIGHT)) py = (HEIGHT - HEIGHT);

		else if (GetKey(VK_UP) == true && py > (HEIGHT - HEIGHT + 20))
		{
			translate(0, -d);
		}

		//하
		if (py >= HEIGHT - 200) py = (HEIGHT - 200);

		else if (GetKey(VK_DOWN) == true && py < HEIGHT - 220)
		{
			translate(0, d);
		}

		//발사
		if (GetKey(VK_SPACE) == true && fireTime >= fireRate)
		{
			ObjectPool::addGameObject(new LaserP(px + 40, py - 50), 1);
			ObjectPool::addGameObject(new LaserP(px + 60, py - 50), 1);

			fireTime = 0;
		}
	}

	//실드
	shieldLifeTime -= getDeltaTime();
	if (shieldLifeTime <= 0)
	{
		delChildObject(shield);
		if (shieldLifeTime < -0.2 && ShieldState)
		{
			ShieldState = false;

			this->addCollider(new Collider_AABB(10, 30, 88, 36, "body", 0));
		}
	}
}

void Player::OnCollision(GameObject * other, Collider * otherCol, Collider * myCol)
{
	if (other->getTag() == 1)
	{		
		other->DoDamage(this, 100);	
	}
}

void Player::DoDamage(GameObject * fromObj, float d)
{	
	hp = hp - (int)d;

	if (hp <= 0 && !ShieldState)
	{		
		float x = px;
		float y = py;

		//플레이어 폭발 
		ObjectPool::addGameObject(new Exp_Player(x, y));
			
		ObjectPool::delGameObject(this);
	
		GameObject::Life--;

		//Life = 0, 게임 종료
		if (GameObject::Life == 0)
		{
			Framework::LoadScene(new Scene_EndGame());
		}

		//재소환
		else if (only == 1)
		{
			only = 0;
			
			ObjectPool::addGameObject(new Player(500, 800));	
			GameScore -= 100;
		}
	}
}