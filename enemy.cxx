
// Enemy base class

#include "enemy.h"
#include "setup_sprites.h"
#include <iostream>












void enemy::RSV_setup() {


    if ( enemy_type == 1 ) {

        enemy_offset[0][0] = 0 ; // first object x offset
        enemy_offset[1][0] = 0 ; // first object y offset

        render_state * state_1_1 = new render_state(true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, enemy_offset[0][0], enemy_offset[1][0], 207 );
        RSV.push_back(*state_1_1);
        delete state_1_1;
    }


}

enemy::enemy( int e_type) {

x_location = 30 ;
y_location = 30 ;
enemy_type = e_type;
RSV_setup();

};

void enemy::test() {
cout << "Func ok" << endl;
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
                    cout << " width half " << width/2 << endl;
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

                    render_requests * obj = new render_requests(RSV.at(i).sprite_nr, RSV_x-x_mirror, RSV_y, palette_current,horisontal, vertical, rot);
                    render_req.push_back(*obj);
                    delete obj;

        //cout << fc << endl;
    };


}
    break;
    default:
    break;



    };






};


