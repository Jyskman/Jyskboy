
#include <iostream>
#include "champ.h"
#include <vector>
#include "soundmanager.h"
#include "setup_sprites.h"
#include "render.h"
#include "environment.h"
#include <cmath>

using namespace std;

//champ::champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter) {
champ::champ(int a, int size, int Height, int Width) {

// Current sprite and palette
sprite_current = 100; // sprite index, will need to connect to all_sprites
palette_current = 1;

sprite_nr = Relation_Spritenr_type(); // translates the index/current/type to vector position in all_sprites

x_velocity = 0;
y_velocity = 0;
x_max_speed = 3;
floor_contact = false;
internal_state = 0;
gun_direction = 1;
//internal = &render_req;
//setContactPoints();
};

int champ::Relation_Spritenr_type() {
    int return_value = 0;
    sprite_error = true;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == sprite_current ) {
                return_value = i;
                sprite_error = false;
                width = all_sprites.at(i).getWidth();
                height = all_sprites.at(i).getHeight();

            } else {

            };
        };

    return return_value;

};

int champ::Relation_Spritenr_type_dev(int parameter) {
    int return_value = 0;
    //sprite_error = true;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == parameter ) {
                return_value = i;
                //sprite_error = false;
                //width = all_sprites.at(i).getWidth();
                //height = all_sprites.at(i).getHeight();

            } else {

            };
        };
    sprite_error = false;
    return return_value;

};

int champ::getHeight() {
	return height;
}


int champ::getWidth() {
	return width;
}

int champ::getX() {
	return x_location;
}

int champ::getY() {
	return y_location;
}

void champ::setX(int x) {
	x_location = x;
}

void champ::setY(int y) {
	y_location = y;
}

unsigned char champ::getChar(int pos) {

	return all_sprites.at(sprite_current).getVector(pos);
}


int champ::getSpriteSize() {
	return sprite_size;
}

int champ::getPalette() {

    return palette_current;
}

void champ::setRender()  {

// For mode 2
//int y_test = 0;

    switch (render_req_mode) {
    case 0:
        if (sprite_error == false) {
            render_requests * obj = new render_requests(sprite_nr, x_location, y_location, palette_current);

            render_req.push_back(*obj);
            delete obj;


        } else {
//        cout << "ok" << endl;
        };
    break;
    case 1:
        if (sprite_error == false) {
            render_requests * obj = new render_requests(current_form_info[4], x_location, y_location, palette_current,current_sprite_direction);
            render_requests * obj2 = new render_requests(current_form_info[5], x_location, y_location+12, palette_current, current_sprite_direction);
            render_req.push_back(*obj);
            render_req.push_back(*obj2);
            delete obj;
            delete obj2;


        } else {
//        cout << "ok" << endl;
        };
    break;
    case 2:

//        if ( (int)y_velocity != 0 ) {
//        y_test = y_velocity / abs(y_velocity);
//        } else {
//        }


        for ( int i = 0; i < RSV.size(); i++ ) {

//RSV.at(i).f_1 == floor_contact || RSV.at(i).f_2 == floor_contact && RSV.at(i).w_1 == general_contact || RSV.at(i).w_2 == general_contact && RSV.at(i).int_1 == internal_state || RSV.at(i).int_2 == internal_state || RSV.at(i).int_3 == internal_state || RSV.at(i).int_4 == internal_state
//RSV.at(i).f_1 == floor_contact || RSV.at(i).f_2 == floor_contact
//RSV.at(i).w_1 == general_contact || RSV.at(i).w_2 == general_contact
//RSV.at(i).int_1 == internal_state || RSV.at(i).int_2 == internal_state || RSV.at(i).int_3 == internal_state || RSV.at(i).int_4 == internal_state
//
bool fc = floor_contact;
bool gc = general_contact;
int in = internal_state;
int g = gun_direction;
bool r = roof_contact;

            if ( RSV.at(i).r_1 == r || RSV.at(i).r_2 == r && RSV.at(i).gu_1 == g || RSV.at(i).gu_2 == g || RSV.at(i).gu_3 == g && RSV.at(i).f_1 == fc || RSV.at(i).f_2 == fc && RSV.at(i).w_1 == gc || RSV.at(i).w_2 == gc && RSV.at(i).int_1 == in || RSV.at(i).int_2 == in || RSV.at(i).int_3 == in || RSV.at(i).int_4 == in ) {
                render_requests * obj = new render_requests(RSV.at(i).sprite_nr, x_location+RSV.at(i).x_off, y_location+RSV.at(i).y_off, palette_current,current_sprite_direction);
                render_req.push_back(*obj);
                delete obj;

            } else {
            }

        }

    break;
    default:
    break;



    };






}

void champ::setContactPoints() {


// Setup of new contact points array
//contact_points_all[0][0] = all_sprites.at(sprite_nr).getWidth()/2;
//contact_points_all[1][0] = all_sprites.at(sprite_nr).getHeight();
//contact_points_all[0][1] = all_sprites.at(sprite_nr).getWidth()/2;
//contact_points_all[1][1] = 0;
//
//contact_points_all[0][2] = all_sprites.at(sprite_nr).getWidth();
//contact_points_all[1][2] = 0;
//contact_points_all[0][3] = all_sprites.at(sprite_nr).getWidth();
//contact_points_all[1][3] = all_sprites.at(sprite_nr).getHeight()*(1/4);
//contact_points_all[0][4] = all_sprites.at(sprite_nr).getWidth();
//contact_points_all[1][4] = all_sprites.at(sprite_nr).getHeight()*(2/4);
//contact_points_all[0][5] = all_sprites.at(sprite_nr).getWidth();
//contact_points_all[1][5] = all_sprites.at(sprite_nr).getHeight()*(3/4);
//contact_points_all[0][6] = all_sprites.at(sprite_nr).getWidth();
//contact_points_all[1][6] = all_sprites.at(sprite_nr).getHeight()*(4/4);
//
//contact_points_all[0][7] = 0;
//contact_points_all[1][7] = 0;
//contact_points_all[0][8] = 0;
//contact_points_all[1][8] = all_sprites.at(sprite_nr).getHeight()*(1/4);
//contact_points_all[0][9] = 0;
//contact_points_all[1][9] = all_sprites.at(sprite_nr).getHeight()*(2/4);
//contact_points_all[0][10] = 0;
//contact_points_all[1][10] = all_sprites.at(sprite_nr).getHeight()*(3/4);
//contact_points_all[0][11] = 0;
//contact_points_all[1][11] = all_sprites.at(sprite_nr).getHeight();

// Below is from other data source
contact_points_all[0][0] = width/2;
contact_points_all[1][0] = height;
contact_points_all[0][1] = width/2;
contact_points_all[1][1] = 0;

contact_points_all[0][2] = width;
contact_points_all[1][2] = 0;
contact_points_all[0][3] = width;
contact_points_all[1][3] = height*(1/4);
contact_points_all[0][4] = width;
contact_points_all[1][4] = height*(2/4);
contact_points_all[0][5] = width;
contact_points_all[1][5] = height*(3/4);
contact_points_all[0][6] = width;
contact_points_all[1][6] = height*(4/4);

contact_points_all[0][7] = 0;
contact_points_all[1][7] = 0;
contact_points_all[0][8] = 0;
contact_points_all[1][8] = height*(1/4);
contact_points_all[0][9] = 0;
contact_points_all[1][9] = height*(2/4);
contact_points_all[0][10] = 0;
contact_points_all[1][10] = height*(3/4);
contact_points_all[0][11] = 0;
contact_points_all[1][11] = height;
};

void champ::setContact(int room) {

general_contact = false;
floor_contact = false;
roof_contact = false;
contact_left = false;
contact_right = false;
contact_roof = false;



for ( int i = 0; i < room_objects.at(room).roomblocks.size() ; i++ ) {

        int P3_x = room_objects.at(room).roomblocks.at(i).contact_points[0][2] + room_objects.at(room).roomblocks.at(i).x_location;
        int P3_y = room_objects.at(room).roomblocks.at(i).contact_points[1][2] + room_objects.at(room).roomblocks.at(i).y_location;

        int P4_x = room_objects.at(room).roomblocks.at(i).contact_points[0][1] + room_objects.at(room).roomblocks.at(i).x_location;
        int P4_y = room_objects.at(room).roomblocks.at(i).contact_points[1][1] + room_objects.at(room).roomblocks.at(i).y_location;

        int P1_x = contact_points_all[0][11]  + getX(); // x
        int P1_y = contact_points_all[1][11]  + getY(); // y

        int P2_x = contact_points_all[0][2]  + getX(); // x
        int P2_y = contact_points_all[1][2]  + getY(); // y

// Below is first hitbox check within larger condition check


        if ( abs(P1_x) - abs(P1_x) < 200 && abs(P1_x) - abs(P1_x) < 200  ) {

            if ( P2_y <= P3_y && P1_y >= P4_y && P2_x >= P3_x && P1_x <= P4_x ) {

                contact_position.push_back(i);
            }


        } else {
        }

}

///////////////////////////////////////////////////////////////
            // perform a check for each point in contact list


// prototype replacement below
 for ( int i = 0; i < contact_position.size();i++ ){
        int j = contact_position.at(i);

        int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
        int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

        int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
        int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

}


            for (int k = 0; k < 13; k++){
                switch (k) {
                    case 0:
                    // Floor
                    for ( int i = 0; i < contact_position.size();i++ ){
                    int j = contact_position.at(i);

                    int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                    int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                    int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                    int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

                        if ( contact_points_all[1][0]  + getY() >= P4_y && contact_points_all[1][0]  + getY() < P3_y && contact_points_all[0][0] + getX() >= P3_x && contact_points_all[0][0] + getX() <= P4_x ) {
                        floor_contact = true;
                        y_velocity = 0;
                            while ( contact_points_all[1][0]  + getY() > P4_y ){
                            setY( getY() -1 );
                            }
                        } else {
                        }


                    }


                    break;
                    case 1:
                    // Roof
                         for ( int i = 0; i < contact_position.size();i++ ){
                                int j = contact_position.at(i);

                                int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                                int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                                int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                                int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

                                if ( contact_points_all[1][1]  + getY() >= P4_y && contact_points_all[1][1]  + getY() < P3_y && contact_points_all[0][1] + getX() >= P3_x && contact_points_all[0][1] + getX() <= P4_x ) {
                                roof_contact = true;
                                y_velocity = 0;
                                    while ( contact_points_all[1][1]  + getY() < P3_y ){
                                    setY( getY() +1 );
                                    }
                                } else {
                                }
                        }

                    break;
                    case 2:
                    // Right Side top
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][2]  + getY() >= P4_y && contact_points_all[1][2]  + getY() < P3_y && contact_points_all[0][2] + getX() >= P3_x && contact_points_all[0][2] + getX() <= P4_x ) {
                                if ( y_velocity >= 0){
                                    x_velocity = 0;
                                    contact_right = true;
                                    while ( contact_points_all[0][2]  + getX() > P3_x ){

                                    setX( getX() -1 );
                                    }
                                } else {
                                }
                                if ( y_velocity < 0 ){
                                    roof_contact = true;
                                    y_velocity = 0;
                                    while ( contact_points_all[1][2]  + getY() < P3_y ){
                                    setY( getY() +1 );
                                    }
                                } else {
                                }


                            } else {
                            }
                    }

                    break;
                    case 3:
                    // Right Side 1/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][3]  + getY() >= P4_y && contact_points_all[1][3]  + getY() < P3_y && contact_points_all[0][3] + getX() >= P3_x && contact_points_all[0][3] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_right = true;
                                while ( contact_points_all[0][3]  + getX() > P3_x ){

                                setX( getX() -1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 4:
                    // Right Side 2/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][4]  + getY() >= P4_y && contact_points_all[1][4]  + getY() < P3_y && contact_points_all[0][4] + getX() >= P3_x && contact_points_all[0][4] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_right = true;
                                while ( contact_points_all[0][4]  + getX() > P3_x ){

                                setX( getX() -1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 5:
                    // Right Side 3/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][5]  + getY() >= P4_y && contact_points_all[1][5]  + getY() < P3_y && contact_points_all[0][5] + getX() >= P3_x && contact_points_all[0][5] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_right = true;
                                while ( contact_points_all[0][5]  + getX() > P3_x ){

                                setX( getX() -1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 6:
                    // Right Side 4/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                                if ( contact_points_all[1][6]  + getY() > P4_y && contact_points_all[1][6]  + getY() <= P3_y && contact_points_all[0][6] + getX() >= P3_x && contact_points_all[0][6] + getX() <= P4_x ) {

                                if ( y_velocity >= 0 ) {
                                    floor_contact = true;
                                    y_velocity = 0;
                                    while ( contact_points_all[1][6]  + getY() > P4_y ){
                                    setY( getY() -1 );
                                    }
                                } else {
                                }
                                if ( y_velocity < 0 ) {
                                    x_velocity = 0;
                                    contact_right = true;
                                    //cout << "6" << endl;
                                    while ( contact_points_all[0][6]  + getX() > P3_x ){

                                    setX( getX() -1 );
                                    }
                                } else {
                                }

                                } else {
                                }
                    }

                    break;
                    case 7:
                    // Left Side 0/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                                if ( contact_points_all[1][7]  + getY() >= P4_y && contact_points_all[1][7]  + getY() < P3_y && contact_points_all[0][7] + getX() >= P3_x && contact_points_all[0][7] + getX() <= P4_x ) {
                                    if (y_velocity >= 0) {
                                        x_velocity = 0;
                                        contact_left = true;
                                        while ( contact_points_all[0][7]  + getX() < P4_x ){

                                        setX( getX() +1 );
                                        }
                                    } else {
                                    }
                                    if ( y_velocity < 0 ) {
                                        roof_contact = true;
                                        y_velocity = 0;
                                        while ( contact_points_all[1][7]  + getY() < P3_y ){
                                        setY( getY() +1 );
                                        }
                                    } else {
                                    }


                                } else {
                                }
                    }

                    break;
                    case 8:
                    // Left Side 1/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][8]  + getY() >= P4_y && contact_points_all[1][8]  + getY() < P3_y && contact_points_all[0][8] + getX() >= P3_x && contact_points_all[0][8] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_left = true;
                                while ( contact_points_all[0][8]  + getX() < P4_x ){

                                setX( getX() +1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 9:
                    // Left Side 2/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][9]  + getY() >= P4_y && contact_points_all[1][9]  + getY() < P3_y && contact_points_all[0][9] + getX() >= P3_x && contact_points_all[0][9] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_left = true;
                                while ( contact_points_all[0][9]  + getX() < P4_x ){

                                setX( getX() +1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 10:
                    // Left Side 3/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][10]  + getY() >= P4_y && contact_points_all[1][10]  + getY() < P3_y && contact_points_all[0][10] + getX() >= P3_x && contact_points_all[0][10] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_left = true;
                                while ( contact_points_all[0][10]  + getX() < P4_x ){

                                setX( getX() +1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 11:
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][11]  + getY() > P4_y && contact_points_all[1][11]  + getY() <= P3_y && contact_points_all[0][11] + getX() >= P3_x && contact_points_all[0][11] + getX() <= P4_x ) {
                                if ( y_velocity < 0 ) {
                                    x_velocity = 0;
                                    contact_left = true;
                                    //cout << "11" << endl;
                                    while ( contact_points_all[0][6]  + getX() < P4_x ){

                                    setX( getX() +1 );
                                    }
                                } else {
                                }
                                if ( y_velocity >= 0 ) {
                                    floor_contact = true;
                                    y_velocity = 0;
                                    while ( contact_points_all[1][6]  + getY() > P4_y ){
                                    setY( getY() -1 );
                                    }
                                } else {
                                }




                            } else {
                            }
                    }
                    // L Side 4/4

                    break;
                    case 12:
                    break;

                    default:
                    break;

                }

            }






contact_position.clear();
//End
};

void champ::setPos(button_input& parameter, physics& physics_parameter){

    if (floor_contact == true) {
        y_velocity = 0;
    };
    if (contact_right == true) {
        //x_velocity = 0;
    };
    if (contact_left == true) {
        //x_velocity = 0;
    };

    if ( parameter.getLeftState() == true ) {
        current_sprite_direction = false;
    };
    if ( parameter.getRightState() == true ) {
        current_sprite_direction = true;
    };

    //cout << x_velocity << endl;
    setX( getX() + (int)x_velocity );
    setY( getY() + (int)y_velocity );

};


void champ::updatePos(button_input& parameter, physics& physics_parameter){

//cout << physics_parameter.state << endl;

    switch (physics_parameter.state) {
        case 0:
            if ( parameter.getLeftState() == true && contact_left == false) {
                    //setX( getX() - 3 );
                    x_velocity--;
                    x_velocity--;
            } else {
            }

            if ( parameter.getRightState() == true && contact_right == false ) {
                    //setX( getX() + 3 );
                    x_velocity++;
                    x_velocity++;
            } else {
            }
                // y axis
            if (floor_contact == false) {
                    y_velocity = y_velocity +1 ;
            }
            if (parameter.getJumpState() == true && floor_contact == true) {
                y_velocity = y_velocity -10;
                floor_contact = false;

            }



        break;

        default:
//            if ( parameter.getLeftState() == true ) {
//                    setX( getX() - 3 );
//            } else {
//            }
//
//            if ( parameter.getRightState() == true ) {
//                    setX( getX() + 3 );
//            } else {
//            }
//
//            if ( parameter.getUpState() == true ) {
//                    setY( getY() - 3 );
//            } else {
//            }
//
//            if ( parameter.getDownState() == true ) {
//                    setY( getY() + 3 );
//            } else {
//            }
        break;

    };

    if (x_velocity > x_max_speed) {
        x_velocity = x_max_speed;
    } else {
    }
    if (x_velocity < -x_max_speed) {
        x_velocity = -x_max_speed;
    } else {
    }

    x_velocity = x_velocity * physics_parameter.air;



    if( y_velocity > physics_parameter.g ) {
            y_velocity = physics_parameter.g;
    } else {
    }


};

void champ_setup(champ &parameter) {
    // render_requests * obj = new render_requests(sprite_nr, x_location, y_location, current_palette);
    // upper body
    render_state * state_1_1 = new render_state(true, false, true, false, true, false, 1, 1, 1, 1, 2, 3, 4, 0, 0, 101 );
    parameter.RSV.push_back(*state_1_1);
    delete state_1_1;



    // lower body


    //cout << parameter.render_state_vector.at(0).sprite_nr << endl;

};
