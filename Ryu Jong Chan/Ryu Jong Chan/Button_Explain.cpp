#include "Button_Explain.h"
#include "Framework.h"
#include "Scene_GameExplain.h"

Button_Explain::Button_Explain(float px, float py) : Button(px,py)
{
}


Button_Explain::~Button_Explain()
{
}

void Button_Explain::init()
{	
	readDDS("asset/ButtonN.dds", &imageN);	
	readDDS("asset/ButtonP.dds", &imageP);

	sprite = imageN;  
	 
	label = new Label("게임 설명", "asset/godoMaum.ttf", 26, 0xffffff, 8, 12, 0);
	addChildObject(label);
}

void Button_Explain::OnClick()
{	
	Framework::LoadScene(new Scene_GameExplain());
}