#include "StartBG.h"
#include "input.h"

StartBG::StartBG(float px, float py) : GameObject("StartBG", 0, px, py)
{
}

StartBG::~StartBG()
{
}

void StartBG::init()
{
	readDDS("asset/Startbg.dds", &sprite);
}