
#include <iostream>
#include "champ.h"
#include <vector>
#include "soundmanager.h"
#include "setup_sprites.h"
#include "render.h"
#include "environment.h"
#include <cmath>
#include <assert.h>
#include <math.h>
using namespace std;

//champ::champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter) {
champ::champ(int a, int size, int Height, int Width) : runcycle(2,6,1,60) {

// Current sprite and palette
//sprite_current = 100; // sprite index, will need to connect to all_sprites
palette_current = 1;

//sprite_nr = Relation_Spritenr_type(); // translates the index/current/type to vector position in all_sprites

x_velocity = 0;
y_velocity = 0;
x_max_speed = 3;
floor_contact = false;
internal_state = 7;
gun_direction = 3;
jump_counter = 1;
//internal = &render_req;
//setContactPoints();
};

// May be obsolete after render state
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

//int champ::blockCompare_y(int champ_x, int champ_y, int block_x, int block_y, int block_p3x, int block_p3y, int block_p4x, int block_p4y ) {
//
//int return_value;
//
//return_value = ( ( block_p4y - block_p3y ) / ( block_p4x - block_p3x ) ) * ( champ_x - block_x ) + block_p3y ;
//
//return return_value;
//
//}
double champ::Det(double a, double b, double c, double d)
{
	return a*d - b*c;
};

bool champ::LineLineIntersect(double x1, double y1, //Line 1 start
    double x2, double y2, //Line 1 end
    double x3, double y3, //Line 2 start
    double x4, double y4, //Line 2 end
    double &ixOut, double &iyOut) {

        //http://mathworld.wolfram.com/Line-LineIntersection.html

    double detL1 = Det(x1, y1, x2, y2);
    double detL2 = Det(x3, y3, x4, y4);
    double x1mx2 = x1 - x2;
    double x3mx4 = x3 - x4;
    double y1my2 = y1 - y2;
    double y3my4 = y3 - y4;

    double xnom = Det(detL1, x1mx2, detL2, x3mx4);
    double ynom = Det(detL1, y1my2, detL2, y3my4);
    double denom = Det(x1mx2, y1my2, x3mx4, y3my4);
    if(denom == 0.0)//Lines don't seem to cross
    {
        ixOut = NAN;
        iyOut = NAN;
        return false;
    }

    ixOut = xnom / denom;
    iyOut = ynom / denom;
    if(!isfinite(ixOut) || !isfinite(iyOut)) //Probably a numerical issue
        return false;

    return true; //All OK

};


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

void champ::setContactPoints() {
float floater;

// Setup of new contact points array


// Below is from other data source
floater = (float)width * 1/2;
contact_points_all[0][0] = (int)floater;
contact_points_all[1][0] = height;

floater = (float)width * 1/2;
contact_points_all[0][1] = (int)floater;
contact_points_all[1][1] = 0;

contact_points_all[0][2] = width;
contact_points_all[1][2] = 0;

floater = (float)height * 1/4;
contact_points_all[0][3] = width;
contact_points_all[1][3] = (int)floater;

floater = (float)height * 2/4;
contact_points_all[0][4] = width;
contact_points_all[1][4] = (int)floater;

floater = (float)height * 3/4;
contact_points_all[0][5] = width;
contact_points_all[1][5] = (int)floater;

floater = (float)height * 4/4;
contact_points_all[0][6] = width;
contact_points_all[1][6] = (int)floater;

contact_points_all[0][7] = 0;
contact_points_all[1][7] = 0;

floater = (float)height * 1/4;
contact_points_all[0][8] = 0;
contact_points_all[1][8] = (int)floater;

floater = (float)height * 2/4;
contact_points_all[0][9] = 0;
contact_points_all[1][9] = (int)floater;

floater = (float)height * 3/4;
contact_points_all[0][10] = 0;
contact_points_all[1][10] = (int)floater;

contact_points_all[0][11] = 0;
contact_points_all[1][11] = height;

//cout << contact_points_all[1][3] << endl;
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
                        //cout << " floor " << endl;
                        floor_contact = true;
                        jump_counter = 1;
                        y_velocity = 0;
                            while ( contact_points_all[1][0]  + getY() >= P4_y ){
                            setY( getY() -1 );
                            }
                            //cout << y_location+height << "  " << P4_y << endl;
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
                                cout << "top" << endl;
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

                                if ( contact_points_all[1][2]  + getY() >= P4_y && contact_points_all[1][2]  + getY() <= P3_y && contact_points_all[0][2] + getX() >= P3_x && contact_points_all[0][2] + getX() <= P4_x ) {

                                // champ pos
                                x_1 = x_location + width ;
                                y_1 = y_location ;
                                x_2 = x_location_prev + width ;
                                y_2 = y_location_prev ;

//                                float x_1 = 5 ;
//                                float y_1 = 5 ;
//                                float x_2 = 10 ;
//                                float y_2 = 10 ;
                                length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
                                //cout << "L_" << length << endl;

                                x_location_intersection = x_1;
                                y_location_intersection = y_1;

                                x_location_intersection_int = (int)x_1 ;
                                y_location_intersection_int = (int)y_1 ;

                                delta_x;
                                delta_y;
                                increment = 0;
                                delta_increment = 0.1;


                                cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                a_cos = acos( cos_alfa );

                                // correction of angle due to horizontal line
                                if (y_2 < y_1) {
                                    a_cos = a_cos + M_PI;
                                } else {
                                }

                                //float sin_length = length * sin( a_cos ) ;
                                //float cos_length = length * cos( a_cos ) ;
                                //cout << " sin of length " << sin_length << endl;
                                //cout << " cos of length " << cos_length << endl;


                                //cout << "alfa_" << a_cos*(180/M_PI) << endl;

                                    while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                            increment = increment + delta_increment;

                                                delta_x = ( length - increment ) * cos( a_cos );
                                                delta_y = ( length - increment ) * sin( a_cos );
                                                //cout << delta_x <<endl;

                                                    if (delta_x < 0) {
                                                    //delta_x = 0;
                                                    } else {
                                                    }
                                                    if (delta_y < 0) {
                                                    delta_y = 0;
                                                    } else {
                                                    }

                                                //cout << length << endl;
                                                x_location_intersection = x_location_intersection - (( x_1 - x_2 ) + delta_x) ;
                                                y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);
                                                //cout << ( x_1 - x_2 ) << " - " << delta_x <<endl;

                                                x_location_intersection_int = (int)x_location_intersection;
                                                y_location_intersection_int = (int)y_location_intersection;

                                                //cout << "x_1 " << x_1 << " length-increment" << x_location_intersection << " x_int_" <<x_location_intersection_int << "P3_x" << P3_x << endl;

                                    }

                                    /////////////////
                                if (x_location_intersection_int <= P3_x) {
                                    x_location_intersection_int = P3_x-1;
                                    contact_right = true;
                                } else {
                                }
                                if( y_location_intersection_int >= P3_y ){
                                    y_location_intersection_int = P3_y+1;
                                    roof_contact = true;
                                } else {
                                }

                                x_location = x_location_intersection_int - width;
                                y_location = y_location_intersection_int;
                                //cout << x_1 << " " << y_1 << " Prev " << x_2 << " " << y_2 << " " << x_location+width << " " << y_location << " " << P3_x << " " << P3_y <<endl;


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
                            //x_velocity = 0;
                            contact_right = true;
                            cout << "Z" << endl;
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
                     //Right Side 3/4
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
                                if ( contact_points_all[1][6]  + getY() >= P4_y && contact_points_all[1][6]  + getY() <= P3_y && contact_points_all[0][6] + getX() >= P3_x && contact_points_all[0][6] + getX() <= P4_x ) {
                                    // champ pos
                                    x_1 = x_location + width ;
                                    y_1 = y_location + height;
                                    x_2 = x_location_prev + width ;
                                    y_2 = y_location_prev + height;

                                    length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
                                    //cout << "L_" << length << endl;

                                    x_location_intersection = x_1;
                                    y_location_intersection = y_1;

                                    x_location_intersection_int = (int)x_1 ;
                                    y_location_intersection_int = (int)y_1 ;

                                    delta_x;
                                    delta_y;
                                    increment = 0;
                                    delta_increment = 0.1;


                                    cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                    a_cos = acos( cos_alfa );

                                    // correction of angle due to horizontal line
                                        if (y_2 < y_1) {
                                            a_cos = a_cos + M_PI;
                                        } else {
                                        }

                                    //float sin_length = length * sin( a_cos ) ;
                                    //float cos_length = length * cos( a_cos ) ;
                                    //cout << " sin of length " << sin_length << endl;
                                    //cout << " cos of length " << cos_length << endl;


                                    //cout << "alfa_" << a_cos*(180/M_PI) << endl;

                                        while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                                    increment = increment + delta_increment;

                                                    delta_x = ( length - increment ) * cos( a_cos );
                                                    delta_y = ( length - increment ) * sin( a_cos );
                                                    //cout << delta_x << " _ " << delta_y <<endl;

                                                        if (delta_x < 0) {
                                                        //delta_x = 0;
                                                        } else {
                                                        }
                                                        if (delta_y < 0) {
                                                        delta_y = 0;
                                                        } else {
                                                        }

                                                    //cout << length << " _ " << delta_x << endl;

                                                    x_location_intersection = x_location_intersection - (( x_1 - x_2 ) - delta_x) ;
                                                    y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);
                                                    //cout << ( x_1 - x_2 ) << " - " << delta_x <<endl;

                                                    x_location_intersection_int = (int)x_location_intersection;
                                                    y_location_intersection_int = (int)y_location_intersection;

                                                    //cout << "x_1 " << x_1 << " length-increment" << x_location_intersection << " x_int_" <<x_location_intersection_int << "P3_x" << P3_x << endl;

                                        }

                                        /////////////////

                                        if (x_location_intersection_int <= P3_x && y_location_intersection_int > P4_y) {
                                            x_location_intersection_int = P3_x-1;
                                            contact_right = true;
                                        } else {
                                        }
                                        if( y_location_intersection_int <= P4_y ){
                                            y_location_intersection_int = P4_y-1;

                                            //roof_contact = true;
                                            floor_contact = true;
                                            y_velocity = 0;
                                            jump_counter = 1;
                                        } else {
                                        }

                                    cout << " LR1 " <<  x_location_intersection_int << endl;
                                    if (floor_contact == true) {
                                        x_location_intersection_int = x_location + width;
                                    } else {
                                    }
                                    cout << " LR2 " <<  x_location_intersection_int << endl;
                                    x_location = x_location_intersection_int - width;
                                    y_location = y_location_intersection_int - height;
                                    //cout << x_1 << " " << y_1 << " Prev " << x_2 << " " << y_2 << " " << x_location+width << " " << y_location+height << " " << P3_x << " " << P4_y <<endl;




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
                                    // champ pos
                                    x_1 = x_location ;
                                    y_1 = y_location ;
                                    x_2 = x_location_prev ;
                                    y_2 = y_location_prev ;

                                    length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
                                    //cout << "L_" << length << endl;

                                    x_location_intersection = x_1;
                                    y_location_intersection = y_1;

                                    x_location_intersection_int = (int)x_1 ;
                                    y_location_intersection_int = (int)y_1 ;

                                    delta_x;
                                    delta_y;
                                    increment = 0;
                                    delta_increment = 0.1;


                                    cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                    a_cos = acos( cos_alfa );

                                    // correction of angle due to horizontal line
                                        if (y_2 < y_1) {
                                            a_cos = a_cos + M_PI;
                                        } else {
                                        }

                                    //float sin_length = length * sin( a_cos ) ;
                                    //float cos_length = length * cos( a_cos ) ;
                                    //cout << " sin of length " << sin_length << endl;
                                    //cout << " cos of length " << cos_length << endl;


                                    //cout << "alfa_" << a_cos*(180/M_PI) << endl;

                                        while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                                    increment = increment + delta_increment;

                                                    delta_x = ( length - increment ) * cos( a_cos );
                                                    delta_y = ( length - increment ) * sin( a_cos );
                                                    //cout << delta_x <<endl;

                                                        if (delta_x < 0) {
                                                        //delta_x = 0;
                                                        } else {
                                                        }
                                                        if (delta_y < 0) {
                                                        delta_y = 0;
                                                        } else {
                                                        }

                                                    //cout << length << endl;
                                                    x_location_intersection = x_location_intersection - (( x_1 - x_2 ) + delta_x) ;
                                                    y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);
                                                    //cout << ( x_1 - x_2 ) << " - " << delta_x <<endl;


                                                    x_location_intersection_int = (int)x_location_intersection;
                                                    y_location_intersection_int = (int)y_location_intersection;

                                                    //cout << "x_1 " << x_1 << " length-increment" << x_location_intersection << " x_int_" <<x_location_intersection_int << "P3_x" << P3_x << endl;

                                        }

                                        /////////////////
                                        if (x_location_intersection_int >= P4_x) {
                                            x_location_intersection_int = P4_x+1;
                                            contact_right = true;
                                        } else {
                                        }
                                        if( y_location_intersection_int >= P3_y ){
                                            y_location_intersection_int = P3_y+1;
                                            roof_contact = true;
                                        } else {
                                        }

                                    x_location = x_location_intersection_int;
                                    y_location = y_location_intersection_int;
                                    cout << "U_L" <<endl;
                                    //cout << x_1 << " " << y_1 << " Prev " << x_2 << " " << y_2 << " " << x_location+width << " " << y_location << " " << P3_x << " " << P3_y <<endl;



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
                    // Left Side 4/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][11]  + getY() >= P4_y && contact_points_all[1][11]  + getY() <= P3_y && contact_points_all[0][11] + getX() >= P3_x && contact_points_all[0][11] + getX() <= P4_x ) {

                                    // champ pos
                                    x_1 = x_location ;
                                    y_1 = y_location + height;
                                    x_2 = x_location_prev ;
                                    y_2 = y_location_prev + height;

                                    length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
                                    //cout << "L_" << length << endl;

                                    x_location_intersection = x_1;
                                    y_location_intersection = y_1;

                                    x_location_intersection_int = (int)x_1 ;
                                    y_location_intersection_int = (int)y_1 ;

                                    delta_x;
                                    delta_y;
                                    increment = 0;
                                    delta_increment = 0.1;


                                    cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                    a_cos = acos( cos_alfa );

                                    // correction of angle due to horizontal line
                                        if (y_2 < y_1) {
                                            a_cos = a_cos + M_PI;
                                        } else {
                                        }

                                    //float sin_length = length * sin( a_cos ) ;
                                    //float cos_length = length * cos( a_cos ) ;
                                    //cout << " sin of length " << sin_length << endl;
                                    //cout << " cos of length " << cos_length << endl;


                                    //cout << "alfa_" << a_cos*(180/M_PI) << endl;

                                        while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                                    increment = increment + delta_increment;

                                                    delta_x = ( length - increment ) * cos( a_cos );
                                                    delta_y = ( length - increment ) * sin( a_cos );
                                                    //cout << delta_x << " _ " << delta_y <<endl;

                                                        if (delta_x < 0) {
                                                        //delta_x = 0;
                                                        } else {
                                                        }
                                                        if (delta_y < 0) {
                                                        delta_y = 0;
                                                        } else {
                                                        }

                                                    //cout << length << " _ " << delta_x << endl;
                                                    x_location_intersection = x_location_intersection - (( x_1 - x_2 ) - delta_x) ;
                                                    y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);
                                                    //cout << ( x_1 - x_2 ) << " LL " << delta_x <<endl;

                                                    x_location_intersection_int = (int)x_location_intersection;
                                                    y_location_intersection_int = (int)y_location_intersection;

                                                    //cout << "x_1 " << x_1 << " length-increment" << x_location_intersection << " x_int_" <<x_location_intersection_int << "P3_x" << P3_x << endl;

                                        }

                                        /////////////////
                                        if (x_location_intersection_int >= P4_x && y_location_intersection_int > P4_y) {
                                            x_location_intersection_int = P4_x+1;
                                            contact_left = true;
                                        } else {
                                        }
                                        if( y_location_intersection_int <= P4_y ){
                                            y_location_intersection_int = P4_y-1;
                                            //roof_contact = true;
                                            floor_contact = true;
                                            y_velocity = 0;
                                            jump_counter = 1;
                                        } else {
                                        }
                                        //cout << x_location_intersection_int << " LL- " << y_location_intersection_int <<endl;


                                    cout << " LL1 " << x_location_intersection_int <<endl;
                                    if (floor_contact == true) {
                                        x_location_intersection_int = x_location;
                                    } else {
                                    }
                                    cout << " LL2 " << x_location_intersection_int <<endl;
                                    x_location = x_location_intersection_int ;
                                    y_location = y_location_intersection_int - height;
                                    //cout << x_1 << " " << y_1 << " Prev " << x_2 << " " << y_2 << " " << x_location+width << " " << y_location+height << " " << P3_x << " " << P4_y <<endl;








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
        //y_velocity = 0;
    };
    if (roof_contact == true) {
        y_velocity = 0;
    };
    if (contact_right == true) {
        x_velocity = 0;
    };
    if (contact_left == true) {
        x_velocity = 0;
    };

    if ( parameter.getLeftState() == true ) {
        current_sprite_direction = false;
    };
    if ( parameter.getRightState() == true ) {
        current_sprite_direction = true;
    };


    // set gun direction prototype
    gun_direction = 3;
    if ( parameter.getUpState() == true ) {
        gun_direction = 1;
    } else {
    }
    if ( parameter.getDownState() == true ) {
        gun_direction = 5;
    } else {
    }
    if ( (parameter.getUpState() == true && parameter.getRightState() == true) || (parameter.getUpState() == true && parameter.getLeftState()== true) ) {
        gun_direction = 2;
    } else {
    }
    if ( (parameter.getDownState() == true && parameter.getRightState() == true) || (parameter.getDownState() == true && parameter.getLeftState()== true) ) {
        gun_direction = 4;
    } else {
    }

    x_location_prev = x_location;
    y_location_prev = y_location;

    //cout << x_velocity << endl;
    setX( getX() + (int)x_velocity );
    setY( getY() + (int)y_velocity );

};


void champ::updateV(button_input& parameter, physics& physics_parameter){

//cout << internal_state << endl;

    switch (physics_parameter.state) {
        case 0:
            if ( parameter.getLeftState() == true) {
                    //setX( getX() - 3 );
                    x_velocity--;
                    x_velocity--;
                    internal_state = runcycle.run();
            } else {
                    internal_state = runcycle.idle( internal_state );
            }

            if ( parameter.getRightState() == true) {
                    //setX( getX() + 3 );
                    x_velocity++;
                    x_velocity++;
                    internal_state = runcycle.run();
            } else {
                   internal_state = runcycle.idle( internal_state );
            }
            // y axis

            y_velocity = y_velocity +1;

            //cout << x_location+width << endl;
            if (parameter.getJumpState() == true && jump_counter > 0) { ///
                jump_counter--;

                y_velocity = y_velocity -10;
                floor_contact = false;
                //cout << "XX" << endl;

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
    render_state * state_1_1 = new render_state(true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 101 );
    parameter.RSV.push_back(*state_1_1);
    delete state_1_1;

    // lower body, and run cycle
    render_state * state_1_2 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 7, 7, 7, 7, 7, 7, 7, 0, 12, 102 );
    parameter.RSV.push_back(*state_1_2);
    delete state_1_2;
    // 1
    render_state * state_1_2_1 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 0, 12, 111 );
    parameter.RSV.push_back(*state_1_2_1);
    delete state_1_2_1;
    // 2
    render_state * state_1_2_2 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 2, 2, 2, 2, 2, 2, 2, 0, 12, 112 );
    parameter.RSV.push_back(*state_1_2_2);
    delete state_1_2_2;
    // 3
    render_state * state_1_2_3 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 3, 3, 3, 3, 3, 3, 3, 0, 12, 113 );
    parameter.RSV.push_back(*state_1_2_3);
    delete state_1_2_3;
    // 4
    render_state * state_1_2_4 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 4, 4, 4, 4, 4, 4, 4, 0, 12, 114 );
    parameter.RSV.push_back(*state_1_2_4);
    delete state_1_2_4;
    // 5
    render_state * state_1_2_5 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 0, 12, 115 );
    parameter.RSV.push_back(*state_1_2_5);
    delete state_1_2_5;
    // 6
    render_state * state_1_2_6 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 0, 12, 116 );
    parameter.RSV.push_back(*state_1_2_6);
    delete state_1_2_6;


    ////////////////////////////////////
    // Jump
    render_state * state_1_3 = new render_state(false, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 12, 103 );
    parameter.RSV.push_back(*state_1_3);
    delete state_1_3;

    //gun
    render_state * state_1_4 = new render_state(false, true, true, false, true, false, 3, 3, 3, 3, 3, 1, 2, 3, 4, 5, 6, 7, 14, 10, 104 );
    parameter.RSV.push_back(*state_1_4);
    delete state_1_4;
    render_state * state_1_5 = new render_state(false, true, true, false, true, false, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 11, 10, 104 );
    parameter.RSV.push_back(*state_1_5);
    delete state_1_5;
    render_state * state_1_6 = new render_state(false, true, true, false, true, false, 5, 5, 5, 5, 5, 1, 2, 3, 4, 5, 6, 7, 11, 10, 104 );
    parameter.RSV.push_back(*state_1_6);
    delete state_1_6;
    render_state * state_1_7 = new render_state(false, true, true, false, true, false, 2, 2, 2, 2, 2, 1, 2, 3, 4, 5, 6, 7, 11, -3, 106 );
    parameter.RSV.push_back(*state_1_7);
    delete state_1_7;
    render_state * state_1_8 = new render_state(false, true, true, false, true, false, 4, 4, 4, 4, 4, 1, 2, 3, 4, 5, 6, 7, 11, 10, 106 );
    parameter.RSV.push_back(*state_1_8);
    delete state_1_8;
//    render_state * state_1_5 = new render_state(false, true, true, false, true, false, 2, 2, 2, 1, 2, 3, 4, 12, -12, 105 );
//    parameter.RSV.push_back(*state_1_5);
//    delete state_1_5;
    //cout << parameter.render_state_vector.at(0).sprite_nr << endl;

};

//
//// SLASK
//                                if ( LineLineIntersect(x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, x_location_intersection, y_location_intersection) ) {
//                                    x_location_intersection_int = (int)x_location_intersection ;
//                                    y_location_intersection_int = (int)y_location_intersection ;
//                                    //cout << "RT_1 " << x_location_intersection_int << "_" << P3_x << "_" << P4_x <<endl;
//
//                                        if ( y_location_intersection_int == P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ){
//                                            //cout << "intersect" << endl;
//                                            cout << "RT_2 " << x_location_intersection_int << "_" << y_location_intersection_int << P3_y <<endl;
//                                            y_velocity = 0;
//                                            roof_contact = true;
//                                            x_location = x_location_intersection_int - width ;
//                                            y_location = y_location_intersection_int + 1;
//                                        } else {
//                                        }
//                                } else {
//                                }
//                            // left of the block check
//                            x_3 = P3_x ;
//                            y_3 = P3_y ;
//                            x_4 = P3_x ;
//                            y_4 = P4_y ;
//
//                                if ( LineLineIntersect(x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, x_location_intersection, y_location_intersection) ) {
//                                    x_location_intersection_int = (int)x_location_intersection ;
//                                    y_location_intersection_int = (int)y_location_intersection ;
//                                    //cout << x_location_intersection << "_" << y_location_intersection << endl;
//                                        if ( x_location_intersection_int == P3_x && y_location_intersection_int <= P3_y && y_location_intersection_int >= P4_y && latch){
//                                            cout << "RT_3 " << x_location_intersection_int << "_" << y_location_intersection_int << P3_x <<endl;
//                                            //x_velocity = 0;
//                                            x_location = x_location_intersection_int - width ;
//                                            y_location = y_location_intersection_int;
//                                        } else {
//                                        }
//                                } else {
//                                }
//


























