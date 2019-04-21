

// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H



#include <iostream>
#include <vector>




class sprite_objects {



public:


sprite_objects(int a, unsigned char sprites[], int size, int width, int height);


int sprite_size;
int sprite_widht;
int sprite_height;

void sprite_test();
std::vector<unsigned char> sprite_imported;

int getHeight();
int getWidth();
int getSize();


unsigned char getVector(int x);

};






















// This is the end of the header guard
#endif
