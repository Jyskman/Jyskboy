#include <iostream>
#include "sprite_objects.h"
#include <vector>

using namespace std;



sprite_objects::sprite_objects(int a, unsigned char sprites[], int size) {

sprite_size = size;


	for (int i = 0; i < sprite_size; i++) {
		
		sprite_imported.push_back(sprites[i]);
		
	}

}; 

unsigned char sprite_objects::getVector(int pos) {
	
	return sprite_imported.at(pos);
}

void sprite_objects::sprite_test() {
	printf("Enemy body 1 object - ok \n");
}