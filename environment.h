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






#endif