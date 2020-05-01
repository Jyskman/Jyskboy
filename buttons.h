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
int button_array[4][15];
int *button_array_pointer = (int*)button_array;

void updateState();
void setJumpstate(int state);

bool getJumpState();
bool getShootState();
bool getXState();
bool getAState();

bool getUpState();
bool getDownState();
bool getLeftState();
bool getRightState();

bool getStartState();
bool getSelectState();

bool getJumpstate_justpressed();
bool getJumpstate_justreleased();

bool getXstate_justpressed();

void printAll();
};



// This is the end of the header guard
#endif
