#include "Button_GameStart.h"
#include "Framework.h"
#include "Scene_InGame.h"

Button_GameStart::Button_GameStart(float px, float py) : Button(px, py)
{
}

Button_GameStart::~Button_GameStart()
{
}

void Button_GameStart::init()
{	
	readDDS("asset/ButtonN.dds", &imageN);	
	readDDS("asset/ButtonP.dds", &imageP);

	sprite = imageN; 

	label = new Label("Ω√¿€", "asset/godoMaum.ttf", 32, 0xffffff, 24, 12, 0);
	addChildObject(label);
}

void Button_GameStart::OnClick()
{	
	Framework::LoadScene(new Scene_InGame());
}