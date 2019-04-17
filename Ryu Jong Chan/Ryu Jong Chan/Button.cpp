#include "Button.h"
#include "input.h"
#include "graphic.h"
#include "timer.h"

Button::Button(float px, float py) : GameObject("button", 3, px, py)
{
	label      = NULL;  
	btnState   = BNormal;
	clickDelay = (float)CLICKDEALY; 
}

Button::~Button()
{
	sprite.argb = NULL;

	////메모리 해제
	delete[] imageN.argb;
	delete[] imageP.argb;
}

void Button::init()
{
}

void Button::update()
{
	if (btnState == BNormal) 
	{		
		if (GetKeyDown(VK_LBUTTON) == true)  
		{
			int x0, y0;  //버튼의 좌상단 좌표
			int x1, y1;  //버튼의 우하단 좌표

			x0 = (int)px;
			y0 = (int)py + STARTY;

			x1 = x0 + sprite.width;
			y1 = y0 + sprite.height;

			//마우스 좌표
			POINT mouse = mousePosition();

			if (x1 > mouse.x && mouse.x > x0)	//가로 축좌표
			{
				if (y1 > mouse.y && mouse.y > y0)	//세로 축좌표
				{
					sprite   = imageP;      
					btnState = BPress;          
					
					if (label != NULL)
					{
						label->translate(0, 2);		//텍스트 위치도 아래로 이동
					}
				}
			}
		}
	}

	else if (btnState == BPress)
	{  		
		if (GetKeyUP(VK_LBUTTON) == true)
		{
			sprite   = imageN;    
			btnState = BClick;

			if (label != NULL)
			{
				label->translate(0, -2);	//텍스트 위치 원래 위치로
			}
		}
	}

	else if (btnState == BClick) 
	{  	
		clickDelay = clickDelay - getDeltaTime();

		if (clickDelay <= 0)
		{
			OnClick();                
			btnState   = BNormal;     
			clickDelay = (float)CLICKDEALY;  
		}
	}
}

void Button::OnClick()
{
	
}