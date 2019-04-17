#include "Scene_InGame.h"
#include "Label.h"
#include "ObjectPool.h"
#include "Player.h"
#include "Spawn.h"
#include "Clock.h"
#include "Sound.h"
#include "Score.h"

Scene_InGame::Scene_InGame()
{
}


Scene_InGame::~Scene_InGame()
{
}

void Scene_InGame::init()
{	
	//사운드 출력
	ObjectPool::addGameObject(new Sound("asset/Sound/BGM.wav", true));
	
	ObjectPool::addGameObject(new Spawn(100, -150, 4));  
	ObjectPool::addGameObject(new Spawn(250, -200, 3));   
	ObjectPool::addGameObject(new Spawn(500, -50, 4));   
	ObjectPool::addGameObject(new Spawn(750, -200, 3));  
	ObjectPool::addGameObject(new Spawn(1000, -150, 4));  
	

	ObjectPool::addGameObject(new Clock(10, 10));
	ObjectPool::addGameObject(new Score(1000, 10));
	ObjectPool::addGameObject(new Player(500, 700), 1);		//player layer = 1
}