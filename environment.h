#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <iostream>
#include <vector>
#include "render.h"
#include "champ.h"
#include "game.h"
using namespace::std;


class portal {

    public:
    portal( int type, int x_location, int y_location, int height, int width, int radius, int room_dest, int dest_x, int dest_y );
    void transport( champ &parameter, int &game_room );
    void portal_render();
    void portal_config();
    int portal_type;
    int distance = 0;
    int sprite_nr;
    int sprite_index;
    int x_loc, y_loc, portal_height, portal_width, portal_radius, room_destination, destination_x, destination_y;

    float p_x, p_y, h_x, h_y;


};

class room_portal {

    public:
    room_portal( int *address );
    room_portal( portal &parameter );
    room_portal( int room );
    void load_portalobject(portal &parameter);
    int *addr;
    int room_nr;
    vector<portal> portals;

};




class block {

public:

int x_location;
int y_location;
int current_palette;
int block_type;

int contact_points[2][4];
void setContactpoints();

float friction_coeff;

int sprite_nr;
int sprite_index;
bool sprite_error;
bool destructible;
bool destroyed;

block(int x_pos, int y_pos, int palette, int type);
block(int x_pos, int y_pos, int type);
~block();

void setRender();
int Relation_Spritenr_type(); // need to create a relation between position in all_sprites and type/index
float setFriction(int type);
void set_index();
};

extern vector<block> blocks;


class room_object {

    public:
    int room_nr;
    string name;
    int rows, cols;
    int xlim_up, xlim_low, ylim_up, ylim_low;
    int *adress;
    int *adress_pal;
    vector<block> roomblocks;

    room_object(int *arr, int *arr_pal, int row, int col, int x_up, int x_low, int y_up, int y_low, int nr);
    room_object(int *arr, int row, int col, int x_up, int x_low, int y_up, int y_low, int nr);
    room_object( string file, int room);
    ~room_object();

    void room_object_setup();
    void room_object_setupCSV();

    void create_blocks();
    void set_limits();
    void testfunc();
    int column_items;

    vector< vector<int> > columns_storage ;

};

extern vector<room_object> room_objects;
extern vector<room_portal> room_portals;


void room_setup( game *parameter );

void room_render_req(int roomnr, game *parameter);

void roomblocks_simple_deflection( int room, float x_f, float y_f, float &x_v, float &y_v );

void roomblocks_attack_interaction( int room, vector<attack> &parameter );











// Just an example
//#include <iostream>
//using namespace std;
//
//void print(int *arr, int row, int col)
//{
//     for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            cout << *((arr + i * col) + j) << " " ;
//         }
//      }
//}
//
//int main()
//{
//    int arr[2][2] = { {1, 4},{ 2, 9} };
//
//    print((int*)arr,2,2);
//
//    return 0;
//}

#endif
