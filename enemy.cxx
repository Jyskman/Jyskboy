
// Enemy base class

#include "enemy.h"
#include "setup_sprites.h"
#include <iostream>
#include "physics.h"
#include <math.h>
#include <cstdlib>
#include "environment.h"

using namespace std;
// E



void enemy::perception(champ &parameter) {

float param_x = (float)center_x + (float)x_location;
float param_y = (float)center_y + (float)y_location;

        perception_distance = sqrt( ( param_x - parameter.x_center )*( param_x - parameter.x_center )+( param_y - parameter.y_center )*( param_y - parameter.y_center ) );
        // direction to champ
        perception_angle = (  ( parameter.x_center - param_x )/( perception_distance )  );
        //cout << "angle" << acos(cos_alfa) << endl;
        //champ_direction =  0;
        if ( parameter.y_center > param_y ) {
            perception_above = false;
            //cout << "is below" << endl;
        } else {
            perception_above = true;
            //cout << "is above" << endl;
        }

        // left or right?
        if ( parameter.x_center > param_x ) {
            perception_right = true;
            //cout << "C is right" << endl;
        } else {
            perception_right = false;
            //cout << "C is left" << endl;
        }



};





void enemy::motion( physics &parameter ) {

//length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) )
    switch ( enemy_type ) {

        case(1):

            y_v_float = y_v_float - parameter.new_g;

            if ( perception_right == true ) {

                x_v_float = x_v_float + main_v;
            } else {
                x_v_float = x_v_float - main_v;
            }

            if ( perception_above == true ) {

                y_v_float = y_v_float - main_v;
            } else {
                y_v_float = y_v_float + main_v;
            }



        break;
        case(2):
        break;
        default:
        break;



    };

    parameter.calculate_velocity( y_v_float, x_v_float, 0.050, 1);


    x_location_prev = x_location;
    y_location_prev = y_location;


    //y_v_float = 0;
    x_location = x_location + (int)x_v_float;
    y_location = y_location + (int)y_v_float;

    previous_x.push_back(x_location + width );
    previous_y.push_back(y_location + height );
    //previous_y.push_back(y_location);
    previous_x.erase( previous_x.begin() + 0 );
    previous_y.erase( previous_y.begin() + 0 );



    if ( (x_location - x_location_prev) > 0 ) {
        current_sprite_direction = false;
    } else {
        current_sprite_direction = true;
    };


};



void enemy::set_hitbox_set() {

    switch (enemy_type) {

        case (1):

            for ( int i = 0; i < RSV.size() ; i++ ) {

                hitbox_object * obj = new hitbox_object(0,0, all_sprites.at( RSV.at(i).sprite_nr ).getWidth(), all_sprites.at( RSV.at(i).sprite_nr ).getHeight() );
                enemy_hitbox_set.push_back( *obj );
                delete obj;

                if ( RSV.at(i).use_special_offset == false ) {
                    center_x = all_sprites.at( RSV.at(i).sprite_nr ).getWidth() / 2;
                    center_y = all_sprites.at( RSV.at(i).sprite_nr ).getHeight() / 2;

                } else {
                };

            };

        break;
        case (2):
        break;
        default:
        break;



    }



};




void enemy::RSV_setup() {


    if ( enemy_type == 1 ) {


        for (int i = 0; i < 10; i++) {
            previous_x.push_back(0);
            previous_y.push_back(0);
        };
        //cout << previous_x.size() << endl;


        render_state * state_1_1 = new render_state( true, 1, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 207 );
        RSV.push_back(*state_1_1);
        delete state_1_1;

        render_state * state_1_2 = new render_state(true, 2, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 207 );
        RSV.push_back(*state_1_2);
        delete state_1_2;

        render_state * state_1_3 = new render_state(false, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 208 );
        RSV.push_back(*state_1_3);
        delete state_1_3;


        //Offset setup prototype
        //all_sprites.at(RSV.at(1).sprite_nr).getWidth() +2;
        enemy_offset[0][2] = 0 ; // first object x offset
        enemy_offset[1][2] = 0 ; // first object y offset
        // enemy has a main width and height which mirror x is based on, set below
        width = all_sprites.at(RSV.at(2).sprite_nr).getWidth();
        height = all_sprites.at(RSV.at(2).sprite_nr).getHeight();


        enemy_offset[0][1] = all_sprites.at(RSV.at(2).sprite_nr).getWidth() - 2 ; // first object x offset
        enemy_offset[1][1] = 0 ; // first object y offset

        enemy_offset[0][0] = enemy_offset[0][1] + all_sprites.at(RSV.at(0).sprite_nr).getWidth() - 2 ; // first object x offset
        enemy_offset[1][0] = 0 ; // first object y offset

        for ( int i = 0; i < RSV.size(); i++ ) {
            RSV.at(i).x_off = enemy_offset[0][i];
            RSV.at(i).y_off = enemy_offset[1][i];

        }


    }


}

void enemy::vulnerability_setup() {

    switch (enemy_type) {

        case (1):
            can_take_damage = true;
            life = 1;
        break;
        case (2):
        break;
        default:
        break;


    }


};


enemy::enemy( int e_type, int start_x, int start_y) {

x_location = start_x ;
y_location = start_y ;
enemy_type = e_type;
vector<hitbox_object> enemy_hitbox_set;
vector<render_state> RSV;
vector<int> previous_x;
RSV_setup(); // also height and width main properties
vulnerability_setup();
set_hitbox_set();
destroy = false;
    switch (e_type) {
        case(1):
            main_v = 0.20;
        break;

    };


};

void enemy::test() {
cout << "Func ok" << endl;
};

void enemy::resolve_damage( vector<attack> &parameter, champ &hero_parameter ) {

//E
int X_1_A = 0;
int X_2_A = 0;
int Y_1_A = 0;
int Y_2_A = 0;

//C
int X_1_C = hero_parameter.x_location;
int X_2_C = hero_parameter.x_location + hero_parameter.width;
int Y_1_C = hero_parameter.y_location;
int Y_2_C = hero_parameter.y_location + hero_parameter.height;

// Shot
int X_1_B = 0;
int X_2_B = 0;
int Y_1_B = 0;
int Y_2_B = 0;

bool hit = false;

    for ( int i = 0; i < enemy_hitbox_set.size() ; i++) {

        X_1_A = x_location + enemy_hitbox_set.at(i).x_u_left;
        X_2_A = x_location + enemy_hitbox_set.at(i).x_l_right ;
        Y_1_A = y_location + enemy_hitbox_set.at(i).y_u_left;
        Y_2_A = y_location + enemy_hitbox_set.at(i).y_l_right ;



        // hitbox contact
        hit = true;

        if (  X_1_C < X_2_A && X_2_C > X_1_A && Y_1_C < Y_2_A && Y_2_C > Y_1_A ) {
                hit = false;

                if ( hero_parameter.hero_invincible_counter == 0 ) {
                    cout << "hit" << endl;
                    hero_parameter.hero_life--;
                    hero_parameter.hero_invincible_counter =+ 10;
                } else {
                }

        } else {

        }



        for ( int j = 0; j < parameter.size() ; j++ ) {
            // Enemy

            X_1_A = x_location + enemy_hitbox_set.at(i).x_u_left;
            X_2_A = x_location + enemy_hitbox_set.at(i).x_l_right ;
            Y_1_A = y_location + enemy_hitbox_set.at(i).y_u_left;
            Y_2_A = y_location + enemy_hitbox_set.at(i).y_l_right ;
            // Shot


            X_1_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_u_left;
            X_2_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_l_right;
            Y_1_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_u_left;
            Y_2_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_l_right;;


            //cout << " X1_l_right shot " << X_1_B << " X2 " << X_2_A << " Y1 " << Y_1_A << " Y2 " << Y_2_A << endl;
            //cout << " X1 " << X_1_B << " X2 " << X_2_B << " Y1 " << Y_1_B << " Y2 " << Y_2_B << endl;

                hit = true;
            if (  X_1_B < X_2_A && X_2_B > X_1_A && Y_1_B < Y_2_A && Y_2_B > Y_1_A ) {
                    hit = false;


            } else {

            }

            if ( hit == false ) {
                cout << "hit" << endl;
                life = life - parameter.at(j).a_damage ;
                parameter.at(j).destroy = true;
                if ( life <= 0 ) {
                    destroy = true;

                    destroy_v_x = parameter.at(j).a_x_vel ;
                    destroy_v_y = parameter.at(j).a_y_vel ;

                } else {
                }


                animation_requests * obj = new animation_requests(12, x_location + center_x, y_location + center_y , 0, 0);
                anime_req.push_back(*obj);
                delete obj;

            } else {
            }


        };



    };

//cout << "end" << endl;
//if (RectA.X1 < RectB.X2 && RectA.X2 > RectB.X1 &&
//    RectA.Y1 > RectB.Y2 && RectA.Y2 < RectB.Y1)

};

void enemy::setRender()  {

// For mode 2
//int y_test = 0;

    switch (render_req_mode) {
    case 0:
//        if (sprite_error == false) {
//            render_requests * obj = new render_requests(sprite_nr, x_location, y_location, palette_current);
//
//            render_req.push_back(*obj);
//            delete obj;
//
//
//        } else {
////        cout << "ok" << endl;
//        };
    break;
    case 1:
        if (sprite_error == false) {
//            render_requests * obj = new render_requests(current_form_info[4], x_location, y_location, palette_current,current_sprite_direction);
//            render_requests * obj2 = new render_requests(current_form_info[5], x_location, y_location+12, palette_current, current_sprite_direction);
//            render_req.push_back(*obj);
//            render_req.push_back(*obj2);
//            delete obj;
//            delete obj2;


        } else {
//        cout << "ok" << endl;
        };
    break;
    case 2:



for ( int i = 0; i < RSV.size(); i++ ) {


    bool fc = floor_contact;
    bool gc = general_contact;
    int in = internal_state;
    int g = gun_direction;
    bool r = roof_contact;

    int x_mirror = 0;
    int RSV_x, RSV_y;



    int rot;
    bool vertical;
    bool horisontal;

    if ( (RSV.at(i).f_1 == fc || RSV.at(i).f_2 == fc) && (RSV.at(i).gu_1 == g || RSV.at(i).gu_2 == g || RSV.at(i).gu_3 == g || RSV.at(i).gu_4 == g || RSV.at(i).gu_5 == g) && ( RSV.at(i).int_1 == in || RSV.at(i).int_2 == in || RSV.at(i).int_3 == in || RSV.at(i).int_4 == in || RSV.at(i).int_5 == in || RSV.at(i).int_6 == in || RSV.at(i).int_7 == in ) ) {
    vertical = current_sprite_v_direction;
    horisontal = current_sprite_direction;
    rot = 1;
    RSV_x = x_location+RSV.at(i).x_off;
    RSV_y = y_location+RSV.at(i).y_off;






                        // gun direction
                    if ( RSV.at(i).gu_1 == 1 && RSV.at(i).gu_2 == 1 && RSV.at(i).gu_3 == 1 && RSV.at(i).gu_4 == 1 && RSV.at(i).gu_5 == 1) {

                            if ( current_sprite_direction == true ) {
                                rot = 2;
                                horisontal = false;
                                RSV_y = RSV_y - 20;
                            } else {
                            }
                            if ( current_sprite_direction == false ) {
                                rot = 2;
                                horisontal = false;
                                vertical = false;
                                RSV_y = RSV_y - 20;
                            } else {
                            }

                    } else {
                    }
                    // gun down
                    if ( RSV.at(i).gu_1 == 5 && RSV.at(i).gu_2 == 5 && RSV.at(i).gu_3 == 5 && RSV.at(i).gu_4 == 5 && RSV.at(i).gu_5 == 5) {

                            if ( current_sprite_direction == true ) {
                                rot = 2;
                                horisontal = true;
                                vertical = false;
                                RSV_y = RSV_y + 1;
                            } else {
                            }
                            if ( current_sprite_direction == false ) {
                                rot = 2;
                                horisontal = true;
                                vertical = true;
                                RSV_y = RSV_y + 1;
                            } else {
                            }

                    } else {
                    }
                    // gun 45 down
                    if ( RSV.at(i).gu_1 == 4 && RSV.at(i).gu_2 == 4 && RSV.at(i).gu_3 == 4 && RSV.at(i).gu_4 == 4 && RSV.at(i).gu_5 == 4) {

                            if ( current_sprite_direction == true ) {
                                rot = 2;
                                horisontal = true;
                                vertical = false;
                                RSV_y = RSV_y + 0;
                            } else {
                            }
                            if ( current_sprite_direction == false ) {
                                rot = 2;
                                horisontal = true;
                                vertical = true;
                                RSV_y = RSV_y + 0;
                            } else {
                            }

                    } else {
                    }
                    // based on rotation the xoffset is set
                    if ( current_sprite_direction == false &&  RSV.at(i).x_off > 0) {
                        switch (rot){
                            case 1:
                            x_mirror = 2*(RSV.at(i).x_off - width/2) + all_sprites.at(RSV.at(i).sprite_nr).getWidth()-1;
                            break;
                            case 2:
                            x_mirror = 2*(RSV.at(i).x_off - width/2) + all_sprites.at(RSV.at(i).sprite_nr).getHeight()-1;

                            break;
                            default:
                            break;
                        };

                    } else {
                    }

                    // transmitt the RSV and mirror values to the later attack creation
                    //cout << " width half " << width/2 << endl;
                    if ( RSV.at(i).is_g == true ) {
                        x_mirror_gun = x_mirror;
                        RSV_x_gun = RSV_x-x_location;
                        RSV_y_gun = RSV_y-y_location;
                        horisontal_gun = horisontal;
                        vertical_gun = vertical;
                        rot_gun = rot;
                        gun_sprite_nr = RSV.at(i).sprite_nr;
                    }else {
                    }

                    if ( RSV.at(i).use_special_offset == true ) {

                        switch (enemy_type) {

                            case (1):

                                switch ( RSV.at(i).use_special_index ) {
                                    case(1):
                                        RSV_x = previous_x.at(7) - all_sprites.at(RSV.at(i).sprite_nr).getWidth()-1 ;
                                        RSV_y = previous_y.at(7) - all_sprites.at(RSV.at(i).sprite_nr).getHeight()-1 ;
                                    break;
                                    case(2):
                                        RSV_x = previous_x.at(5) - all_sprites.at(RSV.at(i).sprite_nr).getWidth()-1 ;
                                        RSV_y = previous_y.at(5) - all_sprites.at(RSV.at(i).sprite_nr).getHeight()-1 ;
                                    break;
                                    case(3):
                                    break;
                                    default:
                                    break;

                                }



                                //cout << previous_x.at(6) << endl;
                                x_mirror = 0;
                            break;


                        };


                    } else {
                        switch (enemy_type) {
                            case (1):
                                if ( abs(y_v_float) > abs(x_v_float)  ) {
                                    vertical = true;
                                    rot = 2;
                                } else {
									
                                };


                            break;
                            case (2):
                            break;
                        };


                    };


                    RSV.at(i).RSV_x_store = RSV_x-x_mirror;
                    RSV.at(i).RSV_y_store = RSV_y;
                    render_requests * obj = new render_requests( RSV.at(i).sprite_nr, RSV_x-x_mirror, RSV_y, palette_current,horisontal, vertical, rot);
                    render_req.push_back(*obj);
                    delete obj;



        //cout << fc << endl;
    };


}
if (destroy == true) {
particle_generator( this, 0, 0, 50);
} else {
}


    break;
    default:
    break;



    };






};

// Enemy create function for game
void create_and_reset_enemies( int room_nr, vector<enemy>& parameter ) {

    parameter.clear();


    for ( int i = 1; i < room_objects.at(room_nr).columns_storage.size()/room_objects.at(room_nr).column_items ; i++ ) {

        if ( room_objects.at(room_nr).columns_storage.at(3).at(i)  > 0 ) {

            enemy * new_enemy_1 = new enemy( room_objects.at(room_nr).columns_storage.at(3).at(i), room_objects.at(room_nr).columns_storage.at(4).at(i), room_objects.at(room_nr).columns_storage.at(5).at(i));
            parameter.push_back( *new_enemy_1 );
            delete new_enemy_1;
            new_enemy_1 = 0;

        }else {
        }


    }




    switch (room_nr) {

    case (0):
    break;
    case (1):
    break;
    case (2):{

//        enemy * new_enemy_1 = new enemy(1, 1, 1);
//        parameter.push_back( *new_enemy_1 );
//        delete new_enemy_1;
//        new_enemy_1 = 0;

    break;
    }

    case (3):
    break;

    default:
    break;

    };



};
