// cpp file for the buttons

#include <iostream>
#include "render.h"
//~ #include "sprite.h"
#include <vector>
#include "setup_sprites.h"

using namespace std;


render::render(int a){

fill(render_array[0], render_array[0] + (240 + 20) * (320*2 + 20*2), 0);


};


void render::fillColor(int x, int y, unsigned short color){

		byte_2 = color & 0xFF;
		byte_1 = color >> 8;

		render_array[y][x]   = byte_1 ;
		render_array[y][x+1] = byte_2 ;

};

void render::clear() {
fill(render_array[0], render_array[0] + (240 + 20) * (320*2 + 20*2), 0);

};


unsigned char render::getColor(int x, int y) {

	return render_array[y][x];
};

unsigned char render::mutateColor(int RGB, unsigned char color, int palette) {
    // R = 0, G = 1, B = 2
    unsigned char return_value;

    switch ( palette ) {
        case 1:

                switch ( color ) {
                    case 0:
                        return_value = palette_1[0][RGB];
                    break;
                    case 50:
                        return_value = palette_1[1][RGB];
                    break;
                    case 100:
                        return_value = palette_1[2][RGB];
                    break;
                    case 150:
                        return_value = palette_1[3][RGB];
                    break;
                    case 200:
                        return_value = palette_1[4][RGB];
                    break;
                    default:
                    return_value = 255;
                    break;
                };
        break;



    };



return return_value;
};

void render::filler_dev(champ& spritefiller) {

int sprite_current = spritefiller.sprite_current;


	for ( int i = 0; i < all_sprites.at(sprite_current).getHeight(); i++ ) {

		for ( int ii = 0; ii < all_sprites.at(sprite_current).getWidth(); ii++ ) {

			R_888_byte = all_sprites.at(sprite_current).getVector(0 + ii*3 + i*3*all_sprites.at(sprite_current).getWidth());
			G_888_byte = all_sprites.at(sprite_current).getVector(1 + ii*3 + i*3*all_sprites.at(sprite_current).getWidth());
			B_888_byte = all_sprites.at(sprite_current).getVector(2 + ii*3 + i*3*all_sprites.at(sprite_current).getWidth());

			//RGB565 = (((R_888_byte & 0xf8)<<8) + ((G_888_byte & 0xfc)<<3)+(B_888_byte>>3));
			RGB565 = (((mutateColor(0, R_888_byte, 1) & 0xf8)<<8) + ((mutateColor(1,G_888_byte,1) & 0xfc)<<3)+(mutateColor(2, B_888_byte, 1)>>3));

            if ( RGB565 != 0xFFFF ) {
            render::fillColor( spritefiller.getX()+2*ii, spritefiller.getY() +i, RGB565 );
            } else {
            }

//			render::fillColor( spritefiller.getX()+2*ii, spritefiller.getY() +i, RGB565 );

		}

	}



};

void render::filler_general() {

//int sprite_current = spritefiller.sprite_current;
// The render_req vector contain the data of which sprite and position to draw using this function
// all_sprites are the vector that store all sprites, mutate color use the palettes


// iii is the number of items in the render req vector
// ii and i is the horizontal components
    for ( unsigned int iii = 0; iii < render_req.size(); iii++ ) {

        for ( int i = 0; i < all_sprites.at( render_req.at(iii).getSprite_nr() ).getHeight(); i++ ) {

            for ( int ii = 0; ii < all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth(); ii++ ) {

                R_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getVector(0 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                G_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getVector(1 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                B_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getVector(2 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());

                //RGB565 = (((R_888_byte & 0xf8)<<8) + ((G_888_byte & 0xfc)<<3)+(B_888_byte>>3));
                RGB565 = (((mutateColor(0, R_888_byte, 1) & 0xf8)<<8) + ((mutateColor(1,G_888_byte,1) & 0xfc)<<3)+(mutateColor(2, B_888_byte, 1)>>3));

                if ( RGB565 != 0xFFFF ) {
                render::fillColor( render_req.at(iii).getX()+2*ii, render_req.at(iii).getY() +i, RGB565 );
                } else {
                }

            }

        }

    }

// clear items from vector
render_req.clear();


};

// render req object class implementation

vector<render_requests> render_req;

render_requests::render_requests(int sprite, int xpos, int ypos){

sprite_nr = sprite;
x_pos = xpos;
y_pos = ypos;

};


int render_requests::getSprite_nr(){
    return sprite_nr;
};

int render_requests::getX(){
    return x_pos;
};

int render_requests::getY(){
    return y_pos;
};




