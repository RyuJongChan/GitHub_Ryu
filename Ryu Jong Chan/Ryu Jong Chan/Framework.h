#pragma once

#include "Scene.h"

class Framework
{
private:	
	static Scene * scene;   
	static Scene * next;    

public:

	static bool isRun;   //게임 진행 상태 변수

	static void init();    
	static void update();  
	static void exit();    

	static void LoadScene(Scene * newScene);

	static void QuitGame();
};