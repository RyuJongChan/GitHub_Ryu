#pragma once

#include "Scene.h"

class Framework
{
private:	
	static Scene * scene;   
	static Scene * next;    

public:

	static bool isRun;   //���� ���� ���� ����

	static void init();    
	static void update();  
	static void exit();    

	static void LoadScene(Scene * newScene);

	static void QuitGame();
};