#pragma once
#include "Button.h"

class Button_TitleGo : public Button
{
private:

public:
	Button_TitleGo(float px, float py);
	virtual ~Button_TitleGo();

	virtual void init();

	virtual void OnClick();
};

