#ifndef PHYS
#define PHYS

#include <vector>
#include <iostream>
//~ #include "setup_sprites.h"

using namespace::std;

class animation_profile {

public:
animation_profile( int type, int profile_index, int min_cycle, int max_cycle );

int profile_type;
int animation_index;
int animation_nr;
int min_c, max_c;

vector<int> animate_from_cycle;
vector<int> animate_to_cycle;
vector<int> animate_type;
vector<int> animate_main_index;
vector<int> animate_main_nr;
vector<int> animate_sub_index_1;
vector<bool> animate_subject_to_physics;
vector<bool> animate_quad;
vector<bool> animate_duo;

void load_animate_from_cycle(int value);
void load_animate_to_cycle(int value);
void load_animate_type(int value);
void load_animate_main_index(int value);
void load_animate_sub_index_1(int value);
void load_animate_physics(bool value);
void load_animate_quad(bool value);
void load_animate_duo(bool value);
void set_sprite_numbers();
void set_to_from_cycles(int type);


};



class hitbox_object {


public:
hitbox_object ( int x_upper_left, int y_upper_left, int x_lower_right, int y_lower_right );

int x_u_left;
int y_u_left;
int x_l_right;
int y_l_right;
void test();

};




class attack {
// attack class used by game object, will be linked somehow to weaponprofiles also in game
public:
void render_attacks();
void update();
attack( int type, int damage, int x_pos, int y_pos, int x_vel, int y_vel, int rotation, bool horisontal, bool vertical, int gun_sprite_nr, bool cross, bool shoot_direction, int hitboxtype, int cycles );

int a_rot;
int a_damage;
int a_gun_sprite_nr;
bool a_horisontal;
bool a_vertical;
bool a_cross;

int cycles_to_terminate;
int current_cycle = 0;

bool shooter_direction;

int hitbox_type;

int a_type;
int a_x_pos;
int a_y_pos;
int a_x_vel;
int a_y_vel;

int mid_x, mid_y;

bool destroy;

vector<hitbox_object> attack_hitbox;
void setup_hitbox();
};

class weaponProfile {
public:
weaponProfile(int sprite_index, int sprite_index_rotation, int x_velocity, int y_velocity, int set_damage, int hitbox_type, int cycles);
int hitbox_t;
int weapon_sprite;
int weapon_sprite_rot;
int damage;
int sprite_nr;
int sprite_nr_rot;
int cycles_to_terminate;

int x_vel;
int y_vel;
};




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
render_state(  bool static_, int sprite_index );
render_state(  bool f_c1, bool f_c2, bool w_c1, bool w_c2, bool r_c1, bool r_c2,int g_1, int g_2, int g_3, int g_4, int g_5, int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int x_offset, int y_offset, int sprite_index);
// Overload RSV med gun true false
render_state(  bool is_gun ,bool f_c1, bool f_c2, bool w_c1, bool w_c2, bool r_c1, bool r_c2,int g_1, int g_2, int g_3, int g_4, int g_5, int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int x_offset, int y_offset, int sprite_index);

render_state( bool special_offset, int special_index, bool is_gun ,bool f_c1, bool f_c2, bool w_c1, bool w_c2, bool r_c1, bool r_c2,int g_1, int g_2, int g_3, int g_4, int g_5, int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int x_offset, int y_offset, int sprite_index);


bool is_g;

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

bool use_special_offset;
int use_special_index;


int RSV_x_store, RSV_y_store;


// For advanced loader 
bool Advanced;  
bool grab;
bool static_;

};


class physics {

public:
physics( float g_force, float air_force, int index );
physics( int index, float set_new_g, float set_new_air_density, int extra_parameter );

void calculate_velocity( float &v_parameter, float &v_x_parameter , float Area_factor, float Area_x_fraction );

void setState(int param);
float getG(int state);

float g;
float air;
int state;
int vector_nr;
//int Relation_nr_type();

float new_g;
float new_air_density;

float current_drag;
int sign;

};



void physics_setup ();


extern vector<physics> physics_objects;
extern vector<animation_profile> animation_profiles;

void modifier_random( int &number, int maximum, int minimum );
float modifier_random_float( float number, int maximum, bool negative_possibility );

// hitbox objects



// Item updrade class
class item {
	
	public:

	item( int item_nr, int x, int y );	
	int index_nr( int index );
	int nr;
	int x_pos, y_pos;
	int sprite_index;
	int sprite_nr;
	void render_item();
	void setup();
	
	
};









#endif // PHYS
