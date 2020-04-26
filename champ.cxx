
#include <iostream>
#include "champ.h"
#include <vector>
#include "soundmanager.h"
#include "setup_sprites.h"
#include "render.h"
#include "environment.h"
#include <cmath>
#include <assert.h>
#include <math.h>
#include "physics.h"
#include <cstdlib>
#include <algorithm>
using namespace std;

//champ::champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter) {
champ::champ(int a, int size, int Height, int Width) : runcycle(2,6,1,60) {

// Current sprite and palette
//sprite_current = 100; // sprite index, will need to connect to all_sprites
palette_current = 1;

//sprite_nr = Relation_Spritenr_type(); // translates the index/current/type to vector position in all_sprites

champ_area = 0.111;
x_velocity = 0;
y_velocity = 0;
x_max_speed = 3;
floor_contact = false;
internal_state = 7;
gun_direction = 3;
jump_counter = 1;
current_gun = 1;
//internal = &render_req;
//setContactPoints();
grab_left = false;
grab_right = false;
grab_lock = false;

jump_counter_set = 6;
jump_v = 3;
nr_of_jumps_set = 1;



};

void champ::upgrade_animation() {
	
	//~ void modifier_random( int &number, int maximum, int minimum );
	int x = rand() % 10 - rand() % 10 ;
	int y = rand() % 10 - rand() % 10 ;

	
	int type = 2;
	switch ( type ) {
	
		case(1):
		
			if ( ( rand() % 10 ) > 7 ) {
				
				animation_requests * obj = new animation_requests(14, x_location + width/2, y_location + height/2 , x, y);
				anime_req.push_back(*obj);
				delete obj;
				obj = 0;
			
			} else {
			};
		
		break;
		
		case(2):
		


			if ( ( rand() % 10 ) > 8 ) {
				
				animation_requests * obj = new animation_requests(&x_location, &y_location , 0, 0, true);
								
				if ( ( rand() % 10 ) > 7 ) {
					obj->front = false;
				} else {
				};
				
				
				anime_req.push_back(*obj);
				delete obj;
				obj = 0;

			} else {
			};
			
			upgrade_animation_counter++;
			if ( upgrade_animation_counter > 30 ) {
			
				upgrade_animation_trigger = false;
				upgrade_animation_counter = 0;
				
			} else {
			};
			
						
		break;
	
	
	
	};
	
	
	
};


void champ::check_items( int room ) {

	room_objects.at(room).update_hitbox();
	
	hero_hitbox.at(0).load_base( x_location, y_location );
	

	
	for ( int i = 0; i < room_objects.at(room).room_items.size(); i++ ) {
		
		//~ room_objects.at(room).room_items.at(i).update_hitbox();
		
			if ( room_objects.at(room).room_items.at(i).item_hitbox.at(0).hitbox_compare( hero_hitbox.at(0) ) == false && room_objects.at(room).room_items.at(i).active == true ) {
				

					hero_items.push_back( &room_objects.at(room).room_items.at(i) );
					upgrade_animation_trigger = true;

					room_objects.at(room).room_items.at(i).hit = true;
					
				

			} else {
			}; 
		

	};
	
	// drop items
	for ( int i = 0; i < room_objects.at(room).room_drop_items.size(); i++ ) {
		
		//~ room_objects.at(room).room_items.at(i).update_hitbox();
		
			if ( room_objects.at(room).room_drop_items.at(i).item_hitbox.at(0).hitbox_compare( hero_hitbox.at(0) ) == false ) {
				

					room_objects.at(room).room_drop_items.at(i).run_effect(this);
					//~ upgrade_animation_trigger = true;

					room_objects.at(room).room_drop_items.at(i).hit = true;
					room_objects.at(room).room_drop_items.at(i).destroy = true;
				
				

			} else {
			}; 
		

	};
	
	
	if ( upgrade_animation_trigger == true ) {
	
		upgrade_animation();	
	
	} else {
	};


	
	
};

void champ::run_items() {
	

	for ( int i = 0; i < hero_items.size(); i ++ ) {
	
		//~ cout << hero_items.size() << " " << hero_items.at(i)->nr << endl;
	
		hero_items.at(i)->run_effect(this);
		


	
	};
	

	

	
	
};




// May be obsolete after render state
int champ::Relation_Spritenr_type() {
    int return_value = 0;
    sprite_error = true;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == sprite_current ) {
                return_value = i;
                sprite_error = false;
                width = all_sprites.at(i).getWidth();
                height = all_sprites.at(i).getHeight();

            } else {

            };
        };

    return return_value;

};

int champ::Relation_Spritenr_type_dev(int parameter) {
    int return_value = 0;
    //sprite_error = true;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == parameter ) {
                return_value = i;
                //sprite_error = false;
                //width = all_sprites.at(i).getWidth();
                //height = all_sprites.at(i).getHeight();

            } else {

            };
        };
    sprite_error = false;
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

//int champ::blockCompare_y(int champ_x, int champ_y, int block_x, int block_y, int block_p3x, int block_p3y, int block_p4x, int block_p4y ) {
//
//int return_value;
//
//return_value = ( ( block_p4y - block_p3y ) / ( block_p4x - block_p3x ) ) * ( champ_x - block_x ) + block_p3y ;
//
//return return_value;
//
//}
double champ::Det(double a, double b, double c, double d)
{
	return a*d - b*c;
};

bool champ::LineLineIntersect(double x1, double y1, //Line 1 start
    double x2, double y2, //Line 1 end
    double x3, double y3, //Line 2 start
    double x4, double y4, //Line 2 end
    double &ixOut, double &iyOut) {

        //http://mathworld.wolfram.com/Line-LineIntersection.html

    double detL1 = Det(x1, y1, x2, y2);
    double detL2 = Det(x3, y3, x4, y4);
    double x1mx2 = x1 - x2;
    double x3mx4 = x3 - x4;
    double y1my2 = y1 - y2;
    double y3my4 = y3 - y4;

    double xnom = Det(detL1, x1mx2, detL2, x3mx4);
    double ynom = Det(detL1, y1my2, detL2, y3my4);
    double denom = Det(x1mx2, y1my2, x3mx4, y3my4);
    if(denom == 0.0)//Lines don't seem to cross
    {
        ixOut = NAN;
        iyOut = NAN;
        return false;
    }

    ixOut = xnom / denom;
    iyOut = ynom / denom;
    if(!isfinite(ixOut) || !isfinite(iyOut)) //Probably a numerical issue
        return false;

    return true; //All OK

};

void champ::render_life() {

	if ( hero_life > 0 ) {
	
		for ( int i = 0; i < hero_life; i++ ) {
		
			render_requests * obj = new render_requests(life_bar_nr, 105 + 2*i, 13, true);

			render_req.push_back(*obj);
			delete obj;
			
		};
	
	} else {
	};



};



void champ::setRender(button_input& parameter, physics &physics_parameter, int room)  {

// For mode 2
//int y_test = 0;

	render_life();

    switch (render_req_mode) {
    case 0:
        if (sprite_error == false) {
            render_requests * obj = new render_requests(sprite_nr, x_location, y_location, palette_current);

            render_req.push_back(*obj);
            delete obj;


        } else {
//        cout << "ok" << endl;
        };
    break;
    case 1:
        if (only_once == true) {



        } else {

        };
    break;
    case 2:

//        if ( (int)y_velocity != 0 ) {
//        y_test = y_velocity / abs(y_velocity);
//        } else {
//        }

destroy_counter = 0;
for ( int i = 0; i < RSV.size(); i++ ) {

//RSV.at(i).f_1 == floor_contact || RSV.at(i).f_2 == floor_contact && RSV.at(i).w_1 == general_contact || RSV.at(i).w_2 == general_contact && RSV.at(i).int_1 == internal_state || RSV.at(i).int_2 == internal_state || RSV.at(i).int_3 == internal_state || RSV.at(i).int_4 == internal_state
//RSV.at(i).f_1 == floor_contact || RSV.at(i).f_2 == floor_contact
//RSV.at(i).w_1 == general_contact || RSV.at(i).w_2 == general_contact
//RSV.at(i).int_1 == internal_state || RSV.at(i).int_2 == internal_state || RSV.at(i).int_3 == internal_state || RSV.at(i).int_4 == internal_state
//
    bool animate = true;
    bool fc = floor_contact;
    bool gc = general_contact; // maybe redundanty
    int in = internal_state;
    int g = gun_direction;
    bool r = roof_contact;
   
    int x_mirror = 0;
    int RSV_x, RSV_y;

    int rot;
    bool vertical;
    bool horisontal;

    int rand_v_x = 0;
    int rand_v_y = 0;

    if ( (RSV.at(i).w_1 == grab_lock || RSV.at(i).w_2 == grab_lock) && (RSV.at(i).f_1 == fc || RSV.at(i).f_2 == fc) && (RSV.at(i).gu_1 == g || RSV.at(i).gu_2 == g || RSV.at(i).gu_3 == g || RSV.at(i).gu_4 == g || RSV.at(i).gu_5 == g) && ( RSV.at(i).int_1 == in || RSV.at(i).int_2 == in || RSV.at(i).int_3 == in || RSV.at(i).int_4 == in || RSV.at(i).int_5 == in || RSV.at(i).int_6 == in || RSV.at(i).int_7 == in ) ) {
    vertical = current_sprite_v_direction;
    horisontal = current_sprite_direction;
    rot = 1;
    RSV_x = x_location+RSV.at(i).x_off;
    RSV_y = y_location+RSV.at(i).y_off;
                        // gun direction
                    if ( RSV.at(i).gu_1 == 1 && RSV.at(i).gu_2 == 1 && RSV.at(i).gu_3 == 1 && RSV.at(i).gu_4 == 1 && RSV.at(i).gu_5 == 1) {

                            if ( current_sprite_direction == true ) {
                                rot = 2;
                                horisontal = false;
                                RSV_y = RSV_y - 20;
                            } else {
                            }
                            if ( current_sprite_direction == false ) {
                                rot = 2;
                                horisontal = false;
                                vertical = false;
                                RSV_y = RSV_y - 20;
                            } else {
                            }

                    } else {
                    }
                    // gun down
                    if ( RSV.at(i).gu_1 == 5 && RSV.at(i).gu_2 == 5 && RSV.at(i).gu_3 == 5 && RSV.at(i).gu_4 == 5 && RSV.at(i).gu_5 == 5) {

                            if ( current_sprite_direction == true ) {
                                rot = 2;
                                horisontal = true;
                                vertical = false;
                                RSV_y = RSV_y + 1;
                            } else {
                            }
                            if ( current_sprite_direction == false ) {
                                rot = 2;
                                horisontal = true;
                                vertical = true;
                                RSV_y = RSV_y + 1;
                            } else {
                            }

                    } else {
                    }
                    // gun 45 down
                    if ( RSV.at(i).gu_1 == 4 && RSV.at(i).gu_2 == 4 && RSV.at(i).gu_3 == 4 && RSV.at(i).gu_4 == 4 && RSV.at(i).gu_5 == 4) {

                            if ( current_sprite_direction == true ) {
                                rot = 2;
                                horisontal = true;
                                vertical = false;
                                RSV_y = RSV_y + 0;
                            } else {
                            }
                            if ( current_sprite_direction == false ) {
                                rot = 2;
                                horisontal = true;
                                vertical = true;
                                RSV_y = RSV_y + 0;
                            } else {
                            }

                    } else {
                    }
                    // based on rotation the xoffset is set
                    if ( current_sprite_direction == false &&  RSV.at(i).x_off > 0) {
                        switch (rot){
                            case 1:
                            x_mirror = 2*(RSV.at(i).x_off - width/2) + all_sprites.at(RSV.at(i).sprite_nr).getWidth()-1;
                            break;
                            case 2:
                            x_mirror = 2*(RSV.at(i).x_off - width/2) + all_sprites.at(RSV.at(i).sprite_nr).getHeight()-1;

                            break;
                            default:
                            break;
                        };

                    } else {
                    }

                    // transmitt the RSV and mirror values to the later attack creation
                    //cout << " width half " << width/2 << endl;
                    if ( RSV.at(i).is_g == true ) {
                        x_mirror_gun = x_mirror;
                        RSV_x_gun = RSV_x-x_location;
                        RSV_y_gun = RSV_y-y_location;
                        horisontal_gun = horisontal;
                        vertical_gun = vertical;
                        rot_gun = rot;
                        gun_sprite_nr = RSV.at(i).sprite_nr;
                            if ( parameter.getShootState() == true && rot == 1 ) {
                                modifier_random(RSV_x, 2, 1);
                            } else {
                            };
                            if ( parameter.getShootState() == true && rot == 2 ) {
                                modifier_random(RSV_y, 2, 1);
                            } else {
                            };


                    }else {
                    }

                    // Setup the destroy sequence
                    if ( hero_life <= 0 && only_once == true ) {
							

							x_destroy_pos_float.push_back(  (float)RSV_x );
							y_destroy_pos_float.push_back(  (float)RSV_y );

                            destroy_animation.push_back(true);
                            destroy_animation_extra.push_back(true);

                            x_destroy_v_float.push_back( modifier_random_float(0.00, 10, true) );
                            y_destroy_v_float.push_back( modifier_random_float(0.00, 15, false) );

							if ( RSV.at(i).Advanced == false ) {
							
								animation_requests * obj_ex = new animation_requests(12, RSV_x - x_mirror + all_sprites.at(RSV.at(i).sprite_nr).getWidth()/2,
								RSV_y + all_sprites.at(RSV.at(i).sprite_nr).getHeight()/2 , 0, 0);
								anime_req.push_back(*obj_ex);
								delete obj_ex;


								particle_generator(RSV_x - x_mirror + all_sprites.at(RSV.at(i).sprite_nr).getWidth()/2,
								RSV_y + all_sprites.at(RSV.at(i).sprite_nr).getHeight()/2, 0, 5, true, 30, 20 );

								for (int ii = 0; ii < 3; ii++) {
									particle_generator(RSV_x - x_mirror + all_sprites.at(RSV.at(i).sprite_nr).getWidth()/2,
									RSV_y + all_sprites.at(RSV.at(i).sprite_nr).getHeight()/2, false ,4, true, 30, 20 );
								};
							
							} else {
							};




                    } else {
                    }


                    if ( hero_life <= 0 && only_once == false  ) {

                        int test = (rand() % 100);
                        if (  test > 98 ) {
                            destroy_animation.at(0 + destroy_counter ) = false;

                                if ( destroy_animation_extra.at( 0 + destroy_counter ) == true ) {

                                        animation_requests * obj_e = new animation_requests(12, (int)x_destroy_pos_float.at( 0 + destroy_counter ) + all_sprites.at(RSV.at(i).sprite_nr).getWidth()/2,
                                        (int)y_destroy_pos_float.at( 0 + destroy_counter ) + all_sprites.at(RSV.at(i).sprite_nr).getHeight()/2 , 0, 0);
                                        anime_req.push_back(*obj_e);
                                        delete obj_e;

                                            for (int ii = 0; ii < 4; ii++) {
                                                particle_generator((int)x_destroy_pos_float.at( 0 + destroy_counter ) + all_sprites.at(RSV.at(i).sprite_nr).getWidth()/2,
                                                (int)y_destroy_pos_float.at( 0 + destroy_counter ) + all_sprites.at(RSV.at(i).sprite_nr).getHeight()/2, 0 ,5, true, 30, 20 );

                                                particle_generator((int)x_destroy_pos_float.at( 0 + destroy_counter ) + all_sprites.at(RSV.at(i).sprite_nr).getWidth()/2,
                                                (int)y_destroy_pos_float.at( 0 + destroy_counter ) + all_sprites.at(RSV.at(i).sprite_nr).getHeight()/2, 0, 4, true, 30, 20 );
                                            };



                                        destroy_animation_extra.at( 0 + destroy_counter ) = false;
                                } else {
                                }

                        } else {
                        }



                        physics_parameter.calculate_velocity(y_destroy_v_float.at(0 + destroy_counter), x_destroy_v_float.at(0 + destroy_counter),0.5, 1.00 );

                        float x_pos = x_destroy_pos_float.at( 0 + destroy_counter ) ;
                        float y_pos = y_destroy_pos_float.at( 0 + destroy_counter ) + (float)all_sprites.at(RSV.at(i).sprite_nr).getHeight();


                        roomblocks_simple_deflection( room, x_pos, y_pos,
                        x_destroy_v_float.at(0 + destroy_counter), y_destroy_v_float.at(0 + destroy_counter)   );

                        x_destroy_pos_float.at( 0 + destroy_counter ) = x_destroy_pos_float.at( 0 + destroy_counter ) - x_destroy_v_float.at(0 + destroy_counter);
                        y_destroy_pos_float.at( 0 + destroy_counter ) = y_destroy_pos_float.at( 0 + destroy_counter ) + y_destroy_v_float.at(0 + destroy_counter);


                       RSV_x = (int)x_destroy_pos_float.at( 0 + destroy_counter )  ;
                       RSV_y = (int)y_destroy_pos_float.at( 0 + destroy_counter )  ;
                       //cout << x_destroy_pos.at( 0 + destroy_counter ) << endl;

                    if ( destroy_animation.at(0 + destroy_counter) == false ) {
                        animate = false;

                    } else {
                    }
                    destroy_counter++;

                    } else {
                    }


					// Grab settings
					if ( RSV.at(i).grab == true ) {
						
						if ( grab_right == true ) {
							horisontal = true;
							x_mirror = 0;
						} else {
						}
						if ( grab_left == true ) {
							horisontal = false;
							x_mirror = 2*(RSV.at(i).x_off - width/2) + all_sprites.at(RSV.at(i).sprite_nr).getWidth()-1;
						} else {
						}
						
					} else {
					};



                    if ( animate == true && RSV.at(i).static_ == false ) {
                        render_requests * obj = new render_requests(RSV.at(i).sprite_nr, RSV_x-x_mirror, RSV_y, palette_current,horisontal, vertical, rot);
                        render_req.push_back(*obj);
                        delete obj;

                    } else {
                    }
                    if ( animate == true && RSV.at(i).static_ == true ) {
                        render_requests * obj = new render_requests(RSV.at(i).sprite_nr, RSV.at(i).x_off , RSV.at(i).y_off, true);
                        render_req.push_back(*obj);
                        delete obj;

                    } else {
                    }





    };


}

if ( hero_life <= 0 && only_once == true ) {
    only_once = false;
} else {
}

    break;
    default:
    break;



    };






};


void champ::setContactPoints() {
float floater;

// Setup of new contact points array


// Below is from other data source
floater = (float)width * 1/2;
contact_points_all[0][0] = (int)floater;
contact_points_all[1][0] = height;

floater = (float)width * 1/2;
contact_points_all[0][1] = (int)floater;
contact_points_all[1][1] = 0;

contact_points_all[0][2] = width;
contact_points_all[1][2] = 0;

floater = (float)height * 1/4;
contact_points_all[0][3] = width;
contact_points_all[1][3] = (int)floater;

floater = (float)height * 2/4;
contact_points_all[0][4] = width;
contact_points_all[1][4] = (int)floater;

floater = (float)height * 3/4;
contact_points_all[0][5] = width;
contact_points_all[1][5] = (int)floater;

floater = (float)height * 4/4;
contact_points_all[0][6] = width;
contact_points_all[1][6] = (int)floater;

contact_points_all[0][7] = 0;
contact_points_all[1][7] = 0;

floater = (float)height * 1/4;
contact_points_all[0][8] = 0;
contact_points_all[1][8] = (int)floater;

floater = (float)height * 2/4;
contact_points_all[0][9] = 0;
contact_points_all[1][9] = (int)floater;

floater = (float)height * 3/4;
contact_points_all[0][10] = 0;
contact_points_all[1][10] = (int)floater;

contact_points_all[0][11] = 0;
contact_points_all[1][11] = height;

//cout << contact_points_all[1][3] << endl;


hitbox_object * obj_h = new hitbox_object(0,0, width, height );
hero_hitbox.push_back( *obj_h );
delete obj_h;
obj_h = 0;



};

void champ::setContact(int room) {

general_contact = false;
floor_contact = false;
roof_contact = false;
contact_left = false;
contact_right = false;
contact_roof = false;

if (grab_lock == false) {
	grab_right = false;
	grab_left = false;
} else {
}


for ( int i = 0; i < room_objects.at(room).roomblocks.size() ; i++ ) {

        int P3_x = room_objects.at(room).roomblocks.at(i).contact_points[0][2] + room_objects.at(room).roomblocks.at(i).x_location;
        int P3_y = room_objects.at(room).roomblocks.at(i).contact_points[1][2] + room_objects.at(room).roomblocks.at(i).y_location;

        int P4_x = room_objects.at(room).roomblocks.at(i).contact_points[0][1] + room_objects.at(room).roomblocks.at(i).x_location;
        int P4_y = room_objects.at(room).roomblocks.at(i).contact_points[1][1] + room_objects.at(room).roomblocks.at(i).y_location;

        int P1_x = contact_points_all[0][11]  + getX(); // x
        int P1_y = contact_points_all[1][11]  + getY(); // y

        int P2_x = contact_points_all[0][2]  + getX(); // x
        int P2_y = contact_points_all[1][2]  + getY(); // y

// Below is first hitbox check within larger condition check


        if ( abs(P1_x) - abs(P1_x) < 200 && abs(P1_x) - abs(P1_x) < 200  ) {

            if ( P2_y <= P3_y && P1_y >= P4_y && P2_x >= P3_x && P1_x <= P4_x ) {

                contact_position.push_back(i);
            }


        } else {
        }

}

///////////////////////////////////////////////////////////////
            // perform a check for each point in contact list


// prototype replacement below
 for ( int i = 0; i < contact_position.size();i++ ){
        int j = contact_position.at(i);

        int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
        int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

        int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
        int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

}


            for (int k = 0; k < 13; k++){
                switch (k) {
                    case 0:
                    // Floor
                    for ( int i = 0; i < contact_position.size();i++ ){
                    int j = contact_position.at(i);

                    int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                    int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                    int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                    int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

                        if ( contact_points_all[1][0]  + getY() >= P4_y && contact_points_all[1][0]  + getY() < P3_y && contact_points_all[0][0] + getX() >= P3_x && contact_points_all[0][0] + getX() <= P4_x ) {
                        //cout << " floor " << endl;
                        floor_contact = true;
                       

                        //jump_counter = 1;
                        jump_counter = jump_counter_set;
                        nr_of_jumps = nr_of_jumps_set;

                        y_vel = 0;
                        
                            while ( contact_points_all[1][0]  + getY() >= P4_y ){
                            setY( getY() -1 );
                            }
                            //cout << y_location+height << "  " << P4_y << endl;
                            room_objects.at(room).roomblocks.at(j).convey_v(this);

                        } else {
                        }


                    }


                    break;
                    case 1:
                    // Roof
                         for ( int i = 0; i < contact_position.size();i++ ){
                                int j = contact_position.at(i);

                                int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                                int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                                int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                                int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

                                if ( contact_points_all[1][1]  + getY() >= P4_y && contact_points_all[1][1]  + getY() < P3_y && contact_points_all[0][1] + getX() >= P3_x && contact_points_all[0][1] + getX() <= P4_x ) {
                                roof_contact = true;

                                y_vel = 0;
                                //cout << "top" << endl;
                                    while ( contact_points_all[1][1]  + getY() < P3_y ){
                                    setY( getY() +1 );
                                    }
                                } else {
                                }
                        }

                    break;
                    case 2:
                    // Right Side top
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

                                if ( contact_points_all[1][2]  + getY() >= P4_y && contact_points_all[1][2]  + getY() <= P3_y && contact_points_all[0][2] + getX() >= P3_x && contact_points_all[0][2] + getX() <= P4_x ) {
								
									if ( current_sprite_direction == true ) {
										grab_right = true;
										grab_block_nr = j;
										
									} else {
									}
								
                                // champ pos
                                float x_1 = x_location + width ;
                                float y_1 = y_location ;
                                float x_2 = x_location_prev + width ;
                                float y_2 = y_location_prev ;

//                                float x_1 = 5 ;
//                                float y_1 = 5 ;
//                                float x_2 = 10 ;
//                                float y_2 = 10 ;
                                length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
                                //cout << "L_" << length << endl;

                                x_location_intersection = x_1;
                                y_location_intersection = y_1;

                                x_location_intersection_int = (int)x_1 ;
                                y_location_intersection_int = (int)y_1 ;

                                delta_x;
                                delta_y;
                                increment = 0;
                                delta_increment = 0.1;


                                cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                a_cos = acos( cos_alfa );

                                // correction of angle due to horizontal line
                                if (y_2 < y_1) {
                                    a_cos = a_cos + M_PI;
                                } else {
                                }

                                //float sin_length = length * sin( a_cos ) ;
                                //float cos_length = length * cos( a_cos ) ;
                                //cout << " sin of length " << sin_length << endl;
                                //cout << " cos of length " << cos_length << endl;


                                //cout << "alfa_" << a_cos*(180/M_PI) << endl;

                                    while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                            increment = increment + delta_increment;

                                                delta_x = ( length - increment ) * cos( a_cos );
                                                delta_y = ( length - increment ) * sin( a_cos );
                                                //cout << delta_x <<endl;

                                                    if (delta_x < 0) {
                                                    //delta_x = 0;
                                                    } else {
                                                    }
                                                    if (delta_y < 0) {
                                                    delta_y = 0;
                                                    } else {
                                                    }

                                                //cout << length << endl;
                                                x_location_intersection = x_location_intersection - (( x_1 - x_2 ) + delta_x) ;
                                                y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);
                                                //cout << ( x_1 - x_2 ) << " - " << delta_x <<endl;
												
                                                x_location_intersection_int = (int)x_location_intersection;
                                                y_location_intersection_int = (int)y_location_intersection;
													
                                    }

                                    /////////////////
                                    

                                if (x_location_intersection_int <= P3_x && y_location_intersection_int < P3_y ) {
                                    x_location_intersection_int = P3_x-1;
                                    contact_right = true;
                                    x_velocity = 0;
                                    y_location_intersection_int = (int)y_1 ;
                                    cout << "A" << endl;
                                } else {
                                }
                                if( y_location_intersection_int >= P3_y && x_location_intersection_int > P3_x ){
                                    y_location_intersection_int = P3_y+1;
                                    roof_contact = true;
                                    cout << "B" << endl;
                                } else {
                                }

                                x_location = x_location_intersection_int - width;
                                y_location = y_location_intersection_int;
                                //cout << x_1 << " " << y_1 << " Prev " << x_2 << " " << y_2 << " " << x_location+width << " " << y_location << " " << P3_x << " " << P3_y <<endl;



                                } else {
                                }
                    }

                    break;
                    case 3:
                    // Right Side 1/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][3]  + getY() >= P4_y && contact_points_all[1][3]  + getY() < P3_y && contact_points_all[0][3] + getX() >= P3_x && contact_points_all[0][3] + getX() <= P4_x ) {
                            //x_velocity = 0;
                            contact_right = true;
                            //cout << "Z" << endl;
                                while ( contact_points_all[0][3]  + getX() >= P3_x ){

                                setX( getX() -1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 4:
                    // Right Side 2/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][4]  + getY() >= P4_y && contact_points_all[1][4]  + getY() < P3_y && contact_points_all[0][4] + getX() >= P3_x && contact_points_all[0][4] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_right = true;
                                while ( contact_points_all[0][4]  + getX() >= P3_x ){

                                setX( getX() -1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 5:
                     //Right Side 3/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][5]  + getY() >= P4_y && contact_points_all[1][5]  + getY() < P3_y && contact_points_all[0][5] + getX() >= P3_x && contact_points_all[0][5] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_right = true;
                                while ( contact_points_all[0][5]  + getX() >= P3_x ){

                                setX( getX() -1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 6:
                    // Right Side 4/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                                if ( contact_points_all[1][6]  + getY() >= P4_y && contact_points_all[1][6]  + getY() <= P3_y && contact_points_all[0][6] + getX() >= P3_x && contact_points_all[0][6] + getX() <= P4_x ) {
                                    // champ pos
                                    float x_1 = x_location + width ;
                                    float y_1 = y_location + height;
                                    float x_2 = x_location_prev + width ;
                                    float y_2 = y_location_prev + height;

                                    length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
                                    //cout << "L_" << length << endl;

                                    x_location_intersection = x_1;
                                    y_location_intersection = y_1;

                                    x_location_intersection_int = (int)x_1 ;
                                    y_location_intersection_int = (int)y_1 ;

                                    delta_x;
                                    delta_y;
                                    increment = 0;
                                    delta_increment = 0.1;


                                    cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                    a_cos = acos( cos_alfa );

                                    // correction of angle due to horizontal line
                                        if (y_2 < y_1) {
                                            a_cos = a_cos + M_PI;
                                        } else {
                                        }

                                    //float sin_length = length * sin( a_cos ) ;
                                    //float cos_length = length * cos( a_cos ) ;
                                    //cout << " sin of length " << sin_length << endl;
                                    //cout << " cos of length " << cos_length << endl;


                                    //cout << "alfa_" << a_cos*(180/M_PI) << endl;
										
                                        while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                                    increment = increment + delta_increment;

                                                    delta_x = ( length - increment ) * cos( a_cos );
                                                    delta_y = ( length - increment ) * sin( a_cos );
                                                    //cout << delta_x << " _ " << delta_y <<endl;

                                                        if (delta_x < 0) {
                                                        //delta_x = 0;
                                                        } else {
                                                        }
                                                        if (delta_y < 0) {
                                                        delta_y = 0;
                                                        } else {
                                                        }

                                                    //cout << length << " _ " << delta_x << endl;

                                                    x_location_intersection = x_location_intersection - (( x_1 - x_2 ) - delta_x) ;
                                                    y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);
                                                    //cout << ( x_1 - x_2 ) << " - " << delta_x <<endl;

                                                    x_location_intersection_int = (int)x_location_intersection;
                                                    y_location_intersection_int = (int)y_location_intersection;

                                                    //cout << "x_1 " << x_1 << " length-increment" << x_location_intersection << " x_int_" <<x_location_intersection_int << "P3_x" << P3_x << endl;

                                        }

                                        /////////////////

                                        if (x_location_intersection_int <= P3_x && y_location_intersection_int > P4_y) {
                                            //cout << " XR " << endl;
                                            x_location_intersection_int = P3_x-1;
                                            contact_right = true;
                                        } else {
                                        }
                                        if( y_location_intersection_int <= P4_y ){
                                            //cout << " YR " << endl;
                                            y_location_intersection_int = P4_y-1;
                                            x_location_intersection_int = x_location + width;

                                            //roof_contact = true;
                                            floor_contact = true;

                                            y_vel = 0;
                                            //jump_counter = 1;
                                            jump_counter = jump_counter_set;
                                            nr_of_jumps = nr_of_jumps_set;
                                        } else {
                                        }

                                    //cout << " LR1 " <<  x_location_intersection_int << endl;
                                    if (floor_contact == true && y_location_intersection_int < P3_y) {
                                        //x_location_intersection_int = x_location + width;
                                        //cout << y_location_intersection_int << " _ " << P3_y << endl;
                                    } else {
                                    }
                                    //cout << " LR2 " <<  x_location_intersection_int << endl;
                                    x_location = x_location_intersection_int - width;
                                    y_location = y_location_intersection_int - height;
                                    //cout << x_1 << " " << y_1 << " Prev " << x_2 << " " << y_2 << " " << x_location+width << " " << y_location+height << " " << P3_x << " " << P4_y <<endl;

									room_objects.at(room).roomblocks.at(j).convey_v(this);


                                }
                    }
                    break;
                    case 7:
                    // Left Side 0/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;

                                    //cout << P4_x << "_" << getX() << endl;
                                    if ( contact_points_all[1][7]  + getY() >= P4_y && contact_points_all[1][7]  + getY() <= P3_y && contact_points_all[0][7] + getX() >= P3_x && contact_points_all[0][7] + getX() <= P4_x ) {
                                    grab_left = true;
                                    grab_block_nr = j;
                                    
                                    //champ pos
                                    float x_1 = x_location ;
                                    float y_1 = y_location ;
                                    float x_2 = x_location_prev ;
                                    float y_2 = y_location_prev ;

                                    length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
                                    //cout << "L_" << length << endl;

                                    x_location_intersection = x_1;
                                    y_location_intersection = y_1;

                                    x_location_intersection_int = (int)x_1 ;
                                    y_location_intersection_int = (int)y_1 ;

                                    delta_x;
                                    delta_y;
                                    increment = 0;
                                    delta_increment = 0.1;


                                    cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                    a_cos = acos( cos_alfa );

                                     //correction of angle due to horizontal line
                                        if (y_2 < y_1) {
                                            a_cos = a_cos + M_PI;
                                        } else {
                                        }

                                        while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                                    increment = increment + delta_increment;

                                                    delta_x = ( length - increment ) * cos( a_cos );
                                                    delta_y = ( length - increment ) * sin( a_cos );
                                                    //cout << delta_x <<endl;

                                                        if (delta_x < 0) {
                                                        //delta_x = 0;
                                                        } else {
                                                        }
                                                        if (delta_y < 0) {
                                                        //delta_y = 0;
                                                        } else {
                                                        }

                                                    //cout << length << endl;
                                                    x_location_intersection = x_location_intersection - (( x_1 - x_2 ) + delta_x) ;
                                                    y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);


                                                    x_location_intersection_int = (int)x_location_intersection;
                                                    y_location_intersection_int = (int)y_location_intersection;

                                                    //cout << "x_1 " << x_1 << " length-increment" << x_location_intersection << " x_int_" <<x_location_intersection_int << "P3_x" << P3_x << endl;

                                        }

                                        ///////////////
                                        //~ There is a bug here.. prev 2020 03 26 code was x_location_intersection_int >= P4_x
                                        
										cout << P4_x << " " <<  P3_y << endl;
                                        if (x_location_intersection_int <= P4_x && y_location_intersection_int < P3_y ) {

                                            x_location_intersection_int = P4_x+1;
                                            contact_left = true;
                                            y_location_intersection_int = (int)y_1 ;
                                            x_velocity = 0;
                                            //~ cout << "A" << endl;
                                        } else {
                                        }
                                        if( y_location_intersection_int >= P3_y && x_location_intersection_int < P4_x){

                                            y_location_intersection_int = P3_y+1;
                                            roof_contact = true;
                                            //~ cout << "B" << endl;
                                        } else {
                                        }

                                    x_location = x_location_intersection_int;
                                    y_location = y_location_intersection_int;
                                    //~ cout << " x " << x_location << " y " << y_location << " P3X " << P3_x << endl;
                                } else {
                                }
                    }



                    break;
                    case 8:
                    // Left Side 1/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][8]  + getY() >= P4_y && contact_points_all[1][8]  + getY() < P3_y && contact_points_all[0][8] + getX() >= P3_x && contact_points_all[0][8] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_left = true;
                                while ( contact_points_all[0][8]  + getX() <= P4_x ){

                                setX( getX() +1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 9:
                    // Left Side 2/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][9]  + getY() >= P4_y && contact_points_all[1][9]  + getY() < P3_y && contact_points_all[0][9] + getX() >= P3_x && contact_points_all[0][9] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_left = true;
                                while ( contact_points_all[0][9]  + getX() <= P4_x ){

                                setX( getX() +1 );
                                }
                            } else {
                            }
                    }

                    break;
                    case 10:
                    // Left Side 3/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][10]  + getY() >= P4_y && contact_points_all[1][10]  + getY() < P3_y && contact_points_all[0][10] + getX() >= P3_x && contact_points_all[0][10] + getX() <= P4_x ) {
                            x_velocity = 0;
                            contact_left = true;
                            cout << "C" << endl;
                                while ( contact_points_all[0][10]  + getX() <= P4_x ){

                                setX( getX() +1 ); //
                                }
                            } else {
                            }
                    }

                    break;
                    case 11:
                    // Left Side 4/4
                     for ( int i = 0; i < contact_position.size();i++ ){
                            int j = contact_position.at(i);

                            int P3_x = room_objects.at(room).roomblocks.at(j).contact_points[0][2] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P3_y = room_objects.at(room).roomblocks.at(j).contact_points[1][2] + room_objects.at(room).roomblocks.at(j).y_location;

                            int P4_x = room_objects.at(room).roomblocks.at(j).contact_points[0][1] + room_objects.at(room).roomblocks.at(j).x_location;
                            int P4_y = room_objects.at(room).roomblocks.at(j).contact_points[1][1] + room_objects.at(room).roomblocks.at(j).y_location;
                            if ( contact_points_all[1][11]  + getY() >= P4_y && contact_points_all[1][11]  + getY() <= P3_y && contact_points_all[0][11] + getX() >= P3_x && contact_points_all[0][11] + getX() <= P4_x ) {
                                    // champ pos
                                    float x_1 = x_location ;
                                    float y_1 = y_location + height;
                                    float x_2 = x_location_prev ;
                                    float y_2 = y_location_prev + height;
                                    //cout << "XYXY" << x_1 << " " << x_2 << " " << y_1 << " " << y_2 << endl;
                                    length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;

                                    x_location_intersection = x_1;
                                    y_location_intersection = y_1;

                                    x_location_intersection_int = (int)x_1 ;
                                    y_location_intersection_int = (int)y_1 ;

                                    delta_x;
                                    delta_y;
                                    increment = 0;
                                    delta_increment = 0.1;


                                    cos_alfa = (  ( x_2 - x_1 )/( length )  );
                                    a_cos = acos( cos_alfa );

                                    // correction of angle due to horizontal line
                                        if (y_2 < y_1) {
                                            a_cos = a_cos + M_PI;
                                        } else {
                                        }

										
                                        while ( y_location_intersection_int >= P4_y && y_location_intersection_int <= P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ) {
                                                    increment = increment + delta_increment;

                                                    delta_x = ( length - increment ) * cos( a_cos );
                                                    delta_y = ( length - increment ) * sin( a_cos );


                                                        if (delta_x < 0) {
                                                        //delta_x = 0;
                                                        } else {
                                                        }
                                                        if (delta_y < 0) {
                                                        //delta_y = 0;
                                                        } else {
                                                        }

                                                    //cout << length << " _ " << delta_x << endl;
                                                    x_location_intersection = x_location_intersection - (( x_1 - x_2 ) - delta_x) ;
                                                    y_location_intersection = y_location_intersection + ((y_2 - y_1) - delta_y);
                                                    //cout << ( x_1 - x_2 ) << " LL " << delta_x <<endl;

                                                    x_location_intersection_int = (int)x_location_intersection;
                                                    y_location_intersection_int = (int)y_location_intersection;

                                                    //cout << "x_1 " << x_1 << " length-increment" << x_location_intersection << " x_int_" <<x_location_intersection_int << "P3_x" << P3_x << endl;

                                        }

                                        /////////////////
                                        //cout << " cont left before_ " << x_location_intersection_int <<endl;
                                        if (x_location_intersection_int >= P4_x && y_location_intersection_int > P4_y) {

                                            x_location_intersection_int = P4_x+1;
                                            contact_left = true;
                                            x_velocity = 0;

                                        } else {
                                        }
                                        if( y_location_intersection_int <= P4_y ){

                                            y_location_intersection_int = P4_y-1;
                                            //roof_contact = true;
                                            x_location_intersection_int = x_location;
                                            floor_contact = true;

                                            y_vel = 0;
                                            //jump_counter = 1;
                                            jump_counter = jump_counter_set;
                                            nr_of_jumps = nr_of_jumps_set;

                                        } else {
                                        }

                                    //cout << " LL2 " << x_location_intersection_int <<endl;
                                    x_location = x_location_intersection_int ;
                                    y_location = y_location_intersection_int - height;
                                    //cout << x_1 << " " << y_1 << " Prev " << x_2 << " " << y_2 << " " << x_location+width << " " << y_location+height << " " << P3_x << " " << P4_y <<endl;

									room_objects.at(room).roomblocks.at(j).convey_v(this);

	

                            } else {
                            }
                    }
                    // L Side 4/4

                    break;
                    case 12:
                    break;

                    default:
                    break;

                }

            }






contact_position.clear();
//End
};



void champ::setPos(button_input& parameter, physics& physics_parameter){

    // update the invulnerable counter
    if ( hero_invincible_counter > 0 ) {
        hero_invincible_counter--;
    } else {
    }


    if (floor_contact == true) {
        y_vel = y_vel + physics_parameter.new_g;
    };
    if (roof_contact == true) {

        y_vel = 0;
    };
    if (contact_right == true) {
        x_velocity = 0;
    };
    if (contact_left == true) {
        x_velocity = 0;
    };

    if ( parameter.getLeftState() == true ) {
        current_sprite_direction = false;
    };
    if ( parameter.getRightState() == true ) {
        current_sprite_direction = true;
    };


    // set gun direction prototype
    gun_direction = 3;
    if ( parameter.getUpState() == true ) {
        gun_direction = 1;
    } else {
    }
    if ( parameter.getDownState() == true ) {
        gun_direction = 5;
    } else {
    }
    if ( (parameter.getUpState() == true && parameter.getRightState() == true) || (parameter.getUpState() == true && parameter.getLeftState()== true) ) {
        gun_direction = 2;
    } else {
    }
    if ( (parameter.getDownState() == true && parameter.getRightState() == true) || (parameter.getDownState() == true && parameter.getLeftState()== true) ) {
        gun_direction = 4;
    } else {
    }

    x_location_prev = x_location;
    y_location_prev = y_location;



    setX( getX() + (int)x_velocity );
    setY( getY() + (int)y_vel );

    //cout << x_location << "_" << x_location_prev << endl;

    x_center = (float)x_location + (float)width;
    y_center = (float)y_location + (float)height;

};


void champ::updateV(button_input& parameter, physics& physics_parameter, int room){

//cout << internal_state << endl;


    switch (physics_parameter.state) {
        case 0:
            if ( parameter.getLeftState() == true) {

                    x_velocity--;
                    //x_velocity--;
                    internal_state = runcycle.run();
            } else {
                    internal_state = runcycle.idle( internal_state );
            }

            if ( parameter.getRightState() == true) {
                    //setX( getX() + 3 );
                    x_velocity++;
                    //x_velocity++;
                    internal_state = runcycle.run();
            } else {
                   internal_state = runcycle.idle( internal_state );
            }
            // y axis

            
			physics_parameter.calculate_velocity( y_vel , x_velocity, champ_area, 4.00);
						
			// will try the grab thing here
			//~ cout << floor_contact << endl;
			if ( grab_right == true && parameter.getRightState() == true && y_vel > 1.00 && grab_lock == false && floor_contact == false) {
				grab_lock = true;
				room_objects.at(room).roomblocks.at( grab_block_nr ).grabbed = true;
				//jump_counter++;
				jump_counter = jump_counter_set;
				nr_of_jumps = nr_of_jumps_set;
				
			} else {

			};
			if ( grab_left == true && parameter.getLeftState() == true && y_vel > 1.00 && grab_lock == false && floor_contact == false) {
				grab_lock = true;
				room_objects.at(room).roomblocks.at( grab_block_nr ).grabbed = true;
				//jump_counter++;
				jump_counter = jump_counter_set;
				nr_of_jumps = nr_of_jumps_set;
				
			} else {

			};
			
			if ( grab_lock == true ) { 
				y_vel = 0;
				x_velocity = 0;
				
				room_objects.at(room).roomblocks.at(grab_block_nr).convey_v(this);
				
				if ( parameter.getLeftState() == true ) {
					current_sprite_direction = false;
				} else {
				};
				if ( parameter.getRightState() == true ) {
					current_sprite_direction = true;
				} else {
				};
				
			} else {

			};
			

			// jumpstuff


			
            if (parameter.getJumpState() == true && jump_counter >= 0 && nr_of_jumps > 0) { ///
                jump_counter--;
                //~ if (jump_counter == 0) {
					//~ nr_of_jumps--;
					
					//~ if ( nr_of_jumps > 0 ) {
						//~ jump_counter = jump_counter_set;
					//~ } else {
					//~ }
					
				//~ } else{
				//~ }
                

                //y_vel = y_vel -10;
                y_vel = y_vel - jump_v;
                floor_contact = false;
                
                // if grab is true
                if ( grab_right == true && grab_lock == true) {
					x_velocity = x_velocity - 5;
					grab_lock = false; 
					grab_right = false;
					room_objects.at(room).roomblocks.at( grab_block_nr ).grabbed = false;
				} else {
				};
				if ( grab_left == true && grab_lock == true ) {
					x_velocity = x_velocity + 5;
					grab_lock = false; 
					grab_left = false;
					room_objects.at(room).roomblocks.at( grab_block_nr ).grabbed = false;
				} else {
				};

            }
            
            // decrease jumpnr
            if ( parameter.getJumpstate_justreleased() == true && floor_contact == false && grab_lock == false ) {
				nr_of_jumps--;
					if ( nr_of_jumps > 0 ) {
						jump_counter = jump_counter_set;
					} else {
					}
			} else {
			}; 
            

            // Dev
            if ( parameter.getUpState() == true ) {
                y_vel--;
                y_vel--;
                y_vel--;
            } else {
            }



        break;

        default:
//            if ( parameter.getLeftState() == true ) {
//                    setX( getX() - 3 );
//            } else {
//            }
//
//            if ( parameter.getRightState() == true ) {
//                    setX( getX() + 3 );
//            } else {
//            }
//
//            if ( parameter.getUpState() == true ) {
//                    setY( getY() - 3 );
//            } else {
//            }
//
//            if ( parameter.getDownState() == true ) {
//                    setY( getY() + 3 );
//            } else {
//            }
        break;

    };

    if (x_velocity > x_max_speed) {
        //x_velocity = x_max_speed;
    } else {
    }
    if (x_velocity < -x_max_speed) {
        //x_velocity = -x_max_speed;
    } else {
    }

    //x_velocity = x_velocity * 0.9;



    if( y_velocity > physics_parameter.g ) {
           // y_velocity = physics_parameter.g;
    } else {
    }


};

void champ_setup(champ &parameter) {
    // render_requests * obj = new render_requests(sprite_nr, x_location, y_location, current_palette);
    // upper body 
    render_state * state_1_1 = new render_state(true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 101 );
    parameter.RSV.push_back(*state_1_1);
    delete state_1_1;

    // lower body, and run cycle
    render_state * state_1_2 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 7, 7, 7, 7, 7, 7, 7, 0, 12, 102 );
    parameter.RSV.push_back(*state_1_2);
    delete state_1_2;
    // 1
    render_state * state_1_2_1 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 0, 12, 111 );
    parameter.RSV.push_back(*state_1_2_1);
    delete state_1_2_1;
    // 2
    render_state * state_1_2_2 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 2, 2, 2, 2, 2, 2, 2, 0, 12, 112 );
    parameter.RSV.push_back(*state_1_2_2);
    delete state_1_2_2;
    // 3
    render_state * state_1_2_3 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 3, 3, 3, 3, 3, 3, 3, 0, 12, 113 );
    parameter.RSV.push_back(*state_1_2_3);
    delete state_1_2_3;
    // 4
    render_state * state_1_2_4 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 4, 4, 4, 4, 4, 4, 4, 0, 12, 114 );
    parameter.RSV.push_back(*state_1_2_4);
    delete state_1_2_4;
    // 5
    render_state * state_1_2_5 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 0, 12, 115 );
    parameter.RSV.push_back(*state_1_2_5);
    delete state_1_2_5;
    // 6
    render_state * state_1_2_6 = new render_state(true, true, true, false, true, false, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 0, 12, 116 );
    parameter.RSV.push_back(*state_1_2_6);
    delete state_1_2_6;


    ////////////////////////////////////
    // Jump
    render_state * state_1_3 = new render_state(false, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 12, 103 );
    parameter.RSV.push_back(*state_1_3);
    delete state_1_3;

    //gun
    render_state * state_1_4 = new render_state(true,false, true, true, false, true, false, 3, 3, 3, 3, 3, 1, 2, 3, 4, 5, 6, 7, 14, 10, 104 );
    parameter.RSV.push_back(*state_1_4);
    delete state_1_4;
    render_state * state_1_5 = new render_state(true,false, true, true, false, true, false, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 11, 10, 104 );
    parameter.RSV.push_back(*state_1_5);
    delete state_1_5;
    render_state * state_1_6 = new render_state(true,false, true, true, false, true, false, 5, 5, 5, 5, 5, 1, 2, 3, 4, 5, 6, 7, 11, 10, 104 );
    parameter.RSV.push_back(*state_1_6);
    delete state_1_6;
    render_state * state_1_7 = new render_state(true,false, true, true, false, true, false, 2, 2, 2, 2, 2, 1, 2, 3, 4, 5, 6, 7, 11, -3, 106 );
    parameter.RSV.push_back(*state_1_7);
    delete state_1_7;
    render_state * state_1_8 = new render_state(true,false, true, true, false, true, false, 4, 4, 4, 4, 4, 1, 2, 3, 4, 5, 6, 7, 11, 10, 106 );
    parameter.RSV.push_back(*state_1_8);
    delete state_1_8;
    
    //Grab
	render_state * state_grab = new render_state(true, false, true, true, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 20, 0, 117 );
	state_grab->Advanced = true;
	state_grab->grab = true;
    parameter.RSV.push_back(*state_grab);
    delete state_grab;

    // Static
    parameter.life_bar_nr = parameter.Relation_Spritenr_type_dev( 701 ); 

	render_state * state_frame = new render_state(true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 100, 10, 702 );
	state_frame->Advanced = true;
	state_frame->static_ = true;
    parameter.RSV.push_back(*state_frame);
    delete state_frame;
    
    
    
    
    
//    render_state * state_1_5 = new render_state(false, true, true, false, true, false, 2, 2, 2, 1, 2, 3, 4, 12, -12, 105 );
//    parameter.RSV.push_back(*state_1_5);
//    delete state_1_5;
    //cout << parameter.render_state_vector.at(0).sprite_nr << endl;

};

//
//// SLASK
//                                if ( LineLineIntersect(x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, x_location_intersection, y_location_intersection) ) {
//                                    x_location_intersection_int = (int)x_location_intersection ;
//                                    y_location_intersection_int = (int)y_location_intersection ;
//                                    //cout << "RT_1 " << x_location_intersection_int << "_" << P3_x << "_" << P4_x <<endl;
//
//                                        if ( y_location_intersection_int == P3_y && x_location_intersection_int >= P3_x && x_location_intersection_int <= P4_x ){
//                                            //cout << "intersect" << endl;
//                                            cout << "RT_2 " << x_location_intersection_int << "_" << y_location_intersection_int << P3_y <<endl;
//                                            y_velocity = 0;
//                                            roof_contact = true;
//                                            x_location = x_location_intersection_int - width ;
//                                            y_location = y_location_intersection_int + 1;
//                                        } else {
//                                        }
//                                } else {
//                                }
//                            // left of the block check
//                            x_3 = P3_x ;
//                            y_3 = P3_y ;
//                            x_4 = P3_x ;
//                            y_4 = P4_y ;
//
//                                if ( LineLineIntersect(x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, x_location_intersection, y_location_intersection) ) {
//                                    x_location_intersection_int = (int)x_location_intersection ;
//                                    y_location_intersection_int = (int)y_location_intersection ;
//                                    //cout << x_location_intersection << "_" << y_location_intersection << endl;
//                                        if ( x_location_intersection_int == P3_x && y_location_intersection_int <= P3_y && y_location_intersection_int >= P4_y && latch){
//                                            cout << "RT_3 " << x_location_intersection_int << "_" << y_location_intersection_int << P3_x <<endl;
//                                            //x_velocity = 0;
//                                            x_location = x_location_intersection_int - width ;
//                                            y_location = y_location_intersection_int;
//                                        } else {
//                                        }
//                                } else {
//                                }
//


























