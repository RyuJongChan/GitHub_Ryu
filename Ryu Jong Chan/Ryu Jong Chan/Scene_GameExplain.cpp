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

	VectorKey = new Label("���� Ű : �÷��̾� �̵�\n", "asset/godoMaum.ttf", 32, 0xffffff, 900, 50, 0);
	ObjectPool::addGameObject(VectorKey,2);

	SpaceKey = new Label ("SPACE  : �߻�\n", "asset/godoMaum.ttf", 32, 0xffffff, 900, 100, 0);
	ObjectPool::addGameObject(SpaceKey, 2);

	EscKey = new Label   ("ESC     : ����\n", "asset/godoMaum.ttf", 32, 0xffffff, 900, 150, 0);
	ObjectPool::addGameObject(EscKey, 2);

	ExplainWord = new Label("�־��� LIFE 3���� ���� ���ϰų� ���Ľ��� SCORE�� �÷���!\n", "asset/godoMaum.ttf", 32, 0xffffff, 100, 50, 0);
	ObjectPool::addGameObject(ExplainWord, 2);

	Warning = new Label("����! : ������ ���� �� ���� SCORE����\n", "asset/godoMaum.ttf", 32, 0xffffff, 100, 100, 0);
	ObjectPool::addGameObject(Warning, 2);
}
