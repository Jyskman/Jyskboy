// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef RENDER_H
#define RENDER_H
 
 

#include <iostream>
#include "render.h"
//~ #include "enemy.h"
#include "champ.h"

// This is the content of the .h file, which is where the declarations go




class render {
	
	
public:
unsigned char render_array[240 + 20][320*2 + 20*2];

unsigned char byte_1, byte_2;
unsigned char R_888_byte, G_888_byte, B_888_byte;

char test = 0;

unsigned short RGB565;

int offset = 0;

render(int a);	// constructor

void fillColor(int x, int y, unsigned short color);

void clear();

void filler(champ& spritefiller);

unsigned char getColor(int x, int y);
	
};



// This is the end of the header guard
#endif
