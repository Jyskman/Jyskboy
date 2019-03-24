
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include "soundmanager.h"


std::vector<int> FX_Req; // global variable for requests of FX sound
std::vector<Mix_Chunk> FX;


Mix_Music *gMusic = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

void Load_audio() {

	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
       
    }
    //Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		
	}


	
    gMusic = Mix_LoadMUS( "./audio/beat.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        //success = false;
    }
	
	//Load sound effects
    gScratch = Mix_LoadWAV( "./audio/scratch.wav" );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
    gHigh = Mix_LoadWAV( "./audio/high.wav" );
    if( gHigh == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
    gMedium = Mix_LoadWAV( "./audio/medium.wav" );
    if( gMedium == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
    gLow = Mix_LoadWAV( "./audio/low.wav" );
    if( gLow == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
	FX.push_back(*gLow);
	FX.push_back(*gHigh);
	FX.push_back(*gMedium);
	FX.push_back(*gScratch); 
    
};

void Close_audio() {

    //Free the sound effects
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMedium );
    Mix_FreeChunk( gLow );
    gScratch = NULL;
    gHigh = NULL;
    gMedium = NULL;
    gLow = NULL;
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;


    //Quit SDL subsystems
    Mix_Quit();
    //~ IMG_Quit();
    SDL_Quit();
};


soundmanager::soundmanager() {
	Load_audio();
};

void soundmanager::Play_FX( Mix_Chunk& parameter ) {
	//Mix_PlayChannel( -1, &FX.at(0), 0 );
	Mix_PlayChannel( -1, &parameter, 0 );
};

void soundmanager::Play_Music() {
	
	if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			Mix_PlayMusic( gMusic, -1 );
		}	
	
};
