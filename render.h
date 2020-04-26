// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef RENDER_H
#define RENDER_H



#include <iostream>

//~ #include "enemy.h"
#include "champ.h"
#include "enemy.h"

// This is the content of the .h file, which is where the declarations go
using namespace::std;

void particle_generator( int x_pos, int y_pos, int animation_type_as_index , int animation_type, bool random_v, int cycles, int random_factor );
void particle_generator( int x_pos, int y_pos, int animation_type_as_index , int animation_type, int v_x, int v_y, int cycles );
//specific for detruction of enemies
void particle_generator( enemy *parameter, int x_pos, int y_pos, int cycles );


void render_requests_quad( int sprite_nr, int x_loc, int y_loc, bool white_border, bool center, bool right_orientation );
void render_requests_dual( int sprite_nr, int x_loc, int y_loc, bool white_border, bool center, bool center_orientation );
void render_primitive_line( int x_start, int y_start, int x_stop, int y_stop, int orientation, int sprite_index );

class render_requests {

public:
render_requests(int sprite_nr, int x_pos, int y_pos, int palette);
render_requests(int sprite_nr, int x_pos, int y_pos, bool static_);
render_requests(int sprite_nr, int x_pos, int y_pos, int palette, bool right_orientation, bool up_orientation, int rot);

//~render_requests();
int sprite_nr;
int sprite_index;
int x_pos;
int y_pos;
bool draw;
bool draw_evaluate;
bool orientation;
bool up_down;
int rotation;
bool static_render = false;

bool checkers;

int getSprite_nr();
int current_palette;

bool getDraw(const render_requests & o);


int getX();
int getY();

};

extern vector<render_requests> render_req;


// Will create general animation req system
class animation_requests {

public:
animation_requests(int animation_nr_as_index, int animation_nr, int rot, bool facing_right, bool facing_up ,int cycles_to_terminate, int x_start, int y_start, int x_vel_start, int y_vel_start);
animation_requests( int profile_index, int x_start, int y_start, int x_vel_start, int y_vel_start );

animation_requests(int *x_start, int *y_start, int x_vel_start, int y_vel_start, bool upgrade_scan );

int update_position_case = 0;

int sprite_width;
int rotation = 1;
int anime_nr, x, y, x_v, y_v, cycles, sprite_nr, sprite_index, current_cycle, profile_nr;
int * x_pos;
int * y_pos;
bool destroy = false;
void sprite_setup( int index );
void profile_setup( int profile_index_parameter );
void render_animation();
void update_position( physics &parameter, int room );
void modifier();
void animation_as_index();
int animation_as_nr;

int state =1;

bool right_orientation;
bool up_orientation;

float x_v_float, y_v_float, x_float, y_float;
int x_offset;

bool front = true;

};

extern vector<animation_requests> anime_req;

class render {


public:

int null_static = 1;
vector<render_requests> *internal;
int x_pos, y_pos;
int current_x_offset, current_y_offset;
int render_xlimit_upper, render_xlimit_lower, render_ylimit_upper, render_ylimit_lower;
int offset_parameter_x_left, offset_parameter_x_right;
int offset_parameter_y_low, offset_parameter_y_up;

int horisontal_p1; // for inversion based on direction parameter
int horisontal_p2; //for inversion based on direction parameter
int vertical_p1; // for inversion based on direction parameter
int vertical_p2; //for inversion based on direction parameter

int rotation_p1;
int rotation_p2;
int render_limit_p1;
int render_limit_p2;

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
// Below is fillcolor dev version
void fillColor_dev(int x, int y, unsigned char color, unsigned char color2 );

void render_clear();


void filler_dev(int roomnr);
void filler_general(int roomnr);


char getColor(int x, int y);

unsigned char mutateColor(int &RGB ,unsigned char &color, int &palette);

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
void render_req_filter();
int filter_w;
int filter_h;

//Will start with 10 hardcoded palettes with 5 color
unsigned char palettes_R[5][10] = {
    {0,  0,0,0,0,0,0,0,0,0},
    {140,0,0,0,0,0,0,0,0,0},
    {230,0,0,0,0,0,0,0,0,0},
    {0,  0,0,0,0,0,0,0,0,0},
    {255,0,0,0,0,0,0,0,0,0}
};
unsigned char palettes_G[5][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {50,0,0,0,0,0,0,0,0,0},
    {60,0,0,0,0,0,0,0,0,0},
    {255,0,0,0,0,0,0,0,0,0},
    {255,0,0,0,0,0,0,0,0,0}
};
unsigned char palettes_B[5][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {90,0,0,0,0,0,0,0,0,0},
    {150,0,0,0,0,0,0,0,0,0},
    {150,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

int R = 0, G = 1, B = 2;
int testpal = 0;
unsigned char palettes_RGB[15][10] = {
    {0,  0,0,0,0,0,0,0,0,0},
    {140,0,0,0,0,0,0,0,0,0},
    {230,0,0,0,0,0,0,0,0,0},
    {0,  0,0,0,0,0,0,0,0,0},
    {255,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {50,0,0,0,0,0,0,0,0,0},
    {60,0,0,0,0,0,0,0,0,0},
    {255,0,0,0,0,0,0,0,0,0},
    {255,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {90,0,0,0,0,0,0,0,0,0},
    {150,0,0,0,0,0,0,0,0,0},
    {150,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}

};


// render will need to store the info of sprites, size and adress for increased speed and reduction of global vector variables. will need to remove all palette stuff prob
vector<unsigned char*> sprite_address;
vector<int> sprite_w;
vector<int> sprite_h;

void load_sprite_data( unsigned char* add, int width, int height );
vector<render_requests> internal_render_requests;
};

// New render req class attempt




// This is the end of the header guard
#endif
