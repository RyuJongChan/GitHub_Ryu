#include "Framework.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>

int main()
{	
	Framework::init();
	system("mode 160, 60");

	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 10, 10, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	while (Framework::isRun == true)
	{
		Framework::update();
	}

	Framework::exit();

	return 0;
}