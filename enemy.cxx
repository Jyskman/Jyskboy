#include <iostream>
#include "enemy.h"
#include <vector>
#include "soundmanager.h"
using namespace std;


enemy::enemy(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter) {

height = Height;
width = Width;
sprite_size = size;


	for (int i = 0; i < sprite_size; i++) {
		imported_sprite[i] = sprites[i];
		imported.push_back(sprites[i]);
		//printf("%d",imported.at(i));
	}

	

};

//~ enemy::enemy(int a, std::vector<sprite_objects>& parameter, int size, int Height, int Width) {
	
	//~ std::cout << "overload ok" << endl;
//~ };

int enemy::getHeight() {
	return height;
}


int enemy::getWidth() {
	return width;
}

int enemy::getX() {
	return x_location;
}

int enemy::getY() {
	return y_location;
}

void enemy::setX(int x) {
	x_location = x;
}

void enemy::setY(int y) {
	y_location = y;
}

unsigned char enemy::getChar(int pos) {
	return imported_sprite[pos];
	//return imported.at(pos);
}

unsigned char enemy::getVector(int pos) {
	//return imported_sprite[x];
	return imported.at(pos);
}

int enemy::getSpriteSize() {
	return sprite_size;
	}




