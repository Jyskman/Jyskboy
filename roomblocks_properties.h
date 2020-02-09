



// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef ROOMBLOCKS_PROPERTIES_H
#define ROOMBLOCKS_PROPERTIES_H

#include <iostream>



class room_limits {
	
	
	public:
	
	room_limits( int in_x_up_left, int in_y_up_left, int in_x_down_right, int in_y_down_right, int set_x_up_left, int set_y_up_left, int set_x_down_right, int set_y_down_right );
	int x_up_left, y_up_left, x_down_right, y_down_right;
	int x_up_left_set, y_up_left_set, x_down_right_set, y_down_right_set;  
	
	
};





// This is the end of the header guard
#endif
