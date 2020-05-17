#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <iostream>
#include <vector>
#include "render.h"
#include "champ.h"
#include "game.h"
#include "roomblocks_properties.h"
#include <algorithm>
#include "physics.h"


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
bool grabbed = false;


int contact_points[2][4];
int deflection_points[2][4];
void setContactpoints();

float friction_coeff;

int sprite_nr;
int sprite_index;
bool sprite_error;
bool destructible;
bool destroyed;
bool active = true;


block(int x_pos, int y_pos, int palette, int type);
block(int x_pos, int y_pos, int type);
block(int x_pos, int y_pos, int type, int sprite__index, bool special);
block(int x_pos, int y_pos, int type, int x_start, int x_stop, int y_start, int y_stop );

int xstart, xstop, ystart, ystop;

~block();

void setRender_Block();
int Relation_Spritenr_type(); // need to create a relation between position in all_sprites and type/index
float setFriction(int type);
void set_index();
void destruction();
void motion();
int xvel = 0;
int yvel = 0;

void convey_v( champ * parameter );
bool xvel_communicated;
bool yvel_communicated;

};




extern vector<block> blocks;


class room_object {

    public:
    int room_nr;
    string name;
    int rows, cols;
    int xlim_up, xlim_low, ylim_up, ylim_low;
    
    int xlim_up_set, xlim_low_set, ylim_up_set, ylim_low_set;
    
    int *adress;
    int *adress_pal;
    vector<block> roomblocks;
    vector<block> block_temp;

    room_object(int *arr, int *arr_pal, int row, int col, int x_up, int x_low, int y_up, int y_low, int nr);
    room_object(int *arr, int row, int col, int x_up, int x_low, int y_up, int y_low, int nr);
    room_object( string file, int room);
    ~room_object();

    void room_object_setup();
    void room_object_setupCSV();

    void create_blocks();
    void set_limits();
    void set_terminator();
    void set_modifiers();
    void testfunc();
    int column_items;

    vector< vector<int> > columns_storage ;
    vector< room_limits > limits ;
    vector< stars > starfields ;
    vector< item > room_items;
    vector< item > room_drop_items;
    
    vector< waypoint > room_waypoint;
    
    vector< hitbox_object > terminator_box;
    
    void update_hitbox();
    
    vector<int> type_temp;
    vector<int> x_temp;
    vector<int> y_temp;
    
    
    vector<int> normal_block_sprite_index;
	vector<int> moving_block_sprite_index;
	vector<int> destructible_block_sprite_index;

	void update_limits( int xoff, int yoff, champ &parameter );
	
	void setup_functions();

};



extern vector<room_object> room_objects;
extern vector<room_portal> room_portals;


void room_setup( game *parameter );

void room_render_req(int roomnr, champ &parameter, physics &parameter_physics);

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
