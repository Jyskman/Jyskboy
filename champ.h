
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
bool sprite_error;

// hitbox contactpoints
int contact_points[2][8];
int contact_points_plus[2][4];
int contact_points_all[2][12];

bool contact_left;
bool contact_right;
bool contact_roof;
bool floor_contact;
bool roof_contact;
bool general_contact;
vector<int> contact_position;

int x_location, y_location;
int height;
int width;
int sprite_size;

int palette_current;
int sprite_current;
int sprite_nr;

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



// This is the end of the header guard
#endif


