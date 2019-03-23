// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef BUTTONS_H
#define BUTTONS_H
 
 
#include <sr595.h>
#include <iostream>
// This is the content of the .h file, which is where the declarations go


int add(int x, int y); 


class button_input {
	
	
public:
button_input(int a);	// constructor

int nr_buttons = 15;
int button_array[3][15];


void updateState();	
void setJumpstate(int state);	
int getJumpstate();
void printAll();	
};



// This is the end of the header guard
#endif
