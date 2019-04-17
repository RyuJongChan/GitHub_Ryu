#include "Scene_EndGame.h"
#include "ObjectPool.h"
#include "graphic.h"
#include "Button_TitleGo.h"
#include "Button_Exit.h"

Scene_EndGame::Scene_EndGame()
{
}


Scene_EndGame::~Scene_EndGame()
{
}

void Scene_EndGame::init()
{
	ExitScoreLabel = new Label("", "asset/godoMaum.ttf", 64, 0xffffff, (WIDTH / 2 - 250), HEIGHT / 2, 0);
	ObjectPool::addGameObject(ExitScoreLabel);

	char LastScoreView[64];
	sprintf_s(LastScoreView, "LAST SCORE = %d", GameObject::GameScore);
	ExitScoreLabel->setText(LastScoreView);

	ObjectPool::addGameObject(new Button_TitleGo((WIDTH / 2 - 250), HEIGHT / 2 + 300));
	ObjectPool::addGameObject(new Button_Exit((WIDTH / 2), HEIGHT / 2 + 300));
}