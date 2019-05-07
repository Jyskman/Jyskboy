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

block(int x_pos, int y_pos, int palette, int type);
~block();

void setRender();
};

extern vector<block> blocks;


class room_object {

public:
int height, width;
int *adress;

room_object(int *arr, int row, int col);

};

extern vector<room_object> room_objects;

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
