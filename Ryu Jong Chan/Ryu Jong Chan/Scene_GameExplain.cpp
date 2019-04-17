#include "Scene_GameExplain.h"
#include "Player.h"
#include "ObjectPool.h"
#include "Label.h"
#include "Button_TitleGo.h"

Scene_GameExplain::Scene_GameExplain() : Scene()
{
}

Scene_GameExplain::~Scene_GameExplain()
{
}

void Scene_GameExplain::init()
{
	ObjectPool::addGameObject(new Player(500, 700), 1);
	ObjectPool::addGameObject(new Button_TitleGo(1100, 800));

	VectorKey = new Label("방향 키 : 플레이어 이동\n", "asset/godoMaum.ttf", 32, 0xffffff, 900, 50, 0);
	ObjectPool::addGameObject(VectorKey,2);

	SpaceKey = new Label ("SPACE  : 발사\n", "asset/godoMaum.ttf", 32, 0xffffff, 900, 100, 0);
	ObjectPool::addGameObject(SpaceKey, 2);

	EscKey = new Label   ("ESC     : 종료\n", "asset/godoMaum.ttf", 32, 0xffffff, 900, 150, 0);
	ObjectPool::addGameObject(EscKey, 2);

	ExplainWord = new Label("주어진 LIFE 3개로 적을 피하거나 폭파시켜 SCORE를 올려라!\n", "asset/godoMaum.ttf", 32, 0xffffff, 100, 50, 0);
	ObjectPool::addGameObject(ExplainWord, 2);

	Warning = new Label("주의! : 라이프 잃을 때 마다 SCORE감점\n", "asset/godoMaum.ttf", 32, 0xffffff, 100, 100, 0);
	ObjectPool::addGameObject(Warning, 2);
}
