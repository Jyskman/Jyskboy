
#include <iostream>
#include <vector>
#include "environment.h"
#include "render.h"
#include "setup_sprites.h"
#include <math.h>

#include <fstream>
#include <sstream>
#include <string>

using namespace std;
//
//int room1_cols = 128;
//int room1_rows = 16;
//int room1_xlimit_upper = 128 * 15;
//int room1_xlimit_lower = 0;
//int room1_ylimit_lower = 0;
//int room1_ylimit_upper = 16 * 15;
//int room1_nr = 1;
//
//int room2_cols = 26;
//int room2_rows = 16;
//int room2_xlimit_upper = 26 * 15;
//int room2_xlimit_lower = 0;
//int room2_ylimit_lower = 0;
//int room2_ylimit_upper = 16 * 15;
////int nr = 2;
//
//int room3_cols = 26;
//int room3_rows = 16*2;
//int room3_xlimit_upper = 26 * 15;
//int room3_xlimit_lower = 0;
//int room3_ylimit_lower = 0;
//int room3_ylimit_upper = 2*16 * 15;

vector<block> blocks;
vector<room_object> room_objects;
//vector<portal> portal_objects;
vector<room_portal> room_portals;

block::block(int x_pos, int y_pos, int palette, int type) {

x_location = x_pos;
y_location = y_pos;
current_palette = palette;
block_type = type; // also called index type/index
sprite_nr = Relation_Spritenr_type();
friction_coeff = setFriction(type);
};

block::block(int x_pos, int y_pos, int type) {

x_location = x_pos;
y_location = y_pos;
current_palette = 1;
block_type = type; // also called index type/index
sprite_nr = Relation_Spritenr_type();
friction_coeff = setFriction(type);
};


block::~block(){};

void block::setContactpoints() {
contact_points[0][0] = 0; // x
contact_points[1][0] = 0; // y

contact_points[0][1] = all_sprites.at( sprite_nr ).getWidth();
contact_points[1][1] = 0;

contact_points[0][2] = 0;
contact_points[1][2] = all_sprites.at(sprite_nr).getHeight();

contact_points[0][3] = all_sprites.at(sprite_nr).getWidth();
contact_points[1][3] = all_sprites.at(sprite_nr).getHeight();

};


float block::setFriction(int type) {
float return_value = 0;
switch (type) {
    case 1:
        return_value = 0.8;
    break;

}


return return_value;
};

void block::setRender(){

    if ( sprite_error == false) {
            render_requests * obj = new render_requests(sprite_nr, x_location, y_location, current_palette);

            render_req.push_back(*obj);
            delete obj;
    } else {
    };


};

// draw error will be true if no relation between index/type and vector index can be established in the forloop all_sprites
int block::Relation_Spritenr_type() {
    int return_value = 0;
    sprite_error = true;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == block_type ) {
                return_value = i;
                sprite_error = false;
                //cout << return_value << endl;
            } else {

            };
        };

    return return_value;

};




// Room_object class below

room_object::room_object(int *arr,int *arr_pal , int row, int col, int x_up, int x_low, int y_up, int y_low, int nr) : roomblocks() {

adress = arr;
adress_pal = arr_pal;
rows = row;
cols = col;
xlim_low = x_low;
xlim_up =x_up;
ylim_low = y_low;
ylim_up = y_up;
room_nr = nr;


room_object_setup();
};

room_object::room_object(int *arr, int row, int col, int x_up, int x_low, int y_up, int y_low, int nr) : roomblocks() {

adress = arr;

rows = row;
cols = col;
xlim_low = x_low;
xlim_up =x_up;
ylim_low = y_low;
ylim_up = y_up;
room_nr = nr;



//    if ( nr == 2 ) {
//     room_object_setupCSV();
//     create_blocks();
//    } else {
//
//
//    }
    room_object_setup();


};


void room_object::set_limits() {

// For a static room you add 320 resp 240 to the low value of x and y eg xlim 0 -> xlim uo 320

xlim_low = columns_storage.at(0).at(0);
xlim_up = columns_storage.at(2).at(0);
ylim_low = columns_storage.at(1).at(0);
ylim_up = columns_storage.at(3).at(0);


};

room_object::room_object( string file, int x_up, int x_low, int y_up, int y_low, int nr) : roomblocks(), columns_storage() {

name = file;

xlim_low = x_low;
xlim_up =x_up;
ylim_low = y_low;
ylim_up = y_up;
room_nr = nr;

room_object_setupCSV();
create_blocks();
set_limits();
cout << " end const " << endl;
};


room_object::~room_object() {

};

void room_object::room_object_setupCSV() {
// How many col of data to create

column_items = 3;


    string file_name = name;
    string line;
    ifstream room_2;
    room_2.open(file_name);

    // counter for once only col items +1 loop, could be bool
    int counter = 0;
    while ( room_2.good() ) {

        // First time only read 4 values and ignore the -1 index in the CSV
        if ( counter == 0 ) {
        getline(room_2, line, ',');
        column_items = -1 * stoi (line.c_str()) ;
        //cout << column_items << endl;

        } else {
        }
        // end first time only, 3 values stored -1 ignored
        counter++;
        for ( int i = 0; i < column_items; i++ ) {

        // v within v creation
        vector<int> *obj = new vector<int> ;
        columns_storage.push_back( *obj );
        delete obj;
        obj = 0;

        };

        // here the rest of the CSV is cycled within the while loop 3 items at a time, the -1 is sacrificed to get the right readings. Sacrifice necessary for lack of comma at end of CSV rows
        for ( int i = 0; i < column_items; i++ ) {
        getline(room_2, line, ',');
        columns_storage.at(i).push_back( stoi (line.c_str()));
        }



    }
//    int room_type, x, y;

    for ( int j = 0; j < columns_storage.at(0).size() ; j++ ) {
        //cout << columns_storage.at(0).at(j) << "_" << columns_storage.at(1).at(j) << "_" << columns_storage.at(2).at(j) << endl;
        for ( int i = 0; i < column_items; i++ ) {
//            cout << columns_storage.at(i).at(j) << "_ ";

        }
//        cout << "_" << endl;


    }
//    cout << "____" << endl;

    room_2.close();
//    cout << " after close" << endl;

}

// Function will be separate for creating blocks

void room_object::create_blocks() {


    for ( int i = 1; i < (columns_storage.size() / column_items); i++ ) {


        if ( columns_storage.at(0).at(i) > 0 ) {

                block * obj = new block(columns_storage.at(1).at(i), columns_storage.at(2).at(i), columns_storage.at(0).at(i) ) ;
                obj->setContactpoints();
                //cout << *( (adress_pal + i*cols) +ii ) << endl;
                roomblocks.push_back(*obj);
                obj = 0;

        } else {
        }



    }

};







void room_object::room_object_setup() {

    for ( int i = 0; i < rows; i++ ) {
        for ( int ii = 0; ii < cols; ii++ ) {
            if ( *( (adress + i*cols) +ii ) > 0 ) {
                //block * obj = new block(ii*15, i*15, *( (adress_pal + i*cols) +ii ), *( (adress + i*cols) +ii ));
                block * obj = new block(ii*15, i*15, *( (adress + i*cols) +ii ));
                obj->setContactpoints();
                //cout << *( (adress_pal + i*cols) +ii ) << endl;
                roomblocks.push_back(*obj);

                delete obj;
            } else {
            }
        };
    };

};

void room_object::testfunc() {
cout << roomblocks.size() << endl;
};

portal::portal( int type, int x_location, int y_location, int height, int width, int radius, int room_dest, int dest_x, int dest_y ) {

    portal_type = type;
    x_loc = x_location;
    y_loc = y_location;
    portal_height = height;
    portal_width = width;
    portal_radius = radius;

    room_destination = room_dest;
    destination_x = dest_x;
    destination_y = dest_y;

    if ( portal_type == 1 ) {
        sprite_index = 301;
    } else {
    }

    if ( portal_type == 2 ) {
        sprite_index = 301;
    } else {
    }



    portal_config();
};

void portal::portal_config() {


// Sprite relation config
    for (int i=0; i < all_sprites.size(); i++) {
        if ( all_sprites.at(i).sprite_index == sprite_index ) {
            sprite_nr = i;


        } else {

        };
    };

};

void portal::portal_render() {

//cout << "test" << endl;
            int x_off = 0;
            int y_off = 0;

    switch (portal_type) {

        case (1):
        {

            render_requests_quad( sprite_nr, x_loc, y_loc, true, true, true );

            break;
            }
        case (2):
        {
            render_requests_dual(sprite_nr, x_loc, y_loc, true, true, true);
            //render_requests_dual(sprite_nr, x_loc, y_loc-20, true, false);
        break;
        }


        default:
        break;

    };


};



void portal::transport( champ &parameter, int &game_room ) {




    switch (portal_type) {

        case (1):
            //render_primitive_line(x_loc, y_loc, x_loc, y_loc-20, 1, 401);
            p_x = (float)x_loc ;
            p_y = (float)y_loc ;
            //cout << p_x << " flaots " << p_y << endl;
            h_x = (float)parameter.x_location + (float)parameter.width/2  ;
            h_y = (float)parameter.y_location + (float)parameter.height/2  ;



            distance = sqrt( ( (p_x - h_x)*(p_x - h_x) + (p_y - h_y)*(p_y - h_y) ) );

            if (distance <= 20 ) {
                game_room = room_destination;
                parameter.x_location = destination_x;
                parameter.y_location = destination_y;
            } else {
            }

        break;

        default:
        break;

    };


};

room_portal::room_portal(int *address) {
    addr = address;
};

room_portal::room_portal( portal &parameter ) {

    portals.push_back(parameter);
};

room_portal::room_portal( int room ) {

    room_nr = room;
};

void room_portal::load_portalobject(portal &parameter) {

    portals.push_back(parameter);
};




void room_setup() {

int room0_cols = 128;
int room0_rows = 16;
int room0_xlimit_upper = 128 * 15;
int room0_xlimit_lower = 0;
int room0_ylimit_lower = 0;
int room0_ylimit_upper = 16 * 15;
int room0_nr = 0;

int room1_cols = 128;
int room1_rows = 16;
int room1_xlimit_upper = 128 * 15;
int room1_xlimit_lower = 0;
int room1_ylimit_lower = 0;
int room1_ylimit_upper = 16 * 15;
int room1_nr = 1;

int room2_cols = 26;
int room2_rows = 16;
int room2_xlimit_upper = 26 * 15;
int room2_xlimit_lower = 0;
int room2_ylimit_lower = 0;
int room2_ylimit_upper = 16 * 15;
//int nr = 2;



//room_object * new_room1 = new room_object( (int*)room_1,room1_rows, room1_cols, room1_xlimit_upper, room1_xlimit_lower, room1_ylimit_upper, room1_ylimit_lower,0);
room_object * new_room0 = new room_object( "room0.csv", room0_xlimit_upper, room0_xlimit_lower, room0_ylimit_upper, room0_ylimit_lower,0);
room_objects.push_back( *new_room0 );
delete new_room0;

//room_object * new_room2 = new room_object( (int*)room_2, room2_rows, room2_cols, room2_xlimit_upper, room2_xlimit_lower, room2_ylimit_upper, room2_ylimit_lower,1);
room_object * new_room1 = new room_object( "room1.csv", room1_xlimit_upper, room1_xlimit_lower, room1_ylimit_upper, room1_ylimit_lower,1);
room_objects.push_back( *new_room1 );
delete new_room1;

//room_object * new_room3 = new room_object( (int*)room_3, room3_rows, room3_cols, room3_xlimit_upper, room3_xlimit_lower, room3_ylimit_upper, room3_ylimit_lower,2);
room_object * new_room2 = new room_object( "room2.csv", room2_xlimit_upper, room2_xlimit_lower, room2_ylimit_upper, room2_ylimit_lower,2);
room_objects.push_back( *new_room2 );
delete new_room2;



// room portal objects

room_portal * new_1 = new room_portal(1);
room_portal * new_2 = new room_portal(2);
room_portal * new_3 = new room_portal(3);
room_portals.push_back( *new_1 );
room_portals.push_back( *new_2 );
room_portals.push_back( *new_3 );
delete new_1;
delete new_2;
delete new_3;

//R1
portal * portal_room1_1 = new portal(1, 50, 200, 20, 20, 20, 2, 30, 30);
//room_1_portals.load_portalobject( *portal_room1_1 );
room_portals.at(0).load_portalobject(*portal_room1_1);
delete portal_room1_1;

//R3
portal * portal_room3_1 = new portal(1, 252, 200, 20, 20, 20, 0, 30, 30);
//room_1_portals.load_portalobject( *portal_room1_1 );
room_portals.at(2).load_portalobject(*portal_room3_1);
delete portal_room3_1;

};

void room_render_req(int roomnr) {

//cout <<  room_objects.size() << ".\n";

for (int i = 0; i < room_objects.at(roomnr).roomblocks.size(); i++ ) {

room_objects.at(roomnr).roomblocks.at(i).setRender();
};





//        for (int i=0; i < room_objects.at(roomnr).roomblocks.size();i++) {
//        room_objects.at(roomnr).roomblocks.at(i).setRender();
//        };


//    switch (roomnr) {
//
//    case 0:
//        for (int i=0; i < blocks.size();i++) {
//        blocks.at(i).setRender();
//        };
//
//    break;
//    case 1:
//        for (int i=0; i < blocks.size();i++) {
//        blocks.at(i).setRender();
//        };
//
//    break;
//
//    default:
//    break;
//
//    };

};


void roomblocks_simple_deflection( int room, float x_f, float y_f, float &x_v, float &y_v ) {
// simple deflector attempt
int x = (int)x_f;
int y = (int)y_f;


    for ( int i = 0; i < room_objects.at(room).roomblocks.size(); i++ ) {

        if ( x >= room_objects.at(room).roomblocks.at(i).contact_points[0][0]+room_objects.at(room).roomblocks.at(i).x_location && x <= room_objects.at(room).roomblocks.at(i).contact_points[0][1]+room_objects.at(room).roomblocks.at(i).x_location &&
        y >= room_objects.at(room).roomblocks.at(i).contact_points[1][0]+room_objects.at(room).roomblocks.at(i).y_location && y <= room_objects.at(room).roomblocks.at(i).contact_points[1][3]+room_objects.at(room).roomblocks.at(i).y_location ) {

                y_v = -1*y_v;

                if ( x <= room_objects.at(room).roomblocks.at(i).contact_points[0][0]+room_objects.at(room).roomblocks.at(i).x_location ||
                x >= room_objects.at(room).roomblocks.at(i).contact_points[0][1]+room_objects.at(room).roomblocks.at(i).x_location ) {
                    x_v = -1*x_v;
                } else {
                };


        } else {

        };

    };

};













