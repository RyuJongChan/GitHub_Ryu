#include "Sound.h"

#pragma comment(lib, "fmod/lib/fmod_vc.lib")

FMOD_SYSTEM  * Sound::system = NULL;

Sound::Sound(const char * filename, bool loop):GameObject("sound",-1,0,0)
{	
    if (loop == true)   //반복재생
    {
        if (FMOD_System_CreateSound(system, filename, FMOD_LOOP_NORMAL, NULL, &sound) != FMOD_OK)
        {
            printf("Fmod 사운드 생성 실패\n");
        }
    }

    else 
	{  
        if (FMOD_System_CreateSound(system, filename, FMOD_DEFAULT, NULL, &sound) != FMOD_OK)
        {
            printf("Fmod 사운드 생성 실패\n");
        }
    }
      
    FMOD_System_PlaySound(system, sound, NULL, false, &channel);
}

Sound::~Sound()
{ 
    FMOD_Channel_Stop(channel);
    FMOD_Sound_Release(sound);
}

void Sound::init()
{
    if (FMOD_System_Create(&system) != FMOD_OK)
    {
        printf("Fmod 시스템 생성 에러\n");
    }

    if (FMOD_System_Init(system, 64 , FMOD_INIT_NORMAL, NULL) != FMOD_OK)
    {
        printf("Fmod 사운드 초기화 실패\n");
    }
}

void Sound::exit()
{
    FMOD_System_Close(system);
}