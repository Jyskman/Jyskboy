#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <iostream>
#include <vector>


using namespace::std;



class block {

public:

int x_location;
int y_location;
int current_palette;
int block_type;
int sprite_nr;
bool sprite_error;

block(int x_pos, int y_pos, int palette, int type);
~block();

void setRender();
int Relation_Spritenr_type(); // need to create a relation between position in all_sprites and type/index
};

extern vector<block> blocks;


class room_object {

public:
int room_nr;

int rows, cols;
int xlim_up, xlim_low, ylim_up, ylim_low;
int *adress;

room_object(int *arr, int row, int col, int x_up, int x_low, int y_up, int y_low, int nr);
~room_object();
};

extern vector<room_object> room_objects;

void room_setup();
void room_render_req(int roomnr);

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
