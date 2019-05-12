#ifndef GAME_H
#define GAME_H


#include "buttons.h"



class game {


public:



int game_state_current;
long int screensize;
int fbfd;


game(int a); // main game constructor

~game();
void game_loop();
void game_main();
void game_setup();
void game_close();
};




















#endif // GAME_H
