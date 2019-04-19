#include "Sound.h"

#pragma comment(lib, "fmod/lib/fmod_vc.lib")

FMOD_SYSTEM  * Sound::system = NULL;

Sound::Sound(const char * filename, bool loop):GameObject("sound",-1,0,0)
{	
    if (loop == true)   
    {
        if (FMOD_System_CreateSound(system, filename, FMOD_LOOP_NORMAL, NULL, &sound) != FMOD_OK)
        {
            printf("Fmod Sound create failed\n");
        }
    }

    else 
	{  
        if (FMOD_System_CreateSound(system, filename, FMOD_DEFAULT, NULL, &sound) != FMOD_OK)
        {
            printf("Fmod Sound create failed\n");
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
        printf("Fmod System create error\n");
    }

    if (FMOD_System_Init(system, 64 , FMOD_INIT_NORMAL, NULL) != FMOD_OK)
    {
        printf("Fmod Sound init failed\n");
    }
}

void Sound::exit()
{
    FMOD_System_Close(system);
}