#ifndef ENVIRONMENT
#define ENVIRONMENT





class block {



public:

int x_location;
int y_location;
int current_palette;
int block_type;

block(int x_pos, int y_pos, int palette, int type);
~block();

void render_request();
};








#endif
