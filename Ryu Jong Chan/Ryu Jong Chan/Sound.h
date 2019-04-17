#pragma once

#include "GameObject.h"
#include "fmod/inc/fmod.h"

class Sound : public GameObject
{
private:    
    static FMOD_SYSTEM  * system;
 
    FMOD_SOUND   * sound;
    FMOD_CHANNEL * channel;

public:
    Sound(const char * filename, bool loop);
    virtual ~Sound();

    static void init();
    static void exit();
};
