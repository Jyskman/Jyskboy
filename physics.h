#ifndef PHYS
#define PHYS

#include <vector>
#include <iostream>

using namespace::std;




class physics {

public:
physics( float g_force, float air_force, int index );

void setState(int param);
float getG(int state);

float g;
float air;
int state;

int vector_nr;
//int Relation_nr_type();

};



void physics_setup ();


extern vector<physics> physics_objects;


#endif // PHYS
