#pragma once

#include "GameObject.h"
#include "Label.h"

class Score : public GameObject
{
private:
	Label *ScoreLabel;
	Label *LifeLabel;

public:		
	Score(float px, float py);
	virtual ~Score();

	virtual void init();
	virtual void update();
};

