// cpp file for the buttons

#include <iostream>
#include "render.h"
//~ #include "sprite.h"
#include <vector>
#include "setup_sprites.h"
#include "environment.h"
#include <algorithm>
#include <cmath>
#include <math.h>
using namespace std;


void particle_generator( int x_pos, int y_pos, int animation_type_as_index, int animation_type, bool random_v, int cycles, int random_factor ) {

    int rand_v_x = rand() % random_factor - rand() % random_factor  ;
    int rand_v_y = -1*rand() % random_factor - rand() % random_factor;

    animation_requests * obj_e1 = new animation_requests(animation_type_as_index, animation_type, 1, true, true , cycles,
    x_pos, y_pos ,
    rand_v_x, rand_v_y);
    anime_req.push_back(*obj_e1);
    delete obj_e1;
    obj_e1 = 0;

};

void particle_generator( int x_pos, int y_pos, int animation_type_as_index , int animation_type, int v_x, int v_y, int cycles ) {

    int rand_v_x = v_x;
    int rand_v_y = v_y;

    animation_requests * obj_e1 = new animation_requests(animation_type_as_index, animation_type, 1, true, true , cycles,
    x_pos, y_pos ,
    rand_v_x, rand_v_y);
    anime_req.push_back(*obj_e1);
    delete obj_e1;
    obj_e1 = 0;

};
// Enemy destruction variant to destroy all enemy components
void particle_generator( enemy *parameter, int x_pos, int y_pos, int cycles ) {

    int vx = 1;
    int vy = 1;
    int explosion_v = 3;

    int animation_type = 5;

    for ( int i = 0; i < parameter->RSV.size() ; i++ ) {


    if ( parameter->destroy_v_x != 0 ) {
        vx = parameter->destroy_v_x / abs(parameter->destroy_v_x);
    } else {
    };
    if ( parameter->destroy_v_y != 0 ) {
        vy = -1*parameter->destroy_v_y / abs(parameter->destroy_v_y);
        if ( rand() % 2 == 1 ) {
            vx = vx *-1;
        } else {
        }
    } else {
    };



        //cout << parameter->RSV.at(i).f_2 << "hej" << endl;
        animation_requests * obj_e1 = new animation_requests(parameter->RSV.at(i).index, 6, 1,
        true, true,
        cycles,
        parameter->RSV.at(i).RSV_x_store, parameter->RSV.at(i).RSV_y_store ,
        vx * (explosion_v + rand() % 6 ), -1* (explosion_v + rand() % 6 )*vy  );
        anime_req.push_back(*obj_e1);
        delete obj_e1;
        obj_e1 = 0;


        animation_requests * obj_e = new animation_requests(12, parameter->RSV.at(i).RSV_x_store + all_sprites.at(parameter->RSV.at(i).sprite_nr).getWidth()/2,
        parameter->RSV.at(i).RSV_y_store + all_sprites.at(parameter->RSV.at(i).sprite_nr).getHeight()/2 , 0, 0);
        anime_req.push_back(*obj_e);
        delete obj_e;

    }




};




void render_requests_quad(int sprite_nr, int x_loc, int y_loc, bool white_border, bool center, bool right_orientation ) {

        int minus_one = 0;
        int x = 0;
        int y = 0;
        bool right_1 = false;
        bool right_2 = true;
        bool right_3 = false;
        bool right_4 = true;

        if ( right_orientation == false ) {
            right_1 = !right_1;
            right_2 = !right_2;
            right_3 = !right_3;
            right_4 = !right_4;

        } else {
        }


        if ( center == true ) {
            x = all_sprites.at(sprite_nr).getWidth() -1;
            y = all_sprites.at(sprite_nr).getHeight() -1;

        }


        if ( white_border == true ) {
            minus_one = 1;
        } else {
        }

        int x_off = all_sprites.at(sprite_nr).getWidth() - 1 - minus_one;
        int  y_off = all_sprites.at(sprite_nr).getHeight() - 1 - minus_one;

        render_requests * obj_x  = new render_requests(sprite_nr, x_loc -x,            y_loc-y,                 1, right_1, true, 1);
        render_requests * obj_x2 = new render_requests(sprite_nr, x_loc+x_off-x,            y_loc-y,            1, right_2, true, 1);
        render_requests * obj_x3 = new render_requests(sprite_nr, x_loc-x,            y_loc+y_off-y,            1, right_3, false, 1);
        render_requests * obj_x4 = new render_requests(sprite_nr, x_loc+x_off-x,            y_loc+y_off-y,      1, right_4, false, 1);
        render_req.push_back( *obj_x );
        render_req.push_back( *obj_x2 );
        render_req.push_back( *obj_x3 );
        render_req.push_back( *obj_x4 );
        delete obj_x;
        delete obj_x2;
        delete obj_x3;
        delete obj_x4;

        //render_primitive_line(x_loc, y_loc, x_loc, y_loc-20, 1, 401);


};

void render_requests_dual( int sprite_nr, int x_loc, int y_loc, bool white_border, bool center, bool center_orientation ) {

        int minus_one = 0;
        int x = 0;
        int y = 0;

        bool right_orientation_1 = true;
        bool right_orientation_2 = false;

        if ( center_orientation == false ) {
            right_orientation_1 = false;
            right_orientation_2 = true;
        } else {
        }


        if ( center == true ) {
            x = all_sprites.at(sprite_nr).getWidth() -1;
            y = all_sprites.at(sprite_nr).getHeight()/2 ;

        }


        if ( white_border == true ) {
            minus_one = 1;
        } else {
        }

        int  x_off = all_sprites.at(sprite_nr).getWidth() - 1 - minus_one;
        int  y_off = all_sprites.at(sprite_nr).getHeight() - 1 - minus_one;

        render_requests * obj_x  = new render_requests(sprite_nr, x_loc+x_off - x,          y_loc-y,           1, right_orientation_1, true, 1);
        render_requests * obj_x2 = new render_requests(sprite_nr, x_loc - x,                y_loc-y,           1, right_orientation_2, true, 1);

        render_req.push_back( *obj_x );
        render_req.push_back( *obj_x2 );

        delete obj_x;
        delete obj_x2;

        //render_primitive_line(x_loc, y_loc, x_loc-10, y_loc-50, 1, 401);

};


// Orientation 0 - vertical
void render_primitive_line( int x_start, int y_start, int x_stop, int y_stop, int orientation, int sprite_index ) {

int x_size = x_stop - x_start;
int y_size = y_stop - y_start;
int x_sign = 1;
int y_sign = 1;
int sprite_nr;

float line_length = sqrt(  (float(y_stop) - float(y_start) )*( float(y_stop) - float(y_start) ) + ( float(x_stop) - float(x_start) )*( float(x_stop) - float(x_start) )  );

    for (int i=0; i < all_sprites.size(); i++) {
        if ( all_sprites.at(i).sprite_index == sprite_index ) {

            sprite_nr = i;
        } else {

        };
    };


    if ( x_size < 0 || x_size > 0 ) {
        x_sign = x_size/abs(x_size);
    };
    if ( y_size < 0 || y_size > 0 ) {
        y_sign = y_size/abs(y_size);
    };


    switch ( orientation ) {

        case (0):

            for ( int i = 0; i < abs(y_size); i++ ) {
            render_requests * obj = new render_requests(sprite_nr, x_start, y_start + i*y_sign, 1);

            render_req.push_back(*obj);
            delete obj;

            }



        break;



        case (1):
            {
                float alfa_radian = acos (  ( float(x_stop) - float(x_start) ) / line_length );
                float alfa = alfa_radian*( 360/(2*M_PI) );

                //cout << alfa << endl;
                if ( y_stop < y_start ) {
                    y_sign = -1;
                } else {
                    y_sign = 1;
                }


                for ( int i = 0; i < int(line_length); i++ ) {

                float x = float(x_start) + (line_length-i)*cos( alfa_radian );
                float y = float(y_start) + y_sign*(line_length-i)*sin( alfa_radian );



                    for ( int i = 0; i < int(line_length); i++ ) {

                        render_requests * obj = new render_requests(sprite_nr, int(x), int(y), 1);

                        render_req.push_back(*obj);
                        delete obj;

                    };


                };


        break;
        };

        case (2):
        default:
        break;

        break;


    };


};



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

//~ cout << "start" << endl;
//~ cout << room_objects.at(roomnr).xlim_low << room_objects.at(roomnr).ylim_low << room_objects.at(roomnr).xlim_up << room_objects.at(roomnr).ylim_up << endl;
//~ cout << room_objects.at(roomnr).xlim_low_set << room_objects.at(roomnr).ylim_low_set << room_objects.at(roomnr).xlim_up_set << room_objects.at(roomnr).ylim_up_set << endl;
//~ cout << "end" << endl;





//current_x_offset = parameter.getX() - ( room_objects.at(roomnr).xlim_low + offset_parameter_x_left );
current_x_offset = room_objects.at(roomnr).xlim_low + ( parameter.getX() - offset_parameter_x_left - room_objects.at(roomnr).xlim_low  );
    if ( parameter.getX() < ( room_objects.at(roomnr).xlim_low + offset_parameter_x_left ) ) {
          //current_x_offset = 0;
          current_x_offset = room_objects.at(roomnr).xlim_low;
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
offset_parameter_y_up =  (240 - offset_parameter_y_low);
current_y_offset = room_objects.at(roomnr).ylim_low + ( parameter.getY() - offset_parameter_y_low - room_objects.at(roomnr).ylim_low  );
//~ cout << current_y_offset << " 1" << endl;


if (parameter.getY() > (room_objects.at(roomnr).ylim_up -  offset_parameter_y_up) ) {
    current_y_offset = room_objects.at(roomnr).ylim_up - offset_parameter_y_low - offset_parameter_y_up;
    //~ current_y_offset = room_objects.at(roomnr).ylim_up - room_objects.at(roomnr).ylim_low - offset_parameter_y_low - offset_parameter_y_up;
	//~ cout << current_y_offset << "  2" << endl;
} else {
}



if (parameter.getY() < (room_objects.at(roomnr).ylim_low + offset_parameter_y_low ) ) {
    current_y_offset = room_objects.at(roomnr).ylim_low;
	//~ cout << current_y_offset << " 3" << endl;

} else {
}
	//~ cout << " end" << parameter.y_location << endl;
//~ if (parameter.getY() > (room_objects.at(roomnr).ylim_up -  offset_parameter_y_up) ) {
    //~ current_y_offset = room_objects.at(roomnr).ylim_up - offset_parameter_y_low - offset_parameter_y_up;

//~ } else {
//~ }



room_objects.at(roomnr).update_limits( current_x_offset, current_y_offset, parameter );

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
// introducing the p1 and p2 to handle rotated geometry

for ( int i = 0; i < render_req.size(); i++ ) {
    // rotation parameters
    filter_w = all_sprites.at(render_req.at(i).getSprite_nr()).getWidth();
    filter_h = all_sprites.at(render_req.at(i).getSprite_nr()).getHeight();
    if ( render_req.at(i).rotation == 2 ) {
    filter_w = all_sprites.at(render_req.at(i).getSprite_nr()).getHeight();
    filter_h = all_sprites.at(render_req.at(i).getSprite_nr()).getWidth();
    } else {
    }


    // us the sprite above or below the frame?
    if ( (render_req.at(i).getY() + filter_h - current_y_offset) > 239  ) {
        //render_req.at(i).draw = false;
        render_req.at(i).draw_evaluate = true;
    } else {
    }
    if ( (render_req.at(i).getY() - current_y_offset) >= 239 && (render_req.at(i).getY() + filter_h - current_y_offset) >= 239 ) {
        render_req.at(i).draw = false;
    } else {
    }


    if ( (render_req.at(i).getY() - current_y_offset) < 0  ) {
        //render_req.at(i).draw = false;
        render_req.at(i).draw_evaluate = true;
    } else {
    }
    if ( (render_req.at(i).getY() - current_y_offset) <= 0 && (render_req.at(i).getY() + filter_h - current_y_offset) <= 0 ) {
        render_req.at(i).draw = false;
    } else {
    }

// X below


    if ( (render_req.at(i).getX() + filter_w - current_x_offset) > 319  ) {
        render_req.at(i).draw_evaluate = true;
    } else {
    }

    if ( (render_req.at(i).getX() + filter_w - current_x_offset) >= 319 && (render_req.at(i).getX() - current_x_offset) >=319  ) {
        render_req.at(i).draw = false;
    } else {
    }

    if ( (render_req.at(i).getX() - current_x_offset) < 0  ) {
        render_req.at(i).draw_evaluate = true;
    } else {
    }
    if ( (render_req.at(i).getX() - current_x_offset) <= 0 && (render_req.at(i).getX() + filter_w - current_x_offset) <= 0  ) {
        render_req.at(i).draw = false;
    } else {
    }


	// Static overide
	if ( render_req.at(i).static_render == true ) {
	
		render_req.at(i).draw = true;
		render_req.at(i).draw_evaluate = false;
	
	} else {
	};


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

        if ( render_req.at(iii).orientation == true ) {
        horisontal_p1 = 1;
        horisontal_p2 = 0;
        } else {
        }
        if( render_req.at(iii).orientation == false ) {
        horisontal_p1 = -1;
        horisontal_p2 = sprite_w.at( render_req.at(iii).getSprite_nr() )-1;
        } else {
        }
        //Vertical flip
        if( render_req.at(iii).up_down == true ) {
        vertical_p1 = 1;
        vertical_p2 = 0;
        } else {
        }
        if( render_req.at(iii).up_down == false ) {
        vertical_p1 = -1;
        vertical_p2 = sprite_h.at( render_req.at(iii).getSprite_nr() )-1;
        } else {
        }


           for ( int i = 0; i < sprite_h.at( render_req.at(iii).getSprite_nr() ) ; i++ ) {

            for ( int ii = 0; ii < sprite_w.at( render_req.at(iii).getSprite_nr() ) ; ii++ ) {
            //( horisontal_p1*ii + horisontal_p2 )
            // Named R/G byte but new version of render has true color and do not use palette
            R_888_byte = *( sprite_address.at( internal->at(iii).getSprite_nr() ) + 0 + ( horisontal_p1*ii + horisontal_p2 )*2 + ( vertical_p1*i + vertical_p2 )*2*sprite_w.at( internal->at(iii).getSprite_nr()  ));
            G_888_byte = *( sprite_address.at( internal->at(iii).getSprite_nr() ) + 1 + ( horisontal_p1*ii + horisontal_p2 )*2 + ( vertical_p1*i + vertical_p2 )*2*sprite_w.at( internal->at(iii).getSprite_nr()  ));

					if ( render_req.at(iii).static_render == true ) {
						null_static = 0;
					} else {
						null_static = 1;
					};

                   if (R_888_byte != 255 && G_888_byte != 255) {

                            rotation_p1 = 2*ii - current_x_offset*2*null_static;
                            rotation_p2 = i - current_y_offset*null_static;
                            render_limit_p1 = 2*ii;
                            render_limit_p2 = i;
                            if ( render_req.at(iii).rotation == 2 ) {
                                    rotation_p1 =2*i - current_x_offset*2*null_static;
                                    rotation_p2 =ii - current_y_offset*null_static;
                                    render_limit_p1 = i*2;
                                    render_limit_p2 = ii;
                            } else {
                            }

                            if ( render_req.at(iii).draw_evaluate == true  ) {
                                if (render_limit_check( 2*render_req.at(iii).getX()+render_limit_p1, render_req.at(iii).getY()+render_limit_p2 )  == true) {
                                fillColor_dev( 2*render_req.at(iii).getX()+rotation_p1,  render_req.at(iii).getY() +rotation_p2, R_888_byte, G_888_byte );
                                } else {
                                }

                            } else {
                            }
                            if ( render_req.at(iii).draw_evaluate == false ) {
                                fillColor_dev( 2*render_req.at(iii).getX()+rotation_p1,  render_req.at(iii).getY() +rotation_p2, R_888_byte, G_888_byte );
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
vector<animation_requests> anime_req;

render_requests::render_requests(int sprite, int xpos, int ypos, int palette){

sprite_nr = sprite;
x_pos = xpos;
y_pos = ypos;
draw = true;
draw_evaluate = false;
current_palette = palette;
orientation = true;
up_down = true;
rotation = 1;
checkers = false;
};

render_requests::render_requests(int sprite, int xpos, int ypos, bool static_){

sprite_nr = sprite;
x_pos = xpos;
y_pos = ypos;
draw = true;
draw_evaluate = false;
current_palette = 1;
orientation = true;
up_down = true;
rotation = 1;
checkers = false;
static_render = static_;
};

render_requests::render_requests(int sprite, int xpos, int ypos, int palette, bool right_orientation, bool up_orientation, int rot ){

sprite_nr = sprite;
x_pos = xpos;
y_pos = ypos;
draw = true;
draw_evaluate = false;
current_palette = palette;
orientation = right_orientation;
up_down = up_orientation;
rotation = rot;
checkers = false;

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

// Animation req system


void animation_requests::sprite_setup( int index ) {
            if ( current_cycle == 0 ) {
                for (int i=0; i < all_sprites.size(); i++) {
                    if ( all_sprites.at(i).sprite_index == index ) {

                    sprite_nr = i;
                    } else {

                    };
                };


            } else {
            };

};

void animation_requests::animation_as_index() {

    if ( animation_as_nr > 0 )  {

        sprite_index = animation_as_nr;
    } else {
    };

};


void animation_requests::modifier() {


    switch (anime_nr) {

        case (1):
        break;
        case (2):
        break;
        case (3):
        break;
        case (4):
        break;
        case (5):
//            rotation = rand() % 2 + 1;
//            if ( rotation == 2 ) {
//                right_orientation = false;
//            } else {
//                right_orientation = true;
//            }

            switch (state) {
                case(1):
                rotation = 1;
                right_orientation = true;
                up_orientation = true;
                break;
                case(2):
                rotation = 2;
                right_orientation = true;
                up_orientation = false;
                break;
                case(3):
                rotation = 1;
                right_orientation = false;
                up_orientation = false;
                break;
                case(4):
                rotation = 2;
                right_orientation = false;
                up_orientation = true;
                break;

            }
            state++;
            if (state >4){
                state = 1;
            } else {
            };
        break;
        case(6):
        if ( current_cycle == cycles-1 ) {
            animation_requests * obj_e = new animation_requests(12, x + all_sprites.at(sprite_nr).getWidth()/2,
            y + all_sprites.at(sprite_nr).getHeight()/2 , 0, 0);
            anime_req.push_back(*obj_e);
            delete obj_e;

        }

        break;


    };


};

animation_requests::animation_requests(int animation_nr_as_index, int animation_nr, int rot, bool facing_right,bool facing_up , int cycles_to_terminate, int x_start, int y_start, int x_vel_start, int y_vel_start) {
animation_as_nr = animation_nr_as_index;
rotation = rot;
anime_nr = animation_nr;
cycles = cycles_to_terminate;
up_orientation = facing_up;
x = x_start;
y = y_start;
x_v = x_vel_start;
y_v = y_vel_start;
current_cycle = 0;
right_orientation = facing_right;

x_v_float = (float)x_v;
y_v_float = (float)y_v;
x_float = (float)x;
y_float = (float)y;

update_position_case = 0;
update_position_case = anime_nr;



    switch (animation_nr) {

        case (1):{

            sprite_index = 401;
            animation_as_index();
            sprite_setup( sprite_index );



        break;
        }

        case (2): {
            sprite_index = 402;
            animation_as_index();
            sprite_setup( sprite_index );
            sprite_width = all_sprites.at(sprite_nr).getWidth();
        break;
        }

        case (3):
        break;

        case (4):
            sprite_index = 403;
            animation_as_index();
            sprite_setup( sprite_index );
            sprite_width = all_sprites.at(sprite_nr).getWidth();
            update_position_case = 2;
        break;

        case (5):
            sprite_index = 405;
            animation_as_index();
            sprite_setup( sprite_index );
            sprite_width = all_sprites.at(sprite_nr).getWidth();
            update_position_case = 2;
            state = rand() % 4 + 1;
        break;

        case (6):
        // ends with another animation
            sprite_index = 111;
            animation_as_index();
            sprite_setup( sprite_index );
            sprite_width = all_sprites.at(sprite_nr).getWidth();
            update_position_case = 2;
        default:
        break;

    };




};

animation_requests::animation_requests( int profile_index, int x_start, int y_start, int x_vel_start, int y_vel_start ) {

anime_nr = 3;
update_position_case = 3;
x = x_start;
y = y_start;
x_v = x_vel_start;
y_v = y_vel_start;
current_cycle = 0;



x_v_float = (float)x_v;
y_v_float = (float)y_v;
x_float = (float)x;
y_float = (float)y;
profile_setup(profile_index);
};

// This one is just for the hero upgrade animation
animation_requests::animation_requests( int *x_start, int *y_start, int x_vel_start, int y_vel_start, bool upgrade_scan ) {

anime_nr = 4;
update_position_case = 4;

x_pos = x_start;
y_pos = y_start;

x = *x_start;
y = *y_start;



x_v = x_vel_start;
y_v = y_vel_start;
current_cycle = 0;
cycles = 25;


x_v_float = (float)x_v;
y_v_float = (float)y_v;
x_float = (float)x;
y_float = (float)y;
//~ profile_setup(profile_index);
};

void animation_requests::profile_setup(int profile_index_parameter) {

    for ( int i = 0; i < animation_profiles.size(); i++ ) {

        if ( animation_profiles.at(i).animation_index == profile_index_parameter ) {
            profile_nr = i;

        } else {
        }
    }

};

void animation_requests::update_position( physics &parameter, int room ) {



    switch (update_position_case) {

    case (1):

            y_v_float = y_v_float + 1;

                if ( y_v_float > parameter.g ) {
                y_v_float = parameter.g;
                } else {
                }

            x_v_float = x_v_float*parameter.air;


            x_float = x_float + x_v_float;
            y_float = y_float + y_v_float;

            x = (int)x_float;

            y = (int)y_float;

        for ( int i = 0; i < room_objects.at(room).roomblocks.size(); i++ ) {

            if ( x > room_objects.at(room).roomblocks.at(i).contact_points[0][0] && x < room_objects.at(room).roomblocks.at(i).contact_points[0][1] &&
            y > room_objects.at(room).roomblocks.at(i).contact_points[1][0] && y < room_objects.at(room).roomblocks.at(i).contact_points[1][1] ) {
                destroy = true;
            } else {

            };

        };

    break;


    case (2):

            //y_v_float = y_v_float + 1;

                if ( y_v_float > parameter.g ) {
                //y_v_float = parameter.g;
                } else {
                }

//            x_v_float = x_v_float*parameter.air;
            //x_v_float = x_v_float*0.90;
            parameter.calculate_velocity(y_v_float, x_v_float, 0.1, 1);


            x_float = x_float + x_v_float;
            y_float = y_float + y_v_float;

            x = (int)x_float;

            y = (int)y_float;



            for ( int i = 0; i < room_objects.at(room).roomblocks.size(); i++ ) {

            if ( x >= room_objects.at(room).roomblocks.at(i).contact_points[0][0]+room_objects.at(room).roomblocks.at(i).x_location && x <= room_objects.at(room).roomblocks.at(i).contact_points[0][1]+room_objects.at(room).roomblocks.at(i).x_location &&
            y >= room_objects.at(room).roomblocks.at(i).contact_points[1][0]+room_objects.at(room).roomblocks.at(i).y_location && y <= room_objects.at(room).roomblocks.at(i).contact_points[1][3]+room_objects.at(room).roomblocks.at(i).y_location ) {

            y_v_float = -1*y_v_float;
                if ( x <= room_objects.at(room).roomblocks.at(i).contact_points[0][0]+room_objects.at(room).roomblocks.at(i).x_location ||
                x >= room_objects.at(room).roomblocks.at(i).contact_points[0][1]+room_objects.at(room).roomblocks.at(i).x_location ) {
                    x_v_float = -1*x_v_float;
                } else {
                };


            } else {

            };

        };
    break;

    case (3):

            for ( int i = 0; i < animation_profiles.at(profile_nr).animate_type.size() ; i++ ) {

                if ( current_cycle >= animation_profiles.at(profile_nr).animate_from_cycle.at(i) && current_cycle < animation_profiles.at(profile_nr).animate_to_cycle.at(i) ) {
                //cout << animation_profiles.at(profile_nr).animate_main_nr.at(i) << endl;
                    if ( animation_profiles.at(profile_nr).animate_subject_to_physics.at(i) == true ) {
                        y_v_float = y_v_float;
                        x_v_float = x_v_float;

                            if ( y_v_float > parameter.g ) {
                            //y_v_float = parameter.g;
                            } else {
                            }

                        x_v_float = x_v_float;

                    } else {
                    }


                } else {
                }

            }





            x_float = x_float + x_v_float;
            y_float = y_float + y_v_float;

            x = (int)x_float;

            y = (int)y_float;
    break;
    case (4):
    
		y = * y_pos;
		x = * x_pos;
    

		
    
    break;
    
    case (5):
			
			parameter.calculate_velocity(y_v_float, x_v_float, 0.1, 1);


            x_float = x_float + x_v_float;
            y_float = y_float + y_v_float;

            x = (int)x_float;

            y = (int)y_float;
    
    
    break;

    };


};


void animation_requests::render_animation() {

    modifier();
	int random = 0;


    switch (update_position_case) {

        case (1):{

            render_requests * obj = new render_requests(sprite_nr, x, y, 1);

            render_req.push_back(*obj);
            delete obj;


        break;
        }

        case (2): {

            if ( rotation == 1 && right_orientation == false ) {
                //x_offset = -1*(sprite_width -1);
                x_offset = 0;
            } else {
                x_offset = 0;
            };

            //cout << rotation << endl;
            render_requests * obj = new render_requests(sprite_nr, x+x_offset, y, 1, right_orientation, up_orientation, rotation);

            render_req.push_back(*obj);
            delete obj;


        break;
        }
        case (3): {

//                cout << animation_profiles.at(profile_nr).animate_type.size() << endl;
            for ( int i = 0; i < animation_profiles.at(profile_nr).animate_type.size() ; i++ ) {

                if ( current_cycle >= animation_profiles.at(profile_nr).animate_from_cycle.at(i) && current_cycle < animation_profiles.at(profile_nr).animate_to_cycle.at(i) ) {
                    //cout << animation_profiles.at(profile_nr).animate_main_nr.at(i) << endl;

                    if ( animation_profiles.at(profile_nr).animate_duo.at(i) == true ) {

                    render_requests_dual( animation_profiles.at(profile_nr).animate_main_nr.at(i), x, y, true, true, false );

                    } else {

                    }
                    if ( animation_profiles.at(profile_nr).animate_quad.at(i) == true ) {

                    render_requests_quad( animation_profiles.at(profile_nr).animate_main_nr.at(i), x, y, true, true, false);

                    } else {

                    }
                    if (animation_profiles.at(profile_nr).animate_quad.at(i) == false && animation_profiles.at(profile_nr).animate_duo.at(i) == false ) {
                    render_requests * obj = new render_requests(animation_profiles.at(profile_nr).animate_main_nr.at(i), x, y, 1, true, true, 1);
                    render_req.push_back(*obj);
                    delete obj;

                    } else {
                    }




                } else {
                }

            }

        break;
        }
        case (4): {
		
			random = (rand() % 10);
		
			render_primitive_line(x-5 - random, y + current_cycle, x+25 + random, y + current_cycle, 1, 401);
			
			render_primitive_line(x + current_cycle, y - random, x + current_cycle, y+25+random, 1, 401);

		
		break;	
		}
		case (5): {
		
//                cout << animation_profiles.at(profile_nr).animate_type.size() << endl;
            for ( int i = 0; i < animation_profiles.at(profile_nr).animate_type.size() ; i++ ) {

                if ( current_cycle >= animation_profiles.at(profile_nr).animate_from_cycle.at(i) && current_cycle < animation_profiles.at(profile_nr).animate_to_cycle.at(i) ) {
                    //cout << animation_profiles.at(profile_nr).animate_main_nr.at(i) << endl;

                    if ( animation_profiles.at(profile_nr).animate_duo.at(i) == true ) {

                    render_requests_dual( animation_profiles.at(profile_nr).animate_main_nr.at(i), x, y, true, true, false );

                    } else {

                    }
                    if ( animation_profiles.at(profile_nr).animate_quad.at(i) == true ) {

                    render_requests_quad( animation_profiles.at(profile_nr).animate_main_nr.at(i), x, y, true, true, false);

                    } else {

                    }
                    if (animation_profiles.at(profile_nr).animate_quad.at(i) == false && animation_profiles.at(profile_nr).animate_duo.at(i) == false ) {
                    render_requests * obj = new render_requests(animation_profiles.at(profile_nr).animate_main_nr.at(i), x, y, 1, true, true, 1);
                    render_req.push_back(*obj);
                    delete obj;

                    } else {
                    }




                } else {
                }

            }

		
		break;	
		}
		
		

        default:
        break;

    };


    current_cycle++;

    if ( current_cycle >= cycles ) {
        destroy = true;
    } else {
    }


};













