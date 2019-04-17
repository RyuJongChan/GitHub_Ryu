#pragma once

#include "Button.h"

class Button_Explain : public Button
{
public:
	Button_Explain(float px, float py);
	virtual ~Button_Explain();
	
	virtual void init();	

	virtual void OnClick();
};

