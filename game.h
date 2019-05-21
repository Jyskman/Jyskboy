#ifndef GAME_H
#define GAME_H


#include "buttons.h"
#include "render.h"
#include "soundmanager.h"

#include <chrono>
#include <ctime>
using namespace std;

class game {


public:

// Time tools
bool game_is_running;
long game_loop_start_ms;
long game_loop_stop_ms;
long fps = 40;
long game_sleep_time;
struct timespec spec;
float time;
float time_ms;
chrono::duration<double> elapsed_seconds;


int game_state_current;
long int screensize;
int fbfd;
button_input buttons; // button object now here instead of the main game loop
render screen;
soundmanager audio;
champ hero;
game(int a); // http://www.cplusplus.com/forum/beginner/34589/


~game();
void game_loop();
void game_main();
void game_setup();
void game_close();
void game_fbp_clear();
void game_frame();
};






#endif // GAME_H
