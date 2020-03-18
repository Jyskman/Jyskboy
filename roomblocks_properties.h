



// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef ROOMBLOCKS_PROPERTIES_H
#define ROOMBLOCKS_PROPERTIES_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "render.h"
#include "setup_sprites.h"

using namespace std;

class stars {
	
	public:
	stars( int type, int x_low, int y_low, int x_up, int y_up );
	void set_stars();
	void render_stars();
	void sprite_config();
	vector<int> x;
	vector<int> y;
	vector<int> nr;
	
	int field_type;
	int x_lo, y_lo, x_u, y_u;
	
	
	vector<int> sprite_nr;
	vector<int> sprite_index;
	
};




class room_limits {
	
	
	public:
	
	room_limits( int in_x_down_left, int in_y_down_left, int in_x_up_right, int in_y_up_right, int set_x_down_left, int set_y_down_left, int set_x_up_right, int set_y_up_right );
	int x_down_left, y_down_left, x_up_right, y_up_right;
	int x_down_left_set, y_down_left_set, x_up_right_set, y_up_right_set;  
	
	
};





// This is the end of the header guard
#endif
