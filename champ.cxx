
#include <iostream>
#include "champ.h"
#include <vector>
#include "soundmanager.h"
using namespace std;

//champ::champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter) {
champ::champ(int a, int size, int Height, int Width, std::vector<sprite_objects>& parameter) {

// Current sprite and palette
sprite_current = 3;
palette_current = 1;

height = parameter.at( sprite_current ).getHeight();
width = parameter.at( sprite_current ).getWidth();
sprite_size = parameter.at( sprite_current ).getSize();


	for (int i = 0; i < sprite_size; i++) {
//		imported_sprite[i] = sprites[i];
		//~ imported.push_back(sprites[i]);
		imported.push_back( parameter.at(sprite_current).getVector(i) );
	}

};

//~ champ::champ(int a, std::vector<sprite_objects>& parameter, int size, int Height, int Width) {

	//~ std::cout << "overload ok" << endl;
//~ };

int champ::getHeight() {
	return height;
}


int champ::getWidth() {
	return width;
}

int champ::getX() {
	return x_location;
}

int champ::getY() {
	return y_location;
}

void champ::setX(int x) {
	x_location = x;
}

void champ::setY(int y) {
	y_location = y;
}

unsigned char champ::getChar(int pos) {
	//~ return imported_sprite[pos];
	return imported.at(pos);
}

unsigned char champ::getVector(int pos) {
	//return imported_sprite[x];
	return imported.at(pos);
}

int champ::getSpriteSize() {
	return sprite_size;
}

int champ::getPalette() {

    return palette_current;
}



