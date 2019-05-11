
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
champ(int a, int size, int Height, int Width);	// constructor
int Relation_Spritenr_type();
bool sprite_error;

int x_location, y_location;
int height;
int width;
int sprite_size;

int palette_current;
int sprite_current;
int sprite_nr;

int getHeight();
int getWidth();

int getX();
int getY();

int getSpriteSize();

void setX(int x);
void setY(int y);

int getPalette();

unsigned char getChar(int x);
void setRender();

};



// This is the end of the header guard
#endif


