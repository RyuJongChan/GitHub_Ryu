#include <stdio.h>
#include "input.h"

#define KEY_UP_REP    0
#define KEY_DOWN      1
#define KEY_DOWN_REP  2
#define KEY_UP        3

//state[255]는 키보드에 있는 모든 키의 상태를 저장하는 배열로..확장
//배열의 방번호(인덱스)와 키의 번호를 일치시켜서...키의 상태를 배열에 저장함
int state[255];    //0-이전에 키가 계속 놓임 
				   //1-이전에 키가 놓임==>눌림
				   //2-이전에 키가 계속 눌림
				   //3-이전에 키가 눌림==>놓임	

HWND GetConsoleHwnd();

HWND InputhWnd;

void initInput()
{
	//(1)모든 키상태를 0 으로 만들고 시작함
	for (int i = 0; i < 255; i++)
	{
		state[i] = KEY_UP_REP;    //// 모든 키의 상태를 KEY_UP_REP 으로 초기화함
	}

	//(2)콘솔 윈도우 핸들 구하기...
	InputhWnd = GetConsoleHwnd();
}

void updateInput()
{
	int key;

	for (int i = 1; i < 255; i++)  //i=1,2,3,4....254 증가...각 i 는 번호에 해당하는 키값이됨
	{
		key = GetAsyncKeyState(i);  //i 번째 키가 눌렸는지를 조사함

		if (state[i] == KEY_UP_REP)   //이전에 키가 놓여있는 상태임
		{
			if ((key & 0x8000) == 0x8000)  //키가 눌림
			{
				state[i] = KEY_DOWN;       //i 번째 키가 노임==>눌림으로 변경되었음을..state[i]번째 배열에 저장함
			}
			else {

			}
		}
		else if (state[i] == KEY_DOWN) {  //키가 놓임==>눌림

			if ((key & 0x8000) == 0x8000)  //키가 눌림
			{
				state[i] = KEY_DOWN_REP;
			}
			else { //키가 놓임
				state[i] = KEY_UP;
			}

		}
		else if (state[i] == KEY_DOWN_REP) {   //키가 계속 눌림

			if ((key & 0x8000) == 0x8000)   //키가 계속 눌리고 있음
			{
			}
			else {  //키가 놓임
				state[i] = KEY_UP;
			}
		}
		else if (state[i] == KEY_UP) {   //키가 눌림==>놓임

			if ((key & 0x8000) == 0x8000)//눌림
			{
				state[i] = KEY_DOWN;
			}
			else {
				state[i] = KEY_UP_REP;
			}
		}
	}
}

void exitInput()
{

}

bool GetKey(int keyCode)   //키가 눌리고 있는 동안에 true를 반환함
{
	//키를 조사하고 싶은 .. 키번호가 keyCode 인데...해당키번호의 상태는 state[keyCode] 배열에 있음
	if (state[keyCode] == KEY_DOWN || state[keyCode] == KEY_DOWN_REP)
	{
		return true;
	}
	else {
		return false;
	}
}

bool GetKeyUP(int keyCode)   //키가 눌렸다가..놓일때만...true
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

bool GetKeyDown(int keyCode)   //키가 놓였다가..눌릴때만...true
{
	if (state[keyCode] == KEY_DOWN)
	{
		return true;
	}
	else {
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