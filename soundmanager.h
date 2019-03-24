
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


extern std::vector<int> FX_Req; // global variable for requests of FX sound
extern std::vector<Mix_Chunk> FX;


void Load_audio();
void Close_audio();

class soundmanager {
	
public:
soundmanager(); //constructor
void Play_FX(Mix_Chunk& parameter );
void Play_Music();

private:

	
};




#endif 
