#include <iostream>
#include "sprite.h"
#include <vector>

using namespace std;


sprite::sprite(int a, unsigned char sprites[], int size, int Height, int Width) {

//~ height = Height;
//~ width = Width;
sprite_size = size;


	for (int i = 0; i < sprite_size; i++) {
		imported_sprite[i] = sprites[i];
		imported.push_back(sprites[i]);
		//printf("%d",imported.at(i));
	}

	

};



int sprite::getHeight() {
	return height;
}


int sprite::getWidth() {
	return width;
}

int sprite::getX() {
	return x_location;
}

int sprite::getY() {
	return y_location;
}

void sprite::setX(int x) {
	x_location = x;
}

void sprite::setY(int y) {
	y_location = y;
}

unsigned char sprite::getChar(int pos) {
	return imported_sprite[pos];
	//return imported.at(pos);
}

unsigned char sprite::getVector(int pos) {
	//return imported_sprite[x];
	return imported.at(pos);
}

int sprite::getSpriteSize() {
	return sprite_size;
	}



