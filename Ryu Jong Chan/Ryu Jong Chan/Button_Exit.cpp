#include "Button_Exit.h"
#include "Framework.h"

Button_Exit::Button_Exit(float px, float py) : Button(px, py)
{
}

Button_Exit::~Button_Exit()
{
}

void Button_Exit::init()
{	
	readDDS("asset/ButtonN.dds", &imageN);	
	readDDS("asset/ButtonP.dds", &imageP);

	sprite = imageN;  
	
	label = new Label("Á¾·á", "asset/godoMaum.ttf", 32, 0xffffff, 24, 12, 0);
	addChildObject(label);
}

void Button_Exit::OnClick()
{	
	Framework::QuitGame();
}