#pragma once

#include <Windows.h>

void initInput();
void updateInput();
void exitInput();

bool GetKey(int keyCode);
bool GetKeyUP(int keyCode);
bool GetKeyDown(int keyCode);

//���� ���콺 ��ǥ ȣ��
POINT mousePosition();