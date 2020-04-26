#ifndef GAME_H
#define GAME_H


#include "buttons.h"
#include "render.h"
#include "soundmanager.h"
#include "physics.h"
#include <chrono>
#include <ctime>
#include <vector>
#include "enemy.h"
#include "roomblocks_properties.h"
using namespace std;

class game {


public:

// Time tools
bool game_is_running;
bool initial_config = true;
long game_loop_start_ms;
long game_loop_stop_ms;
long fps = 30;
long game_sleep_time;
struct timespec spec;
float time;
float time_ms;
chrono::duration<double> elapsed_seconds;

// game variables
void setupWeaponprofiles();
void setup_animation_profiles();
vector<weaponProfile> gameWProfiles;
vector<attack> gameAttacks;
vector<enemy> gameEnemys;
void createAttacks(button_input& parameter);
void setXYfactor();
int x_factor, y_factor;

int room_current;
int room_max = 10; // 0 is a room
int room_prev;
int game_state_current;
int physics_current;
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
bool game_room_switch();
void check_lim();
void check_lim_upon_roomswitch();
int current_lim = 0;
// enemy functions

void enemy_manager();
bool enemy_config = true;

void portals_run_render();
void animations_run_render();
void animations_run_render_back();
void update_attacks();

void remove_used_items();

};






#endif // GAME_H
