#ifndef GAME_H
#define GAME_H


#include "buttons.h"
#include "test.h"


class game {


public:



int game_state_current;
long int screensize;
int fbfd;
//test tester;

game(int a); // http://www.cplusplus.com/forum/beginner/34589/


~game();
void game_loop();
void game_main();
void game_setup();
void game_close();
};




















#endif // GAME_H
