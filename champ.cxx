
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
sprite_current = 100; // sprite index, will need to connect to all_sprites
palette_current = 1;
sprite_nr = Relation_Spritenr_type(); // translates the index/current/type to vector position in all_sprites

};

int champ::Relation_Spritenr_type() {
    int return_value = 0;
    sprite_error = true;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == sprite_current ) {
                return_value = i;
                sprite_error = false;

            } else {

            };
        };

    return return_value;

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

        if (sprite_error == false) {
            render_requests * obj = new render_requests(sprite_nr, x_location, y_location);

            render_req.push_back(*obj);
            delete obj;


        } else {
//        cout << "ok" << endl;
        };




}

void champ::updatePos(button_input& parameter){

    if ( parameter.getLeftState() == true ) {
            setX( getX() - 1 );
    } else {
    }

    if ( parameter.getRightState() == true ) {
            setX( getX() + 1 );
    } else {
    }

    if ( parameter.getUpState() == true ) {
            setY( getY() + 1 );
    } else {
    }

    if ( parameter.getDownState() == true ) {
            setY( getY() - 1 );
    } else {
    }

};
