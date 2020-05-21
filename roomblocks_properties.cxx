
#include "roomblocks_properties.h"


void stars::set_stars() {
	
	int total_pixels = 0;
	
	switch ( field_type ) {
		
	case(1):

		total_pixels = ( x_u - x_lo ) * ( y_u - y_lo ) ;
		
		for ( int i = 0; i < total_pixels; i++ ) {
			
			if ( (rand() % 10000 + 1) > 9996 ) {
				
				
					x.push_back( (rand() %  (x_u - x_lo) + (x_lo + 1) ) );
					y.push_back( (rand() %  (y_u - y_lo) + (y_lo + 1) ) );
					nr.push_back( sprite_nr.at( ((rand() % (sprite_index.size()) + 0)) ) );	
			
			} else {
			} ;
			

			
		};
	
	break;
	case(2):
		total_pixels = ( x_u - x_lo ) * ( y_u - y_lo ) ;
		
		for ( int i = 0; i < total_pixels; i++ ) {
			
			if ( (rand() % 10000 + 1) > 9998 ) {
				
				
			x.push_back( (rand() %  (x_u - x_lo) + (x_lo + 1) ) );
			y.push_back( (rand() %  (y_u - y_lo) + (y_lo + 1) ) );
			nr.push_back( sprite_nr.at( ((rand() % (sprite_index.size()) + 0)) ) );

			} else {
			} ;
			

			
		};
	break;
	case(3):
		total_pixels = ( x_u - x_lo ) * ( y_u - y_lo ) ;
		
		for ( int i = 0; i < total_pixels; i++ ) {
			
			if ( (rand() % 10000 + 1) > 9999 ) {
				
				
			x.push_back( (rand() %  (x_u - x_lo) + (x_lo + 1) ) );
			y.push_back( (rand() %  (y_u - y_lo) + (y_lo + 1) ) );
			nr.push_back( sprite_nr.at( ((rand() % (sprite_index.size()) + 0)) ) );

			} else {
			} ;
			

			
		};
	break;
		
	default:
	break; 
		
	};
	
	
	
};

void stars::sprite_config() {
	
	switch ( field_type ) {
		case(1):
			sprite_index.push_back( 410 ); 
			sprite_index.push_back( 401 ); 
		break;
		case(2):
			sprite_index.push_back( 406 );
			sprite_index.push_back( 407 );
			sprite_index.push_back( 408 );
			sprite_index.push_back( 409 );

		break;
		case(3):
			sprite_index.push_back( 423 );
			sprite_index.push_back( 424 );
			sprite_index.push_back( 425 );
			
		break;
		
	};
	
	
	
	for (int i=0; i < all_sprites.size(); i++) {
		
		for ( int j = 0; j < sprite_index.size(); j++ ) {
			
			if ( all_sprites.at(i).sprite_index == sprite_index.at(j) ) {
				sprite_nr.push_back( i )  ;

			} else {

			};		
			
			
		};
		

	};

        
};


void stars::render_stars() {
	
	for ( int i = 0; i < x.size() ; i++ ) {
		
		render_requests * obj_stars = new render_requests(nr.at(i), x.at(i), y.at(i), 1);

		render_req.push_back(*obj_stars);
		delete obj_stars;
		obj_stars = 0;
		
	};
	
	

	
	
};


stars::stars( int type, int x_low, int y_low, int x_up, int y_up ) {


field_type = type;
x_lo = x_low;
y_lo = y_low;
x_u = x_up;
y_u = y_up;

sprite_config();
set_stars();
	
};





room_limits::room_limits(int in_x_down_left, int in_y_down_left, int in_x_up_right, int in_y_up_right, int set_x_down_left, int set_y_down_left, int set_x_up_right, int set_y_up_right ) {
	
	
	x_down_left = in_x_down_left;
	y_down_left = in_y_down_left;
	x_up_right = in_x_up_right;
	y_up_right = in_y_up_right;
	
	x_down_left_set = set_x_down_left;
	y_down_left_set = set_y_down_left;
	x_up_right_set = set_x_up_right;
	y_up_right_set = set_y_up_right;
	
	
	
	
	
}; 
