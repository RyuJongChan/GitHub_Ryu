#include "Score.h"
#include "Label.h"
#include "Player.h"

Score::Score(float px, float py) : GameObject("score", 2, px, py)
{
	
}

Score::~Score()
{
}

void Score::init()
{	
	ScoreLabel = new Label("0", "asset/godoMaum.ttf", 40, 0xffffff, 20, 10, 3);
	addChildObject(ScoreLabel, 2);

	LifeLabel = new Label("3", "asset/godoMaum.ttf", 40, 0xffffff, 20, 58, 3);
	addChildObject(LifeLabel, 2);
}

void Score::update()
{	
	char ScoreView[64];
	sprintf_s(ScoreView, "SCORE = %d", GameObject::GameScore);
	ScoreLabel->setText(ScoreView);

	char LifeView[64];
	sprintf_s(LifeView, "  LIFE = %d", GameObject::Life);
	LifeLabel->setText(LifeView);
}