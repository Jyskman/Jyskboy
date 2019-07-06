#ifndef PHYS
#define PHYS

#include <vector>
#include <iostream>

using namespace::std;

class render_state {


public:
render_state(  bool floor_contact, int sprite_index );
render_state(  bool floor_contact,int x_offset, int y_offset, int sprite_index );

bool direction;
bool floor;


int index;
int sprite_nr;

int x_off;
int y_off;
};


class physics {

public:
physics( float g_force, float air_force, int index );

void setState(int param);
float getG(int state);

float g;
float air;
int state;

int vector_nr;
//int Relation_nr_type();

};



void physics_setup ();


extern vector<physics> physics_objects;


#endif // PHYS
