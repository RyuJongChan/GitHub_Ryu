#pragma once

#include "Button.h"

class Button_GameStart : public Button
{
public:
	Button_GameStart(float px, float py);
	virtual ~Button_GameStart();
	
	virtual void init();	

	virtual void OnClick();
};

