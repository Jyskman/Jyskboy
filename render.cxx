// cpp file for the buttons

#include <iostream>
#include "render.h"
//~ #include "sprite.h"
#include <vector>
#include "setup_sprites.h"
#include "environment.h"
#include <algorithm>
using namespace std;


render::render(int a){

//fill(render_array[0], render_array[0] + (240 + 20) * (320*2 + 20*2), 0);
fill(render_array[0], render_array[0] + (240) * (320*2), 0);

render_array_pointer = (unsigned char*)render_array;
current_x_offset = 0;
current_y_offset = 0;

internal = &render_req;
};

//test ref passing


void render::determine_current_offset(champ& parameter, int roomnr){
// will determine the current offset for all things not champ
offset_parameter_x_left = 140;
offset_parameter_x_right= (320-offset_parameter_x_left);

current_x_offset = parameter.getX() - ( room_objects.at(roomnr).xlim_low + offset_parameter_x_left );

    if ( parameter.getX() < ( room_objects.at(roomnr).xlim_low + offset_parameter_x_left ) ) {
          current_x_offset = 0;
          //cout << " 1 "  << ".\n";
    } else {

    }


    if ( parameter.getX() > ( room_objects.at(roomnr).xlim_up - offset_parameter_x_right ) ) {
          current_x_offset = room_objects.at(roomnr).xlim_up - offset_parameter_x_right - offset_parameter_x_left;
          //cout << " 2 "  << ".\n";
    } else {
    }
// xoffset done
offset_parameter_y_low = 120;
offset_parameter_y_up = (240 - offset_parameter_y_low);
current_y_offset = parameter.getY() -  room_objects.at(roomnr).ylim_low - offset_parameter_y_low ;

if (parameter.getY() < (room_objects.at(roomnr).ylim_low + offset_parameter_y_low) ) {
    current_y_offset = 0;
} else {
}

if (parameter.getY() > (room_objects.at(roomnr).ylim_up -  offset_parameter_y_up) ) {
    current_y_offset = room_objects.at(roomnr).ylim_up - offset_parameter_y_low - offset_parameter_y_up;
} else {
}

};

bool render::render_limit_check(int x_pos, int y_pos){
// functino will return false if current pos is outside framepos
// render general feeds an already times 2 to this function xpos
return_value = true;
//cout << " 0 "  << ".\n";
    if ( (x_pos - 2*current_x_offset) < 0) {
        return_value = false;
//        cout << " 1 "  << ".\n";
    } else {

    }

    if ( (x_pos - 2*current_x_offset) > 2*(320-1)) {
        return_value = false;
//        cout << " 2 "  << ".\n";
    } else {

    }

    // ypos

    if ( y_pos - current_y_offset < 0) {
        return_value = false;
//        cout << " 1 "  << ".\n";
    } else {

    }

    if ( y_pos - current_y_offset > (240-1)) {
        return_value = false;
//        cout << " 2 "  << ".\n";
    } else {

    }



    return return_value;

};

int render::mutate_Y(int y) {
// transform y kord to fit in the render
int return_value = 240 - y;

return return_value;
};


void render::fillColor(int x, int y, unsigned short color){

		byte_2 = color & 0xFF;
		byte_1 = color >> 8;


            render_array[y][x]   = byte_2 ;
            render_array[y][x+1] = byte_1 ;

};
// Filler dev for direct true color experiment
void render::fillColor_dev(int x, int y, unsigned char color, unsigned char color2){

            render_array[y][x]   = color ;
            render_array[y][x+1] = color2 ;

};


void render::render_clear() {
//fill(render_array[0], render_array[0] + (240 + 20) * (320*2 + 20*2), 0);
fill(render_array[0], render_array[0] + (240) * (320*2), 0);
};



char render::getColor(int x, int y) {

	return render_array[y][x];
};

unsigned char render::mutateColor(int &RGB, unsigned char &color, int &palette) {
    // R = 0, G = 1, B = 2
    unsigned char return_value;

//    switch ( palette ) {
//        case 1:
//
//                switch ( color ) {
//                    case 0:
//                        return_value = palette_1[0][RGB];
//                    break;
//                    case 50:
//                        return_value = palette_1[1][RGB];
//                    break;
//                    case 100:
//                        return_value = palette_1[2][RGB];
//                    break;
//                    case 150:
//                        return_value = palette_1[3][RGB];
//                    break;
//                    case 200:
//                        return_value = palette_1[4][RGB];
//                    break;
//                    default:
//                    return_value = 255;
//                    break;
//                };
//        break;
//
//    };
// Below is alternative to palettefunction above

if (color == 0){
    return_value = palettes_RGB[0 + 5*RGB ][palette];
} else {
}
if (color == 50){
    return_value = palettes_RGB[1 + 5*RGB ][palette];
} else {
}
if (color == 100){
    return_value = palettes_RGB[2 + 5*RGB ][palette];
} else {
}
if (color == 150){
    return_value = palettes_RGB[3 + 5*RGB ][palette];
} else {
}
if (color == 200){
    return_value = palettes_RGB[4 + 5*RGB ][palette];
} else {
}



return return_value;
};

void render::render_req_filter() {
// function will remove render req that are outside the current frame

for ( int i = 0; i < render_req.size(); i++ ) {

    // us the sprite above or below the frame?
    if ( (render_req.at(i).getY() + all_sprites.at(render_req.at(i).getSprite_nr()).getHeight() - current_y_offset) > 239  ) {
        //render_req.at(i).draw = false;
        render_req.at(i).draw_evaluate = true;
    } else {
    }
    if ( (render_req.at(i).getY() - current_y_offset) >= 239 && (render_req.at(i).getY() + all_sprites.at(render_req.at(i).getSprite_nr()).getHeight() - current_y_offset) >= 239 ) {
        render_req.at(i).draw = false;
    } else {
    }


    if ( (render_req.at(i).getY() - current_y_offset) < 0  ) {
        //render_req.at(i).draw = false;
        render_req.at(i).draw_evaluate = true;
    } else {
    }
    if ( (render_req.at(i).getY() - current_y_offset) <= 0 && (render_req.at(i).getY() + all_sprites.at(render_req.at(i).getSprite_nr()).getHeight() - current_y_offset) <= 0 ) {
        render_req.at(i).draw = false;
    } else {
    }

// X below


    if ( (render_req.at(i).getX() + all_sprites.at(render_req.at(i).getSprite_nr()).getWidth() - current_x_offset) > 319  ) {
        render_req.at(i).draw_evaluate = true;
    } else {
    }

    if ( (render_req.at(i).getX() + all_sprites.at(render_req.at(i).getSprite_nr()).getWidth() - current_x_offset) >= 319 && (render_req.at(i).getX() - current_x_offset) >=319  ) {
        render_req.at(i).draw = false;
    } else {
    }

    if ( (render_req.at(i).getX() - current_x_offset) < 0  ) {
        render_req.at(i).draw_evaluate = true;
    } else {
    }
    if ( (render_req.at(i).getX() - current_x_offset) <= 0 && (render_req.at(i).getX() + all_sprites.at(render_req.at(i).getSprite_nr()).getWidth() - current_x_offset) <= 0  ) {
        render_req.at(i).draw = false;
    } else {
    }



}


//all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth()
//all_sprites.at(render_req.at(iii).getSprite_nr()).getHeight()



// removal from render req based on filter
render_req.erase(
    std::remove_if(render_req.begin(), render_req.end(),
        [](const render_requests & o) { return o.draw == false; }),
    render_req.end());

};

void render::filler_dev(int roomnr) {


//int sprite_current = spritefiller.sprite_current;
// The render_req vector contain the data of which sprite and position to draw using this function
// all_sprites are the vector that store all sprites, mutate color use the palettes

// iii is the number of items in the render req vector
// ii and i is the horizontal components
//cout << render_req.size() << ".\n";
render_req_filter();

//cout << render_req.size() << ".\n";

    for ( unsigned int iii = 0; iii < render_req.size(); iii++ ) {

           for ( int i = 0; i < all_sprites.at( render_req.at(iii).getSprite_nr() ).getHeight(); i++ ) {

            for ( int ii = 0; ii < all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth(); ii++ ) {

                R_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getVector(0 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                G_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getVector(1 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                B_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getVector(2 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                    if (R_888_byte != 255 && G_888_byte != 255 && B_888_byte != 255) {
                             //RGB565 = (((R_888_byte & 0xf8)<<8) + ((G_888_byte & 0xfc)<<3)+(B_888_byte>>3));
                            testpal = render_req.at(iii).current_palette - 1;
                            RGB565 = (((mutateColor(R, R_888_byte, testpal) & 0xf8)<<8) + ((mutateColor(G,G_888_byte,testpal) & 0xfc)<<3)+(mutateColor(B, B_888_byte, testpal)>>3));

                            if ( render_req.at(iii).draw_evaluate == true ) {
                                if (render_limit_check( 2*render_req.at(iii).getX()+2*ii, render_req.at(iii).getY()+i )  == true) {
                                render::fillColor( 2*render_req.at(iii).getX()+2*ii - current_x_offset*2,  render_req.at(iii).getY() +i  - current_y_offset, RGB565 );
                                } else {
                                }

                            } else {
                            }
                            if ( render_req.at(iii).draw_evaluate == false ) {
                                render::fillColor( 2*render_req.at(iii).getX()+2*ii - current_x_offset*2,  render_req.at(iii).getY() +i  - current_y_offset, RGB565 );
                            } else {
                            }
                    } else {
                    } // R_888 if statement

            }

        }


    }

// clear items from vector
//cout << render_req.size() << endl;
render_req.clear();

};

void render::filler_general(int roomnr) {

//int sprite_current = spritefiller.sprite_current;
// The render_req vector contain the data of which sprite and position to draw using this function
// all_sprites are the vector that store all sprites, mutate color use the palettes

// iii is the number of items in the render req vector
// ii and i is the horizontal components
//cout << render_req.size() << ".\n";

// This will be true color without palette
render_req_filter();

//cout << render_req.size() << ".\n";

    for ( unsigned int iii = 0; iii < render_req.size(); iii++ ) {

           for ( int i = 0; i < sprite_h.at( render_req.at(iii).getSprite_nr() ) ; i++ ) {

            for ( int ii = 0; ii < sprite_w.at( render_req.at(iii).getSprite_nr() ) ; ii++ ) {

            R_888_byte = *( sprite_address.at( render_req.at(iii).getSprite_nr() ) + 0 + ii*2 + i*2*sprite_w.at( render_req.at(iii).getSprite_nr()  ));
            G_888_byte = *( sprite_address.at( render_req.at(iii).getSprite_nr() ) + 1 + ii*2 + i*2*sprite_w.at( render_req.at(iii).getSprite_nr()  ));

                //R_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getChar(0 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                //G_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getChar(1 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                //B_888_byte = all_sprites.at(render_req.at(iii).getSprite_nr()).getVector(2 + ii*3 + i*3*all_sprites.at(render_req.at(iii).getSprite_nr()).getWidth());
                   if (R_888_byte != 255 && G_888_byte != 255) {
                             //RGB565 = (((R_888_byte & 0xf8)<<8) + ((G_888_byte & 0xfc)<<3)+(B_888_byte>>3));
                            //testpal = render_req.at(iii).current_palette - 1;
                            //RGB565 = (((mutateColor(R, R_888_byte, testpal) & 0xf8)<<8) + ((mutateColor(G,G_888_byte,testpal) & 0xfc)<<3)+(mutateColor(B, B_888_byte, testpal)>>3));
                            //RGB565 = ( ( (R_888_byte & 0xf8)<<8) + ((G_888_byte & 0xfc)<<3) + (B_888_byte>>3) );

                            if ( render_req.at(iii).draw_evaluate == true ) {
                                if (render_limit_check( 2*render_req.at(iii).getX()+2*ii, render_req.at(iii).getY()+i )  == true) {
                                fillColor_dev( 2*render_req.at(iii).getX()+2*ii - current_x_offset*2,  render_req.at(iii).getY() +i  - current_y_offset, R_888_byte, G_888_byte );
                                } else {
                                }

                            } else {
                            }
                            if ( render_req.at(iii).draw_evaluate == false ) {
                                fillColor_dev( 2*render_req.at(iii).getX()+2*ii - current_x_offset*2,  render_req.at(iii).getY() +i  - current_y_offset, R_888_byte, G_888_byte );
                            } else {
                            }
                   } else {
                   } // R_888 if statement

            }

        }


    }


render_req.clear();


};

void render::load_sprite_data(unsigned char* add, int width, int height){

sprite_address.push_back(add);
sprite_h.push_back(height);
sprite_w.push_back(width);

};

// render req object class implementation

vector<render_requests> render_req;

render_requests::render_requests(int sprite, int xpos, int ypos, int palette){

sprite_nr = sprite;
x_pos = xpos;
y_pos = ypos;
draw = true;
draw_evaluate = false;
current_palette = palette;

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

bool render_requests::getDraw(const render_requests & o) {
    return draw;
}

