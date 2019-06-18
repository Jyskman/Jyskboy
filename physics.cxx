
// Phys engine


#include <iostream>
#include <vector>

#include "physics.h"


vector<physics> physics_objects;





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


physics * new_p = new physics(4, 0.90, 0);
physics_objects.push_back(*new_p);
delete new_p;



};
