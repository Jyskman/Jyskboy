
// Phys engine


#include <iostream>
#include <vector>
#include "render.h"
#include "physics.h"
#include "setup_sprites.h"
#include <cstdlib>
#include <math.h>

using namespace std;


vector<physics> physics_objects;
vector<animation_profile> animation_profiles;

// profiles that will be used in anim req system
animation_profile::animation_profile(int type, int profile_index, int min_cycle, int max_cycle) {
profile_type = type;
animation_index = profile_index;
min_c = min_cycle;
max_c = max_cycle;



};

void animation_profile::set_sprite_numbers() {
    int return_value = 0;

    for ( int i = 0; i < animate_main_index.size(); i++ ) {

        for (int j = 0; j < all_sprites.size(); j++ ) {

           if ( all_sprites.at(j).sprite_index == animate_main_index.at(i) ) {
                return_value = j;
                animate_main_nr.push_back(return_value);
                //cout << return_value << endl;
            } else {

            };

        };

    };


};

void animation_profile::set_to_from_cycles(int type) {

    float lower, upper;
    int lower_int, upper_int;

    switch (type) {

        case(1):
        break;
        case(2):

            for ( int i = 0; i < animate_main_index.size(); i++ ) {

                lower = i * ( (float)max_c / (float)animate_main_index.size() );
                upper = ( (float)max_c / (float)animate_main_index.size() ) + i * ( (float)max_c / (float)animate_main_index.size() );

                lower_int = (int)lower;
                upper_int = (int)upper;

                animate_from_cycle.push_back(  lower_int  )  ;
                animate_to_cycle.push_back( upper_int )  ;
                //cout << lower_int << ".--." << upper_int << endl;



            }


        break;
        case(3):

                for ( int i = 0; i < animate_main_index.size(); i++ ) {

                lower = i * ( (float)max_c / (float)animate_main_index.size() );
                upper = ( (float)max_c / (float)animate_main_index.size() ) + i * ( (float)max_c / (float)animate_main_index.size() );

                lower_int = (int)lower;
                upper_int = (int)upper;

                animate_from_cycle.push_back(  lower_int  )  ;
                animate_to_cycle.push_back( upper_int )  ;
                //cout << lower_int << ".--." << upper_int << endl;



            }
        break;
        default:
        break;


    };



}


void animation_profile::load_animate_from_cycle( int value ) {

animate_from_cycle.push_back(value);

};

void animation_profile::load_animate_to_cycle( int value ) {

animate_to_cycle.push_back(value);

};

void animation_profile::load_animate_type( int value ) {

animate_type.push_back(value);

};

void animation_profile::load_animate_main_index( int value ) {

animate_main_index.push_back(value);

};

void animation_profile::load_animate_sub_index_1( int value ) {

animate_sub_index_1.push_back(value);

};

void animation_profile::load_animate_physics(bool value) {

animate_subject_to_physics.push_back(value);
};

void animation_profile::load_animate_quad(bool value) {

animate_quad.push_back(value);
};

void animation_profile::load_animate_duo(bool value) {

animate_duo.push_back(value);
};


hitbox_object::hitbox_object ( int x_upper_left, int y_upper_left, int x_lower_right, int y_lower_right ) {

x_u_left = x_upper_left;
y_u_left = y_upper_left ;
x_l_right = x_lower_right ;
y_l_right = y_lower_right ;

};

void hitbox_object::test() {};




weaponProfile::weaponProfile(int sprite_index, int sprite_index_rotation, int x_velocity, int y_velocity, int set_damage, int hitbox_type) {

        weapon_sprite = sprite_index;
        weapon_sprite_rot = sprite_index_rotation;
        damage = set_damage;
        x_vel = x_velocity;
        y_vel = y_velocity;
        hitbox_t = hitbox_type;

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


void attack::setup_hitbox() {
        int x_base = 0;
        int y_base = 0;
        int x_off = 0 ;
        int y_off = 0;



switch (hitbox_type) {


    case (1): {




        x_base = 0;
        y_base = 0;
        x_off = all_sprites.at(a_type).getWidth() ;
        y_off = all_sprites.at(a_type).getHeight();

        if (a_rot == 2) {

        x_base = 0;
        y_base = 0;
        x_off = all_sprites.at(a_type).getHeight();
        y_off = all_sprites.at(a_type).getWidth();

        } else {

        }



        if (a_cross == true ) {
        //cout << shooter_direction << endl;
            if ( shooter_direction == true ) {
                x_base = all_sprites.at(a_type).getWidth()/2;
                y_base = all_sprites.at(a_type).getHeight()/2;

                x_off = all_sprites.at(a_type).getWidth();
                y_off = 0;

                    if ( a_rot == 2 ) {
                    x_base = all_sprites.at(a_type).getWidth()/2;
                    y_base = all_sprites.at(a_type).getHeight()/2;

                    x_off = all_sprites.at(a_type).getWidth();
                    y_off = all_sprites.at(a_type).getHeight();


                    } else {
                    };



            } else {
            // Horisontal false
                x_base = 0;
                y_base = 0;

                x_off = all_sprites.at(a_type).getWidth()/2;
                y_off = all_sprites.at(a_type).getHeight()/2;

                    if ( a_rot == 2 ) {

                    x_base = 0;
                    y_base = all_sprites.at(a_type).getHeight();

                    x_off = all_sprites.at(a_type).getWidth()/2;
                    y_off = all_sprites.at(a_type).getHeight()/2;


                    } else {
                    };

            };




        } else {
        };




     break;
    }
    case (2):

        x_base = all_sprites.at(a_type).getWidth()/2;
        y_base = 1 - all_sprites.at(a_type).getHeight()/2;
        x_off =  all_sprites.at(a_type).getWidth()/2;
        y_off =  1 + all_sprites.at(a_type).getHeight()/2;

        if (a_rot == 2) {

        x_base = 2 - all_sprites.at(a_type).getHeight()/2;
        y_base = all_sprites.at(a_type).getWidth()/2;
        x_off = 1 + all_sprites.at(a_type).getHeight()/2;
        y_off =  all_sprites.at(a_type).getWidth()/2;

        } else {

        }


        if (a_cross == true ) {
        //cout << shooter_direction << endl;
            if ( shooter_direction == true ) {
            x_base = all_sprites.at(a_type).getWidth()/2;
            y_base = (all_sprites.at(a_type).getHeight()/2) -2 ;

            x_off = all_sprites.at(a_type).getWidth()/2;
            y_off = (all_sprites.at(a_type).getHeight()/2) +1;

                if ( a_rot == 2 ) {
                x_base = all_sprites.at(a_type).getWidth()/2;
                y_base = (all_sprites.at(a_type).getHeight()/2) -2 ;

                x_off = all_sprites.at(a_type).getWidth()/2;
                y_off = (all_sprites.at(a_type).getHeight()/2) + 1;


                } else {
                };



            } else {
            // Horisontal false
            x_base = all_sprites.at(a_type).getWidth()/2;
            y_base = (all_sprites.at(a_type).getHeight()/2) -2 ;

            x_off = all_sprites.at(a_type).getWidth()/2;
            y_off = (all_sprites.at(a_type).getHeight()/2) +1;

                if ( a_rot == 2 ) {

                x_base = all_sprites.at(a_type).getWidth()/2;
                y_base = (all_sprites.at(a_type).getHeight()/2) -2 ;

                x_off = all_sprites.at(a_type).getWidth()/2;
                y_off = (all_sprites.at(a_type).getHeight()/2) +1;


                } else {
                };

            };




        } else {
        };

    break;

    case (3):


        if ( shooter_direction == false ) {
            x_base = -0*all_sprites.at(a_type).getWidth()/1;
            y_base = 1 - all_sprites.at(a_type).getHeight()/2;
            x_off =  -0*all_sprites.at(a_type).getWidth()/1;
            y_off =  1 + all_sprites.at(a_type).getHeight()/2;

        } else {

            x_base = all_sprites.at(a_type).getWidth()/1;
            y_base = 1 - all_sprites.at(a_type).getHeight()/2;
            x_off =  all_sprites.at(a_type).getWidth()/1;
            y_off =  1 + all_sprites.at(a_type).getHeight()/2;

        };



        if (a_rot == 2) {

            if ( a_vertical == 0 ) {

                x_base = 2 - all_sprites.at(a_type).getHeight()/2;
                y_base = 1*all_sprites.at(a_type).getWidth()/1;
                x_off = 1 + all_sprites.at(a_type).getHeight()/2;
                y_off =  1*all_sprites.at(a_type).getWidth()/1;

            } else {
            // a_vertical == 1
                x_base = 2 - all_sprites.at(a_type).getHeight()/2;
                y_base = 0*all_sprites.at(a_type).getWidth()/1;
                x_off = 1 + all_sprites.at(a_type).getHeight()/2;
                y_off =  0*all_sprites.at(a_type).getWidth()/1;

            }

        } else {

        }



        if (a_cross == true ) {
        cout << a_rot << endl;
            if ( shooter_direction == true ) {
            x_base = all_sprites.at(a_type).getWidth() - 3;
            y_base = 4 + 0*all_sprites.at(a_type).getHeight() ;

            x_off = all_sprites.at(a_type).getWidth() - 3;
            y_off = 1 + 0*all_sprites.at(a_type).getHeight();

                if ( a_rot == 2 ) {
                x_base = all_sprites.at(a_type).getWidth() - 3;
                y_base = -5 + 1*all_sprites.at(a_type).getHeight() ;

                x_off = all_sprites.at(a_type).getWidth() - 3;
                y_off = -2 + 1*all_sprites.at(a_type).getHeight();


                } else {
                };



            } else {
            // Horisontal false
            x_base = 0*all_sprites.at(a_type).getWidth() + 2;
            y_base = 4 + 0*all_sprites.at(a_type).getHeight() ;

            x_off = 0*all_sprites.at(a_type).getWidth() + 2;
            y_off = 1 + 0*all_sprites.at(a_type).getHeight();

                if ( a_rot == 2 ) {
                x_base = 0*all_sprites.at(a_type).getWidth() + 2;
                y_base = -5 + 1*all_sprites.at(a_type).getHeight() ;

                x_off = 0*all_sprites.at(a_type).getWidth() + 2;
                y_off = -2 + 1*all_sprites.at(a_type).getHeight();


                } else {
                };

            };




        } else {
        };


    break;



};





        hitbox_object * obj = new hitbox_object(x_base,y_base,x_off,y_off );
        attack_hitbox.push_back( *obj );
        delete obj;

};


attack::attack(int type, int damage, int x_pos, int y_pos, int x_vel, int y_vel, int rotation, bool horisontal, bool vertical, int gun_sprite_nr, bool cross, bool shoot_direction, int hitboxtype ) {

    a_cross = cross;
    a_type = type;
    a_x_pos = x_pos;
    a_y_pos = y_pos;
    a_x_vel = x_vel;
    a_y_vel = y_vel;
    hitbox_type = hitboxtype;
    a_damage = damage;
    shooter_direction = shoot_direction;

    a_horisontal = horisontal;
    a_vertical = vertical;

    a_rot = rotation;
    setup_hitbox();

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

    //render_primitive_line(a_x_pos + attack_hitbox.at(0).x_u_left, a_y_pos + attack_hitbox.at(0).y_u_left, a_x_pos + attack_hitbox.at(0).x_l_right , a_y_pos+attack_hitbox.at(0).y_l_right, 1, 401);

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
use_special_offset = false;

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
use_special_offset = false;

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

render_state::render_state( bool special_offset, int special_index, bool is_gun, bool f_c1, bool f_c2, bool w_c1, bool w_c2, bool r_c1, bool r_c2,int g_1, int g_2, int g_3, int g_4, int g_5, int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int x_offset, int y_offset, int sprite_index) {

is_g = is_gun; // for use with weapon profile and attack offset
use_special_offset = special_offset;
use_special_index = special_index;

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

physics::physics( int index, float set_new_g, float set_new_air_density, int extra_parameter) {

new_g = set_new_g;
new_air_density = set_new_air_density;
state = index;

};

void physics::calculate_velocity(float &v_parameter, float &v_x_parameter, float Area_factor, float Area_x_fraction) {

     sign = -1;
    if ( v_parameter < 0 ) {
        sign = 1;
    } else {
    }


    v_parameter = v_parameter + new_g;

    //current_drag = (Area_factor * Shape_C_factor * new_air_density) * v_parameter*v_parameter;
    current_drag = (float)sign * ( Area_factor * new_air_density ) * v_parameter*v_parameter;

    if ( abs(current_drag) < 0.001 ) {
        current_drag = 0.00;
    } else {
    }


    v_parameter = v_parameter + current_drag;
    //cout << v_parameter << endl;

    // x velocity
         sign = 1;
    if ( v_x_parameter < 0 ) {
        sign = -1;
    } else {
    }

    current_drag = (float)sign * ( Area_factor*Area_x_fraction * new_air_density ) * v_x_parameter*v_x_parameter;

    if ( abs(current_drag) < 0.02 ) {
        current_drag = 0.00;
    } else {
    }
    v_x_parameter = v_x_parameter - current_drag;
    //cout << v_parameter << endl;
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


//physics * new_p = new physics(8, 0.90, 0);
physics * new_p = new physics(0, 0.8, 0.111, 5);

physics_objects.push_back(*new_p);
delete new_p;



};

void modifier_random( int &number, int maximum, int minimum ) {

 number = number - rand() % maximum + minimum ;     // v2 in the range 1 to 100

};

float modifier_random_float( float number, int maximum, bool negative_possibility ) {

    int random = rand() % maximum;

    if ( rand() % 2 == 0 && negative_possibility == true ) {
        random = random * -1;

    } else {
        random = random * -1;
    }



    number = number + (float)random ;     // v2 in the range 1 to 100

    return number;

};
