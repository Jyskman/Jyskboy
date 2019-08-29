#ifndef PHYS
#define PHYS

#include <vector>
#include <iostream>

using namespace::std;


class metronome {
public:
metronome( int cycles_per_increment, int reset_after_x_increments, int start_at_int, int idle_after_x_cycles );
int run();
int idle(int internal_state);
int cpi;
int raxi;
int sai;

int iaxc;
int idle_return;

int r1;
int r2;
int r3;
int return_value;
};





class render_state {


public:
render_state(  bool floor_contact, int sprite_index );
render_state(  bool f_c1, bool f_c2, bool w_c1, bool w_c2, bool r_c1, bool r_c2,int g_1, int g_2, int g_3, int g_4, int g_5, int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int x_offset, int y_offset, int sprite_index);

bool f_1;
bool f_2;
bool w_1;
bool w_2;
bool r_1;
bool r_2;

int gu_1;
int gu_2;
int gu_3;
int gu_4;
int gu_5;

int int_1;
int int_2;
int int_3;
int int_4;
int int_5;
int int_6;
int int_7;

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
