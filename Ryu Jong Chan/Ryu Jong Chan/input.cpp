#include <stdio.h>
#include "input.h"

#define KEY_UP_REP    0
#define KEY_DOWN      1
#define KEY_DOWN_REP  2
#define KEY_UP        3

//state[255]�� Ű���忡 �ִ� ��� Ű�� ���¸� �����ϴ� �迭��..Ȯ��
//�迭�� ���ȣ(�ε���)�� Ű�� ��ȣ�� ��ġ���Ѽ�...Ű�� ���¸� �迭�� ������
int state[255];    //0-������ Ű�� ��� ���� 
				   //1-������ Ű�� ����==>����
				   //2-������ Ű�� ��� ����
				   //3-������ Ű�� ����==>����	

HWND GetConsoleHwnd();

HWND InputhWnd;

void initInput()
{
	//(1)��� Ű���¸� 0 ���� ����� ������
	for (int i = 0; i < 255; i++)
	{
		state[i] = KEY_UP_REP;    //// ��� Ű�� ���¸� KEY_UP_REP ���� �ʱ�ȭ��
	}

	//(2)�ܼ� ������ �ڵ� ���ϱ�...
	InputhWnd = GetConsoleHwnd();
}

void updateInput()
{
	int key;

	for (int i = 1; i < 255; i++)  //i=1,2,3,4....254 ����...�� i �� ��ȣ�� �ش��ϴ� Ű���̵�
	{
		key = GetAsyncKeyState(i);  //i ��° Ű�� ���ȴ����� ������

		if (state[i] == KEY_UP_REP)   //������ Ű�� �����ִ� ������
		{
			if ((key & 0x8000) == 0x8000)  //Ű�� ����
			{
				state[i] = KEY_DOWN;       //i ��° Ű�� ����==>�������� ����Ǿ�����..state[i]��° �迭�� ������
			}
			else {

			}
		}
		else if (state[i] == KEY_DOWN) {  //Ű�� ����==>����

			if ((key & 0x8000) == 0x8000)  //Ű�� ����
			{
				state[i] = KEY_DOWN_REP;
			}
			else { //Ű�� ����
				state[i] = KEY_UP;
			}

		}
		else if (state[i] == KEY_DOWN_REP) {   //Ű�� ��� ����

			if ((key & 0x8000) == 0x8000)   //Ű�� ��� ������ ����
			{
			}
			else {  //Ű�� ����
				state[i] = KEY_UP;
			}
		}
		else if (state[i] == KEY_UP) {   //Ű�� ����==>����

			if ((key & 0x8000) == 0x8000)//����
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

bool GetKey(int keyCode)   //Ű�� ������ �ִ� ���ȿ� true�� ��ȯ��
{
	//Ű�� �����ϰ� ���� .. Ű��ȣ�� keyCode �ε�...�ش�Ű��ȣ�� ���´� state[keyCode] �迭�� ����
	if (state[keyCode] == KEY_DOWN || state[keyCode] == KEY_DOWN_REP)
	{
		return true;
	}
	else {
		return false;
	}
}

bool GetKeyUP(int keyCode)   //Ű�� ���ȴٰ�..���϶���...true
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

bool GetKeyDown(int keyCode)   //Ű�� �����ٰ�..��������...true
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
	ScreenToClient(InputhWnd, &point);  //���콺 ��ǥ >> Ŭ���̾�Ʈ �������� 

	return point;

	//printf("���콺 ��ġ(%d %d)\n", point.x, point.y);
}