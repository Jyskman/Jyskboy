#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <iostream>
#include "physics.h"




class enemy {



public:
enemy(int e_type);

int x_location, y_location;
int enemy_type;
bool destroy = false;

// Render stuff
vector<render_state> RSV;
vector<hitbox_object> enemy_hitbox_set;
void set_hitbox_set();
void setRender();
void test();
int render_req_mode = 2;
int internal_state = 1;

bool contact_left = false;
bool contact_right = false;
bool contact_roof = false;
bool floor_contact = false;
bool roof_contact = false;
int gun_direction = 3;
int jump_counter = 1;

bool sprite_error = false;
bool can_take_damage;
int life;

bool current_sprite_direction = true; // true is right orientation
bool current_sprite_v_direction = true; // true is oriented up, as sprite is drawn
int rotation = 1; // exp rotation parameter
int height = 30;
int width = 25;
bool general_contact;
int x_mirror_gun, RSV_x_gun, RSV_y_gun, rot_gun, gun_sprite_nr;
bool horisontal_gun, vertical_gun;
int palette_current = 1;

void RSV_setup();
void vulnerability_setup();

int enemy_offset[2][10];

void resolve_damage( vector<attack> &parameter );

};


void create_and_reset_enemies( int room_nr, vector<enemy>& parameter );








#endif // EN
