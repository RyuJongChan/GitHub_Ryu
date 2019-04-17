#pragma once

#include "Button.h"

class Button_Exit :	public Button
{
public:
	Button_Exit(float px, float py);
	virtual ~Button_Exit();
	
	virtual void init();	

	virtual void OnClick();
};