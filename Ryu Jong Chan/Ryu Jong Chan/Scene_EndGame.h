#pragma once

#include "Scene.h"
#include "Label.h"

class Scene_EndGame : public Scene
{
private:
	Label *ExitScoreLabel;

public:
	Scene_EndGame();
	virtual ~Scene_EndGame();

	virtual void init();
};

