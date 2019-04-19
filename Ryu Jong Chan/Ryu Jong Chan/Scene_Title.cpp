#include "Scene_Title.h"
#include "StartBG.h"
#include "ObjectPool.h"
#include "Label.h"
#include "Button_GameStart.h"
#include "Button_Exit.h"
#include "Button_Explain.h"

#include <iostream>

Scene_Title::Scene_Title()
{
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::init()
{
	GameObject::GameScore = 0;
	GameObject::Life = 3;

	char title[] = "WHAT'S YOUR CHOICE ";	
	char avoid[] = "<AVOID>";
	char orr[] = "OR ";
	char kill[] = "<KILL>?";
	char name[] = "클라이언트 프로그래머 지원자 = 유종찬";
	
	char ttf[] = "asset/godoMaum.ttf";

	ObjectPool::addGameObject(new StartBG(0, 0));

	ObjectPool::addGameObject(new Label(title, ttf, 48, 0x0000ff, 400, 100, 0));
	ObjectPool::addGameObject(new Label(avoid, ttf, 48, 0xff0000, 800, 100, 0));
	ObjectPool::addGameObject(new Label(orr, ttf, 48, 0x0000ff, 980, 100, 0));
	ObjectPool::addGameObject(new Label(kill, ttf, 48, 0xff0000, 1050, 100, 0));

	ObjectPool::addGameObject(new Label( name, ttf, 24, 0xffffff, 250, 50, 0));	

	ObjectPool::addGameObject(new Button_Explain(1000, 350));
	ObjectPool::addGameObject(new Button_GameStart(1000, 400));
	ObjectPool::addGameObject(new Button_Exit(1000, 450));
}