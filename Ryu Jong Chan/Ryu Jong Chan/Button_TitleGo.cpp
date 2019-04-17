#include "Button_TitleGo.h"
#include "Framework.h"
#include "Scene_Title.h"

Button_TitleGo::Button_TitleGo(float px, float py) : Button(px, py)
{
}

Button_TitleGo::~Button_TitleGo()
{
}

void Button_TitleGo::init()
{	
	readDDS("asset/ButtonN.dds", &imageN);	
	readDDS("asset/ButtonP.dds", &imageP);

	sprite = imageN; 
	
	label = new Label("시작 화면", "asset/godoMaum.ttf", 26, 0xffffff, 8, 12, 0);
	addChildObject(label);
}

void Button_TitleGo::OnClick()
{	
	Framework::LoadScene(new Scene_Title());
}