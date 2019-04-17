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

	////�޸� ����
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
			int x0, y0;  //��ư�� �»�� ��ǥ
			int x1, y1;  //��ư�� ���ϴ� ��ǥ

			x0 = (int)px;
			y0 = (int)py + STARTY;

			x1 = x0 + sprite.width;
			y1 = y0 + sprite.height;

			//���콺 ��ǥ
			POINT mouse = mousePosition();

			if (x1 > mouse.x && mouse.x > x0)	//���� ����ǥ
			{
				if (y1 > mouse.y && mouse.y > y0)	//���� ����ǥ
				{
					sprite   = imageP;      
					btnState = BPress;          
					
					if (label != NULL)
					{
						label->translate(0, 2);		//�ؽ�Ʈ ��ġ�� �Ʒ��� �̵�
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
				label->translate(0, -2);	//�ؽ�Ʈ ��ġ ���� ��ġ��
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