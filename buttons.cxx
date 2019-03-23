// cpp file for the buttons

#include <iostream>
#include "buttons.h"
#include <sr595.h>
#include <wiringPi.h>

using namespace std;


int add(int x, int y)
{
    return x + y;
}

button_input::button_input(int a){

//sr595Setup (100, 10, 0, 1, 2) ;
//    Use wiringPi pins 0, 1 & 2 for data, clock and latch
sr595Setup (100, nr_buttons, 21, 22, 23) ;
fill(button_array[0], button_array[0] + 3 * 10, 0);

}

void button_input::setJumpstate(int state){
	button_array[0][0] = state;
	
	};
	
void button_input::updateState(){

    digitalWrite (101, 1) ;
        
	//~ if ( digitalRead(27) == 1 ) {
		//~ setJumpstate(1);
	//~ } else {
		//~ setJumpstate(0);       
	//~ }

	for (int i = 0; i < nr_buttons-1; i++) {
		digitalWrite(101+i,1);
				if ( digitalRead(27) == 1 ) {
					//setJumpstate(1);
					button_array[0][i] = 1;
				} else {
					//setJumpstate(0);
					button_array[0][i] = 0;       
				}
		digitalWrite(101+i,0);		
	}


	
};

int button_input::getJumpstate(){
	return button_array[0][0];
};

void button_input::printAll(){
	
for (int i = 0; i < nr_buttons; i++){
	printf("%d", button_array[0][i]);
}	
printf("\n");	
};

