
#include <iostream>
#include "champ.h"
#include <vector>
#include "soundmanager.h"
#include "setup_sprites.h"
#include "render.h"
#include "environment.h"
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

        if (sprite_error == false) {
            render_requests * obj = new render_requests(sprite_nr, x_location, y_location, palette_current);

            render_req.push_back(*obj);
            delete obj;


        } else {
//        cout << "ok" << endl;
        };




}

void champ::setContactPoints() {


contact_points[0][0] = 0; // x
contact_points[1][0] = 0; // y

contact_points[0][1] = all_sprites.at( sprite_nr ).getWidth();
contact_points[1][1] = 0;

contact_points[0][2] = 0;
contact_points[1][2] = all_sprites.at(sprite_nr).getHeight();

contact_points[0][3] = all_sprites.at(sprite_nr).getWidth();
contact_points[1][3] = all_sprites.at(sprite_nr).getHeight();

// half points
contact_points[0][4] = all_sprites.at(sprite_nr).getWidth()/2;
contact_points[1][4] = 0;
contact_points[0][5] = all_sprites.at(sprite_nr).getWidth()/2;
contact_points[1][5] = all_sprites.at(sprite_nr).getHeight();

contact_points[0][6] = 0;
contact_points[1][6] = all_sprites.at(sprite_nr).getHeight()/2;

contact_points[0][7] = all_sprites.at(sprite_nr).getWidth();
contact_points[1][7] = all_sprites.at(sprite_nr).getHeight()/2;

//    for (int i = 0; i < 8; i++){
//
//    cout << contact_points[0][i];
//    cout << contact_points[1][i]  << endl;
//    };
};

void champ::setContact(int room) {


// is there floor contact
//contact_points[0][0]
//contact_points[0][1]
//
//contact_points[0][3]
//contact_points[1][3]
//
//room_objects.at(room).roomblocks.at(i).contact_points[0][0]
//room_objects.at(room).roomblocks.at(i).contact_points[1][0]
//
//room_objects.at(room).roomblocks.at(i).contact_points[0][3]
//room_objects.at(room).roomblocks.at(i).contact_points[1][3]
general_contact = false;
floor_contact = false;
contact_left = false;
contact_right = false;
contact_roof = false;


int P1_x = contact_points[0][2]  + getX(); // x
int P1_y = contact_points[1][2]  + getY(); // y

int P2_x = contact_points[0][1]  + getX(); // x
int P2_y = contact_points[1][1]  + getY(); // y


for ( int i = 0; i < room_objects.at(room).roomblocks.size() ; i++ ) {

        int P3_x = room_objects.at(room).roomblocks.at(i).contact_points[0][2] + room_objects.at(room).roomblocks.at(i).x_location;
        int P3_y = room_objects.at(room).roomblocks.at(i).contact_points[1][2] + room_objects.at(room).roomblocks.at(i).y_location;

        int P4_x = room_objects.at(room).roomblocks.at(i).contact_points[0][1] + room_objects.at(room).roomblocks.at(i).x_location;
        int P4_y = room_objects.at(room).roomblocks.at(i).contact_points[1][1] + room_objects.at(room).roomblocks.at(i).y_location;

        if ( P2_y <= P3_y && P1_y >= P4_y && P2_x >= P3_x && P1_x <= P4_x ) {
            general_contact = true;


            if ( general_contact == true ) {
                if ( contact_points[1][2]  + getY() > room_objects.at(room).roomblocks.at(i).contact_points[1][1] || contact_points[1][2]  + getY() > room_objects.at(room).roomblocks.at(i).contact_points[1][0] ) {
                    floor_contact = true;

                        while ( getY()+30  > P4_y){
                        setY( getY() -1 );

                        }

                    //cout << P1_y << endl;
                    //cout << P4_y << endl;
                    cout << height << endl;
                }else {
                }


            } else {
            }



        } else {
        }



}
//








//cout << getY() << endl;
//( P2.y <= P3.y && P1.y >= P4.y && P2.x >= P3.x && P1.x <= P4.x )

};

void champ::setPos(button_input& parameter, physics& physics_parameter){

    if (floor_contact == true) {
        y_velocity = 0;


    };
    setX( getX() + (int)x_velocity );
    setY( getY() + (int)y_velocity );

};


void champ::updatePos(button_input& parameter, physics& physics_parameter){

//cout << physics_parameter.state << endl;

    switch (physics_parameter.state) {
        case 0:
            if ( parameter.getLeftState() == true ) {
                    //setX( getX() - 3 );
                    x_velocity--;
                    x_velocity--;
            } else {
            }

            if ( parameter.getRightState() == true ) {
                    //setX( getX() + 3 );
                    x_velocity++;
                    x_velocity++;
            } else {
            }
                // y axis
            y_velocity++;


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
