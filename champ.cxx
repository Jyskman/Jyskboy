
#include <iostream>
#include "champ.h"
#include <vector>
#include "soundmanager.h"
#include "setup_sprites.h"
#include "render.h"
using namespace std;

//champ::champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter) {
champ::champ(int a, int size, int Height, int Width) {

// Current sprite and palette
sprite_current = 0;
palette_current = 1;


};



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

	return all_sprites.at(sprite_current).getVector(pos);
}


int champ::getSpriteSize() {
	return sprite_size;
}

int champ::getPalette() {

    return palette_current;
}

void champ::setRender()  {
render_requests * obj = new render_requests(sprite_current, x_location, y_location);

render_req.push_back(*obj);
delete obj;
}
