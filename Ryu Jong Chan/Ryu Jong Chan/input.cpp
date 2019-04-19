#include <stdio.h>
#include "input.h"

//0-이전에 키가 계속 놓임 
//1-이전에 키가 놓임==>눌림
//2-이전에 키가 계속 눌림
//3-이전에 키가 눌림==>놓임	
#define KEY_UP_REP    0 
#define KEY_DOWN      1
#define KEY_DOWN_REP  2
#define KEY_UP        3

int state[255];    

HWND GetConsoleHwnd();

HWND InputhWnd;

void initInput()
{	
	for (int i = 0; i < 255; i++)
	{
		state[i] = KEY_UP_REP;   
	}

	//콘솔 윈도우 핸들
	InputhWnd = GetConsoleHwnd();
}

void updateInput()
{
	int key;

	for (int i = 1; i < 255; i++)  
	{
		key = GetAsyncKeyState(i);  

		if (state[i] == KEY_UP_REP)   
		{
			if ((key & 0x8000) == 0x8000)  
			{
				state[i] = KEY_DOWN;       
			}

			else 
			{

			}
		}

		else if (state[i] == KEY_DOWN)
		{  
			if ((key & 0x8000) == 0x8000) 
			{
				state[i] = KEY_DOWN_REP;
			}
			else 
			{ 
				state[i] = KEY_UP;
			}

		}
		else if (state[i] == KEY_DOWN_REP) 
		{  
			if ((key & 0x8000) == 0x8000)   
			{
			}

			else 
			{ 
				state[i] = KEY_UP;
			}
		}

		else if (state[i] == KEY_UP) 
		{   
			if ((key & 0x8000) == 0x8000)
			{
				state[i] = KEY_DOWN;
			}

			else
			{
				state[i] = KEY_UP_REP;
			}
		}
	}
}

void exitInput()
{

}

bool GetKey(int keyCode)   
{	
	if (state[keyCode] == KEY_DOWN || state[keyCode] == KEY_DOWN_REP)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool GetKeyUP(int keyCode)  
{
	if (state[keyCode] == KEY_UP)
	{
		return true;
	}

	else 
	{
		return false;
	}
}

bool GetKeyDown(int keyCode)  
{
	if (state[keyCode] == KEY_DOWN)
	{
		return true;
	}

	else 
	{
		return false;
	}
}

POINT mousePosition()
{
	POINT point;

	GetCursorPos(&point);
	ScreenToClient(InputhWnd, &point);  //마우스 좌표 >> 클라이언트 영역으로 

	return point;

	//printf("마우스 위치(%d %d)\n", point.x, point.y);
}