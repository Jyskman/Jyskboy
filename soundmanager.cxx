
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
Mix_Chunk *gJump = NULL;
Mix_Chunk *gLaser = NULL;
Mix_Chunk *gLaser_2 = NULL;
Mix_Chunk *gExplosion = NULL;

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


	
    gMusic = Mix_LoadMUS( "./audio/mystery.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        //success = false;
    }
	
	//Load sound effects
    gJump = Mix_LoadWAV( "./audio/Jump.wav" );
    if( gJump == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
    gLaser = Mix_LoadWAV( "./audio/laser.wav" );
    if( gLaser == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
    gLaser_2 = Mix_LoadWAV( "./audio/laser_2.wav" );
    if( gLaser_2 == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
    gExplosion = Mix_LoadWAV( "./audio/explosion.wav" );
    if( gExplosion == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        //~ success = false;
    }
    
	FX.push_back(*gExplosion); 	//0
	FX.push_back(*gLaser);		//1
	FX.push_back(*gLaser_2);	//2
	FX.push_back(*gJump); 		//3
    
};

void Close_audio() {

	// clear all objects from the FX vector
	//~ for (int i = 0; i < FX.size(); i++) {
	//~ Mix_FreeChunk( &FX.at(i) );
	//~ }
	//~ FX.clear();


    //Free the sound effects
    Mix_FreeChunk( gJump );
    Mix_FreeChunk( gLaser );
    Mix_FreeChunk( gLaser_2 );
    Mix_FreeChunk( gExplosion );
	
    gJump = NULL;
    gLaser = NULL;
    gLaser_2 = NULL;
    gExplosion = NULL;
      
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

void soundmanager::Play_FX( Mix_Chunk& parameter, int channel ) {
	//Mix_PlayChannel( -1, &FX.at(0), 0 );
	//~ Mix_Volume(1,50);
	Mix_PlayChannel( channel, &parameter, 0 );
};

void soundmanager::Play_Music() {
	
	if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			Mix_VolumeMusic(128);
			Mix_PlayMusic( gMusic, -1 );
		}	
	
};
