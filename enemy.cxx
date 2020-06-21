
// Enemy base class

#include "enemy.h"
#include "setup_sprites.h"
#include <iostream>
#include "physics.h"
#include <math.h>
#include <cstdlib>
#include "environment.h"

using namespace std;
// E



void enemy::perception(champ &parameter) {

float param_x = (float)center_x + (float)x_location;
float param_y = (float)center_y + (float)y_location;

        perception_distance = sqrt( ( param_x - parameter.x_center )*( param_x - parameter.x_center )+( param_y - parameter.y_center )*( param_y - parameter.y_center ) );
        // direction to champ
        perception_angle = (  ( parameter.x_center - param_x )/( perception_distance )  );
        //cout << "angle" << acos(cos_alfa) << endl;
        //champ_direction =  0;
        if ( parameter.y_center > param_y ) {
            perception_above = false;
            //cout << "is below" << endl;
        } else {
            perception_above = true;
            //cout << "is above" << endl;
        }

        // left or right?
        if ( parameter.x_center > param_x ) {
            perception_right = true;
            //cout << "C is right" << endl;
        } else {
            perception_right = false;
            //cout << "C is left" << endl;
        }
        
        
        float x_1 = param_x ;
		float y_1 = param_y ;
		
		
		float x_2 = parameter.x_center ;
		float y_2 = parameter.y_center ;


		float length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) ) ;
		//cout << "L_" << length << endl;

		float cos_alfa = (  ( x_2 - x_1 )/( length )  );
		float a_cos = acos( cos_alfa );


		perception_angle = a_cos;
		//~ cout << a_cos << endl;
		
		
		switch (enemy_type) {
			case(1):
			break;
			
			case(10):
			
				if ( 	( (perception_angle > 0.00 && perception_angle < ( M_PI/8.00 ) ) || 
						(perception_angle > 7*( M_PI/8.00 ) && perception_angle < 8*( M_PI/8.00 )) ) && perception_above == true)  {
					
					gun_direction = 3;
					
				} else {
				};
				
				if ( 	( (perception_angle > 0.00 && perception_angle < ( M_PI/8.00 ) ) || 
						(perception_angle > 7*( M_PI/8.00 ) && perception_angle < 8*( M_PI/8.00 )) ) && perception_above == false)  {
					
					gun_direction = 3;
					
				} else {
				};

				
				
				
				if ( ((perception_angle > ( M_PI/8.00 ) && perception_angle < 3*( M_PI/8.00 )) ||
						(perception_angle > 5*( M_PI/8.00 ) && perception_angle < 7*( M_PI/8.00 )) ) && perception_above == true ) {
					
					gun_direction = 2;
					
				} else {
				}
				

				
				
				if ( (perception_angle > 3*( M_PI/8.00 ) && perception_angle < 5*( M_PI/8.00 )) && perception_above == true ) {
					
					gun_direction = 1;
					
				} else {
				}
				
				if ( (perception_angle > 3*( M_PI/8.00 ) && perception_angle < 5*( M_PI/8.00 )) && perception_above == false ) {
					
					gun_direction = 5;
					
				} else {
				}
				
				
				if ( ((perception_angle > ( M_PI/8.00 ) && perception_angle < 3*( M_PI/8.00 )) ||
						(perception_angle > 5*( M_PI/8.00 ) && perception_angle < 7*( M_PI/8.00 )) ) && perception_above == false ) {
					
					gun_direction = 4;
					
				} else {
				}
				
				


			
			break;
			
			
			
		};


	//~ cout << gun_direction << endl;

};





void enemy::motion( physics &parameter ) {

//length = sqrt( ( x_1 - x_2 )*( x_1 - x_2 )+( y_1 - y_2 )*( y_1 - y_2 ) )

    switch ( enemy_type ) {

        case(1):

            y_v_float = y_v_float - parameter.new_g;

            if ( perception_right == true ) {

                x_v_float = x_v_float + main_v;
            } else {
                x_v_float = x_v_float - main_v;
            }

            if ( perception_above == true ) {

                y_v_float = y_v_float - main_v;
            } else {
                y_v_float = y_v_float + main_v;
            }



        break;
        case(2):
        break;
        case(10):

			main_v = 0.00;

            y_v_float = y_v_float - parameter.new_g;

            if ( perception_right == true ) {

                x_v_float = x_v_float + main_v;
            } else {
                x_v_float = x_v_float - main_v;
            }

            if ( perception_above == true ) {

                y_v_float = y_v_float - main_v;
            } else {
                y_v_float = y_v_float + main_v;
            }


			


        break;
        default:
        break;



    };
    
    
      

    parameter.calculate_velocity( y_v_float, x_v_float, 0.050, 1); 


    x_location_prev = x_location; 
    y_location_prev = y_location; 


    //~ y_v_float = 0;

    
    x_location = x_location + (int)x_v_float; 
    y_location = y_location + (int)y_v_float; 




    previous_x.push_back(x_location + width );
    previous_y.push_back(y_location + height );
    //previous_y.push_back(y_location);
    previous_x.erase( previous_x.begin() + 0 );
    previous_y.erase( previous_y.begin() + 0 );



    if ( (x_location - x_location_prev) > 0 ) {
        current_sprite_direction = false;
    } else {
        current_sprite_direction = true;
    };


};



void enemy::set_hitbox_set() {

 int test = 0;

    switch (enemy_type) {

        case (1):

            for ( int i = 0; i < RSV.size() ; i++ ) {

                hitbox_object * obj_h = new hitbox_object(0,0, all_sprites.at( RSV.at(i).sprite_nr ).getWidth(), all_sprites.at( RSV.at(i).sprite_nr ).getHeight() );
                enemy_hitbox_set.push_back( *obj_h );
                delete obj_h;
                obj_h = 0;

                if ( RSV.at(i).use_special_offset == false ) {
                    center_x = all_sprites.at( RSV.at(i).sprite_nr ).getWidth() / 2;
                    center_y = all_sprites.at( RSV.at(i).sprite_nr ).getHeight() / 2;

                } else {
                };

            };

        break;
        case (2):
        break;
        case (10):

            for ( int i = 0; i < RSV.size() ; i++ ) {

                hitbox_object * obj_h = new hitbox_object(0,0, all_sprites.at( RSV.at(i).sprite_nr ).getWidth(), all_sprites.at( RSV.at(i).sprite_nr ).getHeight() );
                
                if ( RSV.at(i).is_g == true ) {
					
					obj_h->mark = true;
					
				} else {
				};
                
                
                enemy_hitbox_set.push_back( *obj_h );
                delete obj_h;
                obj_h = 0;

                if ( RSV.at(i).use_special_offset == false ) {
                    center_x = all_sprites.at( RSV.at(i).sprite_nr ).getWidth() / 2;
                    center_y = all_sprites.at( RSV.at(i).sprite_nr ).getHeight() / 2;

                } else {
                };

            };
            
           
            

			


        break;
        default:
        break;



    }



};



void enemy::RSV_setup() {


    if ( enemy_type == 1 ) {


        for (int i = 0; i < 10; i++) {
            previous_x.push_back(0);
            previous_y.push_back(0);
        };
        //cout << previous_x.size() << endl;


        render_state * state_1_1 = new render_state( true, 1, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 207 );
        RSV.push_back(*state_1_1);
        delete state_1_1;

        render_state * state_1_2 = new render_state(true, 2, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 207 );
        RSV.push_back(*state_1_2);
        delete state_1_2;

        render_state * state_1_3 = new render_state(false, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 208 );
        RSV.push_back(*state_1_3);
        delete state_1_3;


        //Offset setup prototype
        //all_sprites.at(RSV.at(1).sprite_nr).getWidth() +2;
        enemy_offset[0][2] = 0 ; // first object x offset
        enemy_offset[1][2] = 0 ; // first object y offset
        // enemy has a main width and height which mirror x is based on, set below
        width = all_sprites.at(RSV.at(2).sprite_nr).getWidth();
        height = all_sprites.at(RSV.at(2).sprite_nr).getHeight();


        enemy_offset[0][1] = all_sprites.at(RSV.at(2).sprite_nr).getWidth() - 2 ; // first object x offset
        enemy_offset[1][1] = 0 ; // first object y offset

        enemy_offset[0][0] = enemy_offset[0][1] + all_sprites.at(RSV.at(0).sprite_nr).getWidth() - 2 ; // first object x offset
        enemy_offset[1][0] = 0 ; // first object y offset

        for ( int i = 0; i < RSV.size(); i++ ) {
            RSV.at(i).x_off = enemy_offset[0][i];
            RSV.at(i).y_off = enemy_offset[1][i];

        }


    }
    
    
    if ( enemy_type == 10 ) {


		grid_distance = 16;
        
        
        //~ enemy_offset[0][0] = grid_distance * cos(motion_angle + M_PI/2 ) ; // first object x offset
        //~ enemy_offset[1][0] =  - 1 * grid_distance * sin(motion_angle + M_PI/2 ) ; // first object y offset
        
        render_state * state_1_1 = new render_state( true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,grid_distance, M_PI, 207 );
        state_1_1->is_g = true;
        state_1_1->is_sub = true;
        RSV.push_back(*state_1_1);
        delete state_1_1;
        

        render_state * state_1_2 = new render_state(true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,grid_distance, 0.00, 207 );
        state_1_2->is_g = true;
        state_1_2->is_sub = true;
        RSV.push_back(*state_1_2);
        delete state_1_2;
        
        render_state * state_1_3 = new render_state( true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,2*grid_distance, M_PI, 207 );
        state_1_3->is_g = true;
        state_1_3->is_sub = true;
        RSV.push_back(*state_1_3);
        delete state_1_3;
        

        render_state * state_1_4 = new render_state(true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,2*grid_distance, 0.00, 207 );
        state_1_4->is_g = true;
        state_1_4->is_sub = true;
        RSV.push_back(*state_1_4);
        delete state_1_4;
        
       
        render_state * state_1_1_1 = new render_state( true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,grid_distance, M_PI/2.00, 207 );
        state_1_1_1->is_g = true;
        state_1_1_1->is_sub = true;
        RSV.push_back(*state_1_1_1);
        delete state_1_1_1;
        

        render_state * state_1_2_1 = new render_state(true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,grid_distance, M_PI*1.50, 207 );
        state_1_2_1->is_g = true;
        state_1_2_1->is_sub = true;
        RSV.push_back(*state_1_2_1);
        delete state_1_2_1;
        
        render_state * state_1_3_1 = new render_state( true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,2*grid_distance, M_PI/2.00, 207 );
        state_1_3_1->is_g = true;
        state_1_3_1->is_sub = true;
        RSV.push_back(*state_1_3_1);
        delete state_1_3_1;
        

        render_state * state_1_4_1 = new render_state(true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,2*grid_distance, M_PI*1.50, 207 );
        state_1_4_1->is_g = true;
        state_1_4_1->is_sub = true;
        RSV.push_back(*state_1_4_1);
        delete state_1_4_1;
        
        //~ render_state * state_1_3 = new render_state( true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,15, M_PI, 207 );
        //~ RSV.push_back(*state_1_3);
        //~ delete state_1_3;

        //~ render_state * state_1_4 = new render_state(true, 0, false, true, false, true, false, true, false, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, true ,30, M_PI, 207 );
        //~ RSV.push_back(*state_1_4);
        //~ delete state_1_4;
        
        

        
        render_state * state_1_5 = new render_state(true, false, true, false, true, false, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 0, 0, 209 );
        state_1_5->is_main = true;
        RSV.push_back(*state_1_5);
        delete state_1_5;
        
        render_state * state_1_8 = new render_state(true, false, true, false, true, false, 3, 3, 3, 3, 3, 1, 2, 3, 4, 5, 6, 7, 0, 0, 209 );
        RSV.push_back(*state_1_8);
        delete state_1_8;
        
       
        render_state * state_1_6 = new render_state(true, false, true, false, true, false, 5, 5, 5, 5, 5, 1, 2, 3, 4, 5, 6, 7, 0, 0, 209 );
        RSV.push_back(*state_1_6);
        delete state_1_6;
        
        
        render_state * state_1_7 = new render_state(true, false, true, false, true, false, 2, 2, 2, 2, 2, 1, 2, 3, 4, 5, 6, 7, 0, 0, 210 );
        RSV.push_back(*state_1_7);
        delete state_1_7;
        
        render_state * state_1_9 = new render_state( true, false, true, false, true, false, 4, 4, 4, 4, 4, 1, 2, 3, 4, 5, 6, 7, 0, 0, 210 );
        RSV.push_back(*state_1_9);
        delete state_1_9;
        
        
        

        width = all_sprites.at(RSV.at(0).sprite_nr).getWidth();
        height = all_sprites.at(RSV.at(0).sprite_nr).getHeight();


		for (int i = 0; i < RSV.size(); i++ ) {
		
			if ( RSV.at(i).is_sub == true ) {
				
				for ( int j = 0; j < RSV.size(); j++  ) {
					
					if ( RSV.at(j).is_main == true ) {
						
						RSV.at(i).RSV_length =  RSV.at(i).RSV_length + ( all_sprites.at(RSV.at(j).sprite_nr).getWidth()/2 - all_sprites.at(RSV.at(i).sprite_nr).getWidth()/2 ) ;
						//~ RSV.at(i).x_off = 0;
						RSV.at(i).y_off = RSV.at(i).y_off + ( all_sprites.at(RSV.at(j).sprite_nr).getHeight()/2 - all_sprites.at(RSV.at(i).sprite_nr).getHeight()/2 ) ; 
						
					};
					
				};
				
				
			} else {
			};
		
		
		
		
		};



    }


}

void enemy::vulnerability_setup() {

    switch (enemy_type) {

        case (1):
            can_take_damage = true;
            life = 1;
        break;
        case (2):
        case (10):
			can_take_damage = true;
            life = 10;
        break;
        break;
        default:
        break;


    }


};


enemy::enemy( int e_type, int start_x, int start_y)  {

x_location = start_x ;
y_location = start_y ;
y_v_float = 0;

_id = 10 + (rand() % 1000);


enemy_type = e_type;
vector<hitbox_object> enemy_hitbox_set;
vector<render_state> RSV;
vector<int> previous_x;
RSV_setup(); // also height and width main properties
vulnerability_setup();
set_hitbox_set();
destroy = false;
    switch (e_type) {
        case(1):
            main_v = 0.20;
        break;
        case(10):
            main_v = 0.20;
        break;

    };


};

void enemy::test() {
cout << "Func ok" << endl;
};

void enemy::item_drop(int room) {
	
	switch ( enemy_type ) {
		
		case(1): {
		
			if ( ( rand() % 10 ) > 6 ) {
				
				item * obj = new item(510, x_location , y_location ) ;
				obj->setup();
				obj->x_v_float = (float)destroy_v_x;
				obj->y_v_float = (float)destroy_v_y;
				room_objects.at(room).room_drop_items.push_back(*obj);
				obj = 0;
				
			} else {
			};
		
		
			//~ item * obj = new item(510, x_location , y_location ) ;
			//~ obj->setup();
			//~ obj->x_v_float = (float)destroy_v_x;
			//~ obj->y_v_float = (float)destroy_v_y;
			//~ room_objects.at(room).room_drop_items.push_back(*obj);
			//~ obj = 0;

		
		
		break;
		}
		case(2):
		break;
		case(3):
		break;
		
		
		
	};
	
	
	
};






void enemy::resolve_damage( vector<attack> &parameter, champ &hero_parameter ) {



//E
int X_1_A = 0;
int X_2_A = 0;
int Y_1_A = 0;
int Y_2_A = 0;

//C
int X_1_C = hero_parameter.x_location;
int X_2_C = hero_parameter.x_location + hero_parameter.width;
int Y_1_C = hero_parameter.y_location;
int Y_2_C = hero_parameter.y_location + hero_parameter.height;

// Shot
int X_1_B = 0;
int X_2_B = 0;
int Y_1_B = 0;
int Y_2_B = 0;

bool hit = false;

    for ( int i = 0; i < enemy_hitbox_set.size() ; i++) {

		//~ cout << "EE   " << enemy_hitbox_set.at(i).x_base << endl;

        X_1_A = x_location + enemy_hitbox_set.at(i).x_u_left;
        X_2_A = x_location + enemy_hitbox_set.at(i).x_l_right ;
        Y_1_A = y_location + enemy_hitbox_set.at(i).y_u_left;
        Y_2_A = y_location + enemy_hitbox_set.at(i).y_l_right ;
        
        if (enemy_hitbox_set.at(i).sub_unit == true) {
		
		        X_1_A = enemy_hitbox_set.at(i).x_base + enemy_hitbox_set.at(i).x_u_left;
				X_2_A = enemy_hitbox_set.at(i).x_base + enemy_hitbox_set.at(i).x_l_right ;
				Y_1_A = enemy_hitbox_set.at(i).y_base + enemy_hitbox_set.at(i).y_u_left;
				Y_2_A = enemy_hitbox_set.at(i).y_base + enemy_hitbox_set.at(i).y_l_right ;
				//~ cout << "EE   " << enemy_hitbox_set.at(i).x_base << endl;
		
		} else {
		};
        


		//~ render_primitive_line(X_1_A, Y_1_A, X_2_A, Y_2_A, 1, 401  );

        // hitbox contact
        hit = true;

        if (  X_1_C < X_2_A && X_2_C > X_1_A && Y_1_C < Y_2_A && Y_2_C > Y_1_A ) {
                hit = false;

                if ( hero_parameter.hero_invincible_counter == 0 ) {
                    cout << "hit" << endl;
                    hero_parameter.hero_life--;
                    hero_parameter.hero_invincible_counter =+ 10;
                } else {
                }

        } else {

        }



        for ( int j = 0; j < parameter.size() ; j++ ) {
            // Enemy


            X_1_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_u_left;
            X_2_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_l_right;
            Y_1_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_u_left;
            Y_2_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_l_right;;

			render_primitive_line(X_1_B, Y_1_B, X_2_B, Y_2_B, 1, 401  );

                hit = true;
            if (  X_1_B < X_2_A && X_2_B > X_1_A && Y_1_B < Y_2_A && Y_2_B > Y_1_A ) {
                    hit = false;


            } else {

            }

            if ( hit == false && _id != parameter.at(j).who_fired_med_id ) {
                cout << "hit" << endl;
                life = life - parameter.at(j).a_damage ;
                parameter.at(j).destroy = true;
                if ( life <= 0 ) {
                    destroy = true;

                    destroy_v_x = parameter.at(j).a_x_vel ;
                    destroy_v_y = parameter.at(j).a_y_vel ;
                    

                } else {
                }


                animation_requests * obj = new animation_requests(12, x_location + center_x, y_location + center_y , 0, 0);
                anime_req.push_back(*obj);
                delete obj;

            } else {
            }


        };
        




    };


	// Attacks and champ
	for ( int j = 0; j < parameter.size() ; j++ ) {

		X_1_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_u_left;
		X_2_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_l_right;
		Y_1_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_u_left;
		Y_2_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_l_right;;

			hit = true;
		if (  X_1_B < X_2_C && X_2_B > X_1_C && Y_1_B < Y_2_C && Y_2_B > Y_1_C ) {
				hit = false;


		} else {

		}

		if ( hit == false && parameter.at(j).who_fired_med_id != hero_parameter.hero_id ) {
			cout << "hit" << endl;
			hero_parameter.hero_life = hero_parameter.hero_life - parameter.at(j).a_damage ;
			parameter.at(j).destroy = true;



			animation_requests * obj = new animation_requests(12, x_location + center_x, y_location + center_y , 0, 0);
			anime_req.push_back(*obj);
			delete obj;

		} else {
		}


	};






//cout << "end" << endl;
//if (RectA.X1 < RectB.X2 && RectA.X2 > RectB.X1 &&
//    RectA.Y1 > RectB.Y2 && RectA.Y2 < RectB.Y1)

};


void enemy::create_Enemy_attacks( game * parameter ) {
	

	switch ( enemy_type ) {
		
		case(1):
		break;
		
		
		case(10): {
		
		
				//~ attack( bool animation, int animation_index ,int damage, int x_pos, int y_pos, int x_vel, int y_vel, int hitboxtype, int cycles );
		
		
				if ( rand() % 100 > 95 ) {
					
						//~ cout << "htype  " << parameter->gameWProfiles.at(3).hitbox_t << endl;
					
						attack * obj = new attack( true, parameter->gameWProfiles.at(3).animation_index,parameter->gameWProfiles.at(3).damage, x_location, y_location,
						parameter->gameWProfiles.at(3).x_vel, parameter->gameWProfiles.at(3).y_vel,
						parameter->gameWProfiles.at(3).hitbox_t,
						parameter->gameWProfiles.at(3).cycles_to_terminate );
						
						obj->who_fired_med_id = _id;
						
						parameter->gameAttacks.push_back(*obj);
						delete obj;
						

						
				} else {
				}
		
		

		
		
		
		break;
		}
		
		
		
	};
	
	
	
	
	
	
	
};

void enemy::setRender()  {


    switch (render_req_mode) {
    case 0:
//        if (sprite_error == false) {
//            render_requests * obj = new render_requests(sprite_nr, x_location, y_location, palette_current);
//
//            render_req.push_back(*obj);
//            delete obj;
//
//
//        } else {
////        cout << "ok" << endl;
//        };
    break;
    case 1:
        if (sprite_error == false) {
//            render_requests * obj = new render_requests(current_form_info[4], x_location, y_location, palette_current,current_sprite_direction);
//            render_requests * obj2 = new render_requests(current_form_info[5], x_location, y_location+12, palette_current, current_sprite_direction);
//            render_req.push_back(*obj);
//            render_req.push_back(*obj2);
//            delete obj;
//            delete obj2;


        } else {
//        cout << "ok" << endl;
        };
    break;
    case 2:



for ( int i = 0; i < RSV.size(); i++ ) {


    bool fc = floor_contact;
    bool gc = general_contact;
    int in = internal_state;
    int g = gun_direction;
    bool r = roof_contact;

    int x_mirror = 0;
    int RSV_x = 0;
    int RSV_y = 0;



    int rot;
    bool vertical;
    bool horisontal;

    if ( (RSV.at(i).f_1 == fc || RSV.at(i).f_2 == fc) && (RSV.at(i).gu_1 == g || RSV.at(i).gu_2 == g || RSV.at(i).gu_3 == g || RSV.at(i).gu_4 == g || RSV.at(i).gu_5 == g) && ( RSV.at(i).int_1 == in || RSV.at(i).int_2 == in || RSV.at(i).int_3 == in || RSV.at(i).int_4 == in || RSV.at(i).int_5 == in || RSV.at(i).int_6 == in || RSV.at(i).int_7 == in ) ) {
    vertical = current_sprite_v_direction;
    horisontal = current_sprite_direction;
    rot = 1;

    RSV_x = x_location+RSV.at(i).x_off;
    RSV_y = y_location+RSV.at(i).y_off;
    
				switch (enemy_type) {
						case (1):
							if ( abs(y_v_float) > abs(x_v_float)  ) {
								
								rot = 2;
								
								if ( (int)y_v_float < 0 ) {
									horisontal = true;
								} else {
									horisontal = false;
								};
								
									
								
								
							} else {
								rot = 1;
							};


						break;
						case (2):
						break;
						case (10):
						
							x_mirror = 0;
							current_sprite_direction = perception_right;
							


						break;
					};




					//~ cout << " RSV " << endl;
                        // gun direction
                    if ( RSV.at(i).gu_1 == 1 && RSV.at(i).gu_2 == 1 && RSV.at(i).gu_3 == 1 && RSV.at(i).gu_4 == 1 && RSV.at(i).gu_5 == 1) {
 
                            if ( perception_right == true ) {
                                rot = 2;
                                horisontal = true;
                                RSV_y = RSV_y;
                                vertical = true;
                            } else {
                            }
                            if ( perception_right == false ) {
                                rot = 2;
                                horisontal = true;
                                vertical = true;
                                RSV_y = RSV_y;
                            } else {
                            }

                    } else {
                    }
                    
                    
                    if ( RSV.at(i).gu_1 == 2 && RSV.at(i).gu_2 == 2 && RSV.at(i).gu_3 == 2 && RSV.at(i).gu_4 == 2 && RSV.at(i).gu_5 == 2) {
 
                            if ( perception_right == true ) {
                                //~ rot = 2;
                                horisontal = false;
                                RSV_y = RSV_y;
                                //~ vertical = true;
                            } else {
                            }
                            if ( perception_right == false ) {
                                //~ rot = 2;
                                horisontal = true;
                                //~ vertical = true;
                                RSV_y = RSV_y;
                            } else {
                            }

                    } else {
                    }
                    if ( RSV.at(i).gu_1 == 3 && RSV.at(i).gu_2 == 3 && RSV.at(i).gu_3 == 3 && RSV.at(i).gu_4 == 3 && RSV.at(i).gu_5 == 3) {
 
                            if ( perception_right == true ) {
                                //~ rot = 2;
                                horisontal = false;
                                RSV_y = RSV_y;
                                //~ vertical = true;
                            } else {
                            }
                            if ( perception_right == false ) {
                                //~ rot = 2;
                                horisontal = true;
                                //~ vertical = true;
                                RSV_y = RSV_y;
                            } else {
                            }

                    } else {
                    }
                    // gun down
                    if ( RSV.at(i).gu_1 == 5 && RSV.at(i).gu_2 == 5 && RSV.at(i).gu_3 == 5 && RSV.at(i).gu_4 == 5 && RSV.at(i).gu_5 == 5) {

                           if ( perception_right == true ) {
                                rot = 2;
                                horisontal = false;
                                RSV_y = RSV_y;
                                vertical = true;
                            } else {
                            }
                            if ( perception_right == false ) {
                                rot = 2;
                                horisontal = false;
                                vertical = true;
                                RSV_y = RSV_y;
                            } else {
                            }

                    } else {
                    }
                    // gun 45 down
                    if ( RSV.at(i).gu_1 == 4 && RSV.at(i).gu_2 == 4 && RSV.at(i).gu_3 == 4 && RSV.at(i).gu_4 == 4 && RSV.at(i).gu_5 == 4) {

                            if ( perception_right == true ) {
                                rot = 2;
                                horisontal = false;
                                vertical = false;
                                RSV_y = RSV_y + 0;
                            } else {
                            }
                            if ( perception_right == false ) {
                                rot = 2;
                                horisontal = false;
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
                    //~ cout << " 3_ " << RSV_x << endl;
                    if ( RSV.at(i).is_g == true ) {
                        x_mirror_gun = x_mirror;
                        RSV_x_gun = RSV_x-x_location;
                        RSV_y_gun = RSV_y-y_location;
                        horisontal_gun = horisontal;
                        vertical_gun = vertical;
                        rot_gun = rot;
                        gun_sprite_nr = RSV.at(i).sprite_nr;
                    }else {
                    }
					//~ cout << " 4_ " << RSV_x << endl;
                    if ( RSV.at(i).use_special_offset == true ) {

                        switch (enemy_type) {

                            case (1):

                                switch ( RSV.at(i).use_special_index ) {
                                    case(1):
                                        RSV_x = previous_x.at(7) - all_sprites.at(RSV.at(i).sprite_nr).getWidth()-1 ;
                                        RSV_y = previous_y.at(7) - all_sprites.at(RSV.at(i).sprite_nr).getHeight()-1 ;
                                    break;
                                    case(2):
                                        RSV_x = previous_x.at(5) - all_sprites.at(RSV.at(i).sprite_nr).getWidth()-1 ;
                                        RSV_y = previous_y.at(5) - all_sprites.at(RSV.at(i).sprite_nr).getHeight()-1 ;
                                    break;

                                    default:
                                    break;

                                }


								//~ cout << " 6_ " << RSV_x << endl;
                                //cout << previous_x.at(6) << endl;
                                x_mirror = 0;
                            break;
                            case(10):
                            
								motion_angle = motion_angle + M_PI/120;
								//~ motion_angle = motion_angle + 0;	
								
								RSV_x = RSV_x +  RSV.at(i).RSV_length * cos( RSV.at(i).RSV_angle + motion_angle );
								RSV_y = RSV_y +  RSV.at(i).RSV_length * sin( RSV.at(i).RSV_angle + motion_angle );
								
								//~ enemy_hitbox_set.at( RSV.at(i).hitbox_nr ).load_base(RSV_x, RSV_y);
								

								RSV.at(i).hit_box->load_base(RSV_x, RSV_y);

								//~ render_primitive_line(RSV_x-10, RSV_y, RSV_x+10, RSV_y, 1, 401  );
								//~ render_primitive_line(RSV_x, RSV_y-10, RSV_x, RSV_y+10, 1, 401  );
								//~ cout << RSV_x << " CC " << RSV.at(i).hit_box->x_base << endl;
								
								
                            break;


                        };


                    } else {
						
						
                        //~ switch (enemy_type) {
                            //~ case (1):
                                //~ if ( abs(y_v_float) > abs(x_v_float)  ) {
                                    
                                    //~ rot = 2;
                                    
                                    //~ if ( (int)y_v_float < 0 ) {
										//~ horisontal = true;
									//~ } else {
										//~ horisontal = false;
									//~ };
									
										
                                    
                                    
                                //~ } else {
									//~ rot = 1;
                                //~ };


                            //~ break;
                            //~ case (2):
                            //~ break;
                            //~ case (10):
                            
								//~ x_mirror = 0;
								
                                //~ if ( abs(y_v_float) > abs(x_v_float)  ) {
                                    
                                    //~ rot = 2;
                                    
                                    //~ if ( (int)y_v_float < 0 ) {
										//~ horisontal = true;
									//~ } else {
										//~ horisontal = false;
									//~ };
									
										
                                    
                                    
                                //~ } else {
									//~ rot = 1;
                                //~ };


                            //~ break;
                        //~ };


                    };

					//~ cout << " 8_ " << RSV_x << endl;

                    RSV.at(i).RSV_x_store = RSV_x-x_mirror;
                    RSV.at(i).RSV_y_store = RSV_y;
                    render_requests * obj = new render_requests( RSV.at(i).sprite_nr, RSV_x-x_mirror, RSV_y, palette_current,horisontal, vertical, rot);
                    render_req.push_back(*obj);
                    delete obj;
                    obj = 0;



					//~ cout << RSV_x << " _ " << RSV_y << endl;
    };


}
if (destroy == true) {
particle_generator( this, 0, 0, 50);
cout << "kkl" << endl;
} else {
}


    break;
    default:
    break;



    };






};

// Enemy create function for game
void create_and_reset_enemies( int room_nr, vector<enemy>& parameter ) {

    parameter.clear();


    for ( int i = 1; i < room_objects.at(room_nr).columns_storage.size()/room_objects.at(room_nr).column_items ; i++ ) {

        if ( room_objects.at(room_nr).columns_storage.at(3).at(i)  > 0 ) {

            enemy * new_enemy_1 = new enemy( room_objects.at(room_nr).columns_storage.at(3).at(i), room_objects.at(room_nr).columns_storage.at(4).at(i), room_objects.at(room_nr).columns_storage.at(5).at(i));
          
            parameter.push_back( *new_enemy_1 );
            delete new_enemy_1;
            new_enemy_1 = 0;

        }else {
        }


    }




    switch (room_nr) {

    case (0):
    break;
    case (1):
    break;
    case (2):{

//        enemy * new_enemy_1 = new enemy(1, 1, 1);
//        parameter.push_back( *new_enemy_1 );
//        delete new_enemy_1;
//        new_enemy_1 = 0;

    break;
    }

    case (3):
    break;

    default:
    break;

    };



};

void set_RSV_hitbox_relation( vector<enemy>& parameter ) {
	
	
	    for ( int k = 0; k < parameter.size() ; k++ ) {



            for ( int i = 0; i < parameter.at(k).RSV.size() ; i++ ) {
			
				for ( int j = 0; j < parameter.at(k).enemy_hitbox_set.size(); j++ ) {
					
					if ( parameter.at(k).enemy_hitbox_set.at(j).mark == true && parameter.at(k).RSV.at(i).is_g == true ) {
					
						parameter.at(k).RSV.at(i).hit_box = &(parameter.at(k).enemy_hitbox_set.at(j)) ;
						parameter.at(k).RSV.at(i).hitbox_nr = j;
						parameter.at(k).enemy_hitbox_set.at(j).mark = false;
						parameter.at(k).enemy_hitbox_set.at(j).sub_unit = true;
						parameter.at(k).RSV.at(i).is_g = false;
						

						//~ cout << "mark" << endl;
					} else {
					};
					
				};
				
			
			};




		};
	
	
	
	
	
	
	
	
	
	
	
	
};




