#pragma once

#include "Scene.h"
#include "Label.h"

class Scene_GameExplain :	public Scene
{
private:
	Label *VectorKey;
	Label *SpaceKey;
	Label *EscKey;
	Label *ExplainWord;
	Label *Warning;

public:
	Scene_GameExplain();
	virtual ~Scene_GameExplain();

	virtual void init();
};

