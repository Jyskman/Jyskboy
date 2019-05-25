// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef RENDER_H
#define RENDER_H



#include <iostream>
#include "render.h"
//~ #include "enemy.h"
#include "champ.h"

// This is the content of the .h file, which is where the declarations go
using namespace::std;

class render {


public:
int x_pos, y_pos;
int current_x_offset, current_y_offset;
int render_xlimit_upper, render_xlimit_lower, render_ylimit_upper, render_ylimit_lower;
//unsigned char render_array[240 + 20][320*2 + 20*2];
unsigned char render_array[240][320*2];
unsigned char *render_array_pointer;

unsigned char byte_1, byte_2;
unsigned char R_888_byte, G_888_byte, B_888_byte;

char test = 0;
bool return_value; // for the check function

unsigned short RGB565;

int offset = 0;

render(int a);	// constructor

void fillColor(int x, int y, unsigned short color);

void render_clear();


void filler_dev(champ& spritefiller);
void filler_general(int roomnr);


char getColor(int x, int y);

unsigned char mutateColor(int RGB ,unsigned char color, int palette);

// 0, 50, 100, 150, 200
unsigned char palette_1[5][3] = {

{0,0,0},
{140,50,90},
{230,60,150},
{0,255,150},
{255,255,0}

};

int mutate_Y(int y);
void determine_current_offset(champ& parameter, int roomnr);
bool render_limit_check(int x_pos, int y_pos);
};

// New render req class attempt


class render_requests {

public:
render_requests(int sprite_nr, int x_pos, int y_pos);
//~render_requests();
int sprite_nr;
int x_pos;
int y_pos;
bool draw;
int getSprite_nr();
int getX();
int getY();

};

extern vector<render_requests> render_req;

// This is the end of the header guard
#endif
