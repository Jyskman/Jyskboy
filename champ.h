
// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef CHAMP_H
#define CHAMP_H


#include "buttons.h"
#include <iostream>
#include <vector>
#include "sprite_objects.h"
#include "physics.h"
//#include "render.h"
// This is the content of the .h file, which is where the declarations go




class champ {


public:
//champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter);
champ(int a, int size, int Height, int Width);	// constructor
int Relation_Spritenr_type();
int Relation_Spritenr_type_dev( int parameter );
bool sprite_error;
int render_req_mode = 2;
// hitbox contactpoints
int contact_points_all[2][12];

int internal_state;
bool contact_left;
bool contact_right;
bool contact_roof;
bool floor_contact;
bool roof_contact;
int gun_direction;
bool current_sprite_direction = true; // true is right orientation
bool current_sprite_v_direction = true; // true is oriented up, as sprite is drawn
int rotation = 1; // exp rotation parameter

bool general_contact;
vector<int> contact_position;
vector<render_state> RSV;
int x_location, y_location;
int height;
int width;
int sprite_size;

int palette_current;
int sprite_current;
int sprite_nr;
int current_form_info[10] = {101,102,0,0,0,0,0,0,25,30}; // sprite 1/sprite 2, 3, 4 plus indexes and hitbox size // probably obsolete
float x_velocity;
int y_velocity;


int x_max_speed;

int getHeight();
int getWidth();

int getX();
int getY();

int getSpriteSize();

void setX(int x);
void setY(int y);

void updatePos(button_input& parameter, physics& physics_parameter);
void setPos(button_input& parameter, physics& physics_parameter);
int getPalette();

unsigned char getChar(int x);
void setRender();
void setContactPoints();
void setContact(int room);
//vector<render_requests> *internal;

};


void champ_setup(champ &parameter);

// This is the end of the header guard
#endif


