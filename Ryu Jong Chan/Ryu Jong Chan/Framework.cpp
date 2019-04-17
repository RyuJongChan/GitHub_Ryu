#include "Framework.h"
#include "graphic.h"
#include "input.h"
#include "timer.h"
#include "Scene_InGame.h"
#include "Scene_EndGame.h"
#include "Scene_Title.h"
#include "Sound.h"

Scene * Framework::scene = NULL;
Scene * Framework::next  = NULL;   

bool Framework::isRun    = true;

void Framework::init()
{
	initGraphic();
	initTimer();
	initInput();

    Sound::init();  
	
	scene = new Scene_Title();	
	scene->init();
}

void Framework::update()
{	
	clear(0, 0, 0);
	updateInput();
	updateTimer();

	scene->update();
	scene->checkCol();
	scene->draw();
	scene->clear();
	
	render();

	//Scene 전환
	if (next != NULL)   
	{
		//현재Scene 삭제
		scene->exit(); 
		delete scene;

		//next Scene로드
		scene = next;
		scene->init();

		next = NULL;
	}
}

void Framework::exit()
{	
	scene->exit();
    Sound::exit();
}

void Framework::QuitGame()
{
	Framework::isRun = false;
	exit();
}

void Framework::LoadScene(Scene * newScene)
{
	next = newScene;  
}