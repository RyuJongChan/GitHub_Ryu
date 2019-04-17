#pragma once

#include <Windows.h>

void initInput();
void updateInput();
void exitInput();

bool GetKey(int keyCode);
bool GetKeyUP(int keyCode);
bool GetKeyDown(int keyCode);

//현재 마우스 좌표 호출
POINT mousePosition();