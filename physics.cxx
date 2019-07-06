
// Phys engine


#include <iostream>
#include <vector>

#include "physics.h"
#include "setup_sprites.h"

vector<physics> physics_objects;


render_state::render_state( bool floor_contact, int sprite_index) {

//direction = direction_condition;
floor = floor_contact;
index = sprite_index;

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

render_state::render_state( bool floor_contact, int x_offset, int y_offset, int sprite_index) {

//direction = direction_condition;
floor = floor_contact;
index = sprite_index;

x_off = x_offset;
y_off = y_offset;

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


physics * new_p = new physics(6, 0.90, 0);
physics_objects.push_back(*new_p);
delete new_p;



};
