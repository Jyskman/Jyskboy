
// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef CHAMP_H
#define CHAMP_H



#include <iostream>
#include <vector>
#include "sprite_objects.h"
// This is the content of the .h file, which is where the declarations go




class champ {


public:
//champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter);
champ(int a, int size, int Height, int Width, std::vector<sprite_objects>& parameter);	// constructor


int x_location, y_location;
int height;
int width;
int sprite_size;


struct color_palette {
// Black; Grey;
// 0; 50; 100; 150; 200
    int current_palette = 1;
    unsigned char palette[2][5] =  {{0,0,0,0,0},
                                    {0,0,0,0,0}};

};

std::vector<unsigned char> imported;
//unsigned char imported_sprite[3001];



int getHeight();
int getWidth();

int getX();
int getY();

int getSpriteSize();

void setX(int x);
void setY(int y);


unsigned char getChar(int x);
unsigned char getVector(int x);

//struct getPalette();
};



// This is the end of the header guard
#endif


