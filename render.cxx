// cpp file for the buttons

#include <iostream>
#include "render.h"
//~ #include "sprite.h"
#include <vector>

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

void render::filler(champ& spritefiller) {

	for ( int i = 0; i < spritefiller.getHeight(); i++ ) {
		
		for ( int ii = 0; ii < spritefiller.getWidth(); ii++ ) {
			
			R_888_byte = spritefiller.getChar(0 + ii*3 + i*3*spritefiller.getWidth());
			G_888_byte = spritefiller.getChar(1 + ii*3 + i*3*spritefiller.getWidth());
			B_888_byte = spritefiller.getChar(2 + ii*3 + i*3*spritefiller.getWidth());
						
			RGB565 = (((R_888_byte & 0xf8)<<8) + ((G_888_byte & 0xfc)<<3)+(B_888_byte>>3));
			
			
			
			render::fillColor( spritefiller.getX()+2*ii, spritefiller.getY() +i, RGB565 );
			
			
			
		}
		
	}


	
};

unsigned char render::getColor(int x, int y) {
	
	return render_array[y][x];
};
