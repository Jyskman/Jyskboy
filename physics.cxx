
// Phys engine


#include <iostream>
#include <vector>
#include "render.h"
#include "physics.h"
#include "setup_sprites.h"

vector<physics> physics_objects;


weaponProfile::weaponProfile(int sprite_index, int sprite_index_rotation, int x_velocity, int y_velocity) {

        weapon_sprite = sprite_index;
        weapon_sprite_rot = sprite_index_rotation;

        x_vel = x_velocity;
        y_vel = y_velocity;

        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == weapon_sprite ) {
                sprite_nr = i;

            } else {

            };
        };
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == weapon_sprite_rot ) {
                sprite_nr_rot = i;

            } else {

            };
        };

};




attack::attack(int type, int x_pos, int y_pos, int x_vel, int y_vel, int rotation, bool horisontal, bool vertical, int gun_sprite_nr ) {

    a_type = type;
    a_x_pos = x_pos;
    a_y_pos = y_pos;
    a_x_vel = x_vel;
    a_y_vel = y_vel;

    a_horisontal = horisontal;
    a_vertical = vertical;
    a_rot = rotation;


    destroy = false;

};

void attack::update_and_render() {

    // move according to velocity
    a_x_pos = a_x_pos + a_x_vel;
    a_y_pos = a_y_pos + a_y_vel;
    // render
    // render_requests * obj = new render_requests(RSV.at(i).sprite_nr, RSV_x-x_mirror, RSV_y, palette_current,horisontal, vertical, rot);

    render_requests * obj = new render_requests(a_type, a_x_pos, a_y_pos, 1, a_horisontal, a_vertical, a_rot);
    render_req.push_back(*obj);
    delete obj;

};



metronome::metronome(int cycles_per_increment, int reset_after_x_increments, int start_at_int, int idle_after_x_cycles){
cpi = cycles_per_increment;
raxi = reset_after_x_increments;
sai = start_at_int;

iaxc = idle_after_x_cycles;

r1 = start_at_int;
r2 = 0;
r3 = 0;
};

int metronome::run(){

r2++;
if ( r2 > cpi ) {
r2 = 0;
r1++;
} else {
}

if (r1 > raxi){
r1 = sai;
} else {
};

r3 = 0;
return r1;
};

int metronome::idle( int internal_state ) {
r3++;
if ( r3 > iaxc ) {
    idle_return = 7;
    r3 = 0;
} else {
    idle_return = internal_state;
}

return idle_return;
};


render_state::render_state( bool floor_contact, int sprite_index) {

//direction = direction_condition;
//floor = floor_contact;
//index = sprite_index;

x_off = 0;
y_off = 0;

        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == index ) {
                sprite_nr = i;
                //sprite_error = false;
                //width = all_sprites.at(i).getWidth();
                //height = all_sprites.at(i).getHeight();

            } else {

            };
        };

};

render_state::render_state( bool f_c1, bool f_c2, bool w_c1, bool w_c2, bool r_c1, bool r_c2,int g_1, int g_2, int g_3, int g_4, int g_5, int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int x_offset, int y_offset, int sprite_index) {

f_1 = f_c1;
f_2 = f_c2;
w_1 = w_c1;
w_2 = w_c2;
r_1 = r_c1;
r_2 = w_c2;

gu_1 = g_1;
gu_2 = g_2;
gu_3 = g_3;
gu_4 = g_4;
gu_5 = g_5;

int_1 = i_1;
int_2 = i_2;
int_3 = i_3;
int_4 = i_4;
int_5 = i_5;
int_6 = i_6;
int_7 = i_7;

is_g = false;

x_off = x_offset;
y_off = y_offset;
index = sprite_index;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == index ) {
                sprite_nr = i;
                //sprite_error = false;
                //width = all_sprites.at(i).getWidth();
                //height = all_sprites.at(i).getHeight();

            } else {

            };
        };

};

render_state::render_state( bool is_gun, bool f_c1, bool f_c2, bool w_c1, bool w_c2, bool r_c1, bool r_c2,int g_1, int g_2, int g_3, int g_4, int g_5, int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int x_offset, int y_offset, int sprite_index) {

is_g = is_gun; // for use with weapon profile and attack offset

f_1 = f_c1;
f_2 = f_c2;
w_1 = w_c1;
w_2 = w_c2;
r_1 = r_c1;
r_2 = w_c2;

gu_1 = g_1;
gu_2 = g_2;
gu_3 = g_3;
gu_4 = g_4;
gu_5 = g_5;

int_1 = i_1;
int_2 = i_2;
int_3 = i_3;
int_4 = i_4;
int_5 = i_5;
int_6 = i_6;
int_7 = i_7;

is_g = is_gun;

x_off = x_offset;
y_off = y_offset;
index = sprite_index;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == index ) {
                sprite_nr = i;
                //sprite_error = false;
                //width = all_sprites.at(i).getWidth();
                //height = all_sprites.at(i).getHeight();

            } else {

            };
        };

};



physics::physics( float g_force, float air_force, int index ) {

g = g_force;
air = air_force;

state = index;

};


void physics::setState(int param) {
    state = param;
};


float physics::getG(int state) {

};


//int physics::Relation_nr_type() {
//    int return_value = 0;
//        for (int i=0; i < physics_objects.size(); i++) {
//            if ( physics_objects.at(i).sprite_index == block_type ) {
//                return_value = i;
//                //cout << return_value << endl;
//            } else {
//
//            };
//        };
//
//    return return_value;
//
//};






void physics_setup() {


physics * new_p = new physics(8, 0.90, 0);
physics_objects.push_back(*new_p);
delete new_p;



};
