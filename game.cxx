
#include <iostream>
#include <vector>
#include "game.h"

#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <vector>


#include "render.h"

#include "champ.h"
#include "sprite_objects.h"
#include "setup_sprites.h"
#include "buttons.h"
#include "soundmanager.h"
#include <wiringPi.h>
#include "environment.h"
#include <time.h>
#include <algorithm>

#include <chrono>
#include <ctime>
using namespace std;

char *fbp = 0;

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

int fbfd = 0;
struct fb_var_screeninfo orig_vinfo;
long int screensize = 0;
struct fb_cmap mapm;
//struct fb_cmap {
//	__u32 start;			/* First entry	*/
//	__u32 len;			/* Number of entries */
//	__u16 *red;			/* Red values	*/
//	__u16 *green;
//	__u16 *blue;
//	__u16 *transp;			/* transparency, can be NULL */
//};



game::game(int a) : buttons(1), screen(1), audio(), hero(1, (100 * 100 * 3 + 1), 100, 100) {


// when game is created these items are also
game_state_current = 0;
room_current = 0;
physics_current = 0;
game_is_running = true;
room_prev = room_current;

    // Open the file for reading and writing
    fbfd = open("/dev/fb1", O_RDWR);
    if (!fbfd) {
      printf("Error: cannot open framebuffer device.\n");
//      return(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
      printf("Error reading variable information.\n");
    }
    printf("Original %dx%d, %dbpp\n", vinfo.xres, vinfo.yres,
       vinfo.bits_per_pixel);

    // Store for reset (copy vinfo to vinfo_orig)
    memcpy(&orig_vinfo, &vinfo, sizeof(struct fb_var_screeninfo));

    // Change variable info
    vinfo.bits_per_pixel = 16;
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo)) {
      printf("Error setting variable information.\n");
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
      printf("Error reading fixed information.\n");
    }

    // map fb to user mem
    screensize = vinfo.xres * vinfo.yres * 2;
    fbp = (char*)mmap(0,
              screensize,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fbfd,
              0);

    if ((int)fbp == -1) {
        printf("Failed to mmap.\n");
    }


};

game::~game() {

render_req.clear();


};

void game::game_close() {
    Close_audio();

    munmap(fbp, screensize);
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
        printf("Error re-setting variable information.\n");
    }
    close(fbfd);



};

void game::game_setup() {
    setup_sprites(screen);
    room_setup();
    physics_setup();
    setupWeaponprofiles();
    all_sprites.at(0).sprite_test();



    //champ en_1(1, (100 * 100 * 3 + 1), 100, 100);
    hero.sprite_nr = hero.Relation_Spritenr_type();
    // setup of the 4 sprites
    for (int i = 4; i < 8; i++){
        hero.current_form_info[i] = hero.Relation_Spritenr_type_dev( hero.current_form_info[-4+i]);

        hero.height = hero.current_form_info[9];
        hero.width = hero.current_form_info[8];
    }
        cout << hero.sprite_nr << endl;
    hero.setContactPoints();
    champ_setup(hero);
            hero.setX(20);
            hero.setY(100);
};

void game::setupWeaponprofiles(){


weaponProfile * obj = new weaponProfile(201, 202 ,10, 10);
gameWProfiles.push_back(*obj);
delete obj;

weaponProfile * obj2 = new weaponProfile(203, 204 ,10, 10);
gameWProfiles.push_back(*obj2);
delete obj2;

weaponProfile * obj3 = new weaponProfile(205, 206 ,10, 10);
gameWProfiles.push_back(*obj3);
delete obj3;

};

void game::setXYfactor() {
// This function will set the factors for x and y velocity for the created attacks
    switch (hero.gun_direction){

        case 1:
            x_factor = 0;
            y_factor = -1;
        break;
        case 2:
            x_factor = 1;
            y_factor = -1;
        break;
        case 3:
            x_factor = 1;
            y_factor = 0;
            //cout << "nr3" << endl;
        break;
        case 4:
            x_factor = 1;
            y_factor = 1;
        break;
        case 5:
            x_factor = 0;
            y_factor = 1;
        break;
        case 6:
        break;
        default:
        break;


    };

    if ( hero.current_sprite_direction == false ) {
        x_factor = x_factor*-1;
    } else {
    }


};


void game::createAttacks(button_input& parameter) {
// champ hero is part of the game object


    if ( parameter.getShootState() == true ) {
        //cout << "attack" << endl;
        setXYfactor();
        //cout << hero.gun_direction << endl;

        // need to correct velocity and position according to internal states

        int attack_to_create = 0;
            if ( hero.gun_direction == 2 || hero.gun_direction == 4 ) {
                attack_to_create = gameWProfiles.at(hero.current_gun).sprite_nr_rot;
            } else {
                attack_to_create = gameWProfiles.at(hero.current_gun).sprite_nr;
            }
        int attack_location_x = 0;
        int attack_location_y = 0;
        int attack_mirror = 0;

            //cout << " sprite_nr " << hero.gun_sprite_nr << " " << all_sprites.at( hero.gun_sprite_nr ).sprite_height << " " << all_sprites.at( hero.gun_sprite_nr ).sprite_widht << endl;
            switch ( hero.gun_direction ) {
                case 1:
                //cout << "mirror" <<  hero.x_mirror_gun << endl;
                //attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).sprite_height/2 -1 - 2 + 20;
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 - all_sprites.at( attack_to_create ).getHeight()/2 ;
                attack_location_y = hero.RSV_y_gun - all_sprites.at( hero.gun_sprite_nr ).getHeight() -1;
                //cout << hero.RSV_x_gun << "__" << all_sprites.at( hero.gun_sprite_nr ).sprite_height/2-2 << endl;
                break;
                case 2:
                //attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth() - 11;
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth() - all_sprites.at( attack_to_create ).getWidth();
                attack_location_y = hero.RSV_y_gun ;
                break;
                case 3:
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth() -1;
                attack_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 - all_sprites.at( attack_to_create ).getHeight()/2 - 1;
                break;
                case 4:
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth() - all_sprites.at( attack_to_create ).getWidth();
                attack_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight() - all_sprites.at( attack_to_create ).getHeight() ;
                break;
                case 5:
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 - all_sprites.at( attack_to_create ).getHeight()/2 ;
                attack_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight() -1;
                break;
                case 6:
                break;
                default:
                break;
            };
            // Attack mirror
            if ( hero.current_sprite_direction == false ) {
                if ( hero.rot_gun == 1 ) {

//                    if ( hero.gun_direction == 3 ) {
//                        attack_mirror = 2*(attack_location_x - hero.width/2-1) + all_sprites.at( hero.gun_sprite_nr ).getWidth() - all_sprites.at( attack_to_create ).getWidth() ;
//                    } else {
//                        attack_mirror = 2*(attack_location_x - hero.width/2-1) + all_sprites.at( attack_to_create ).getHeight() - 1;
//                    }
                    //attack_mirror = 2*(attack_location_x - hero.width/2-1) + all_sprites.at( hero.gun_sprite_nr ).getWidth() - all_sprites.at( attack_to_create ).getWidth() ;
                    attack_mirror = 2*(attack_location_x - hero.width/2-1) + all_sprites.at( attack_to_create ).getWidth() - 1;

                } else {
                }
                if ( hero.rot_gun == 2 ) {

                    if ( hero.gun_direction == 1 || hero.gun_direction == 5 ) {
                        attack_mirror = 2*(attack_location_x - hero.width/2) + all_sprites.at( attack_to_create ).getHeight() - 1;
                    } else {
                        //attack_mirror = 2*(attack_location_x - hero.width/2-1) + all_sprites.at( hero.gun_sprite_nr ).getHeight() - all_sprites.at( attack_to_create ).getHeight() - 1;
                        attack_mirror = 2*(attack_location_x - hero.width/2-1) + all_sprites.at( attack_to_create ).getHeight() - 1;
                    }

                } else {

                }


            } else {
                //cout << attack_location_x << "  " << hero.width/2 << endl;
                attack_mirror = 0;
            };

            attack_location_x = attack_location_x - attack_mirror;

        //cout << attack_location_x << endl;
        attack * obj = new attack(attack_to_create, hero.x_location+attack_location_x, hero.y_location+attack_location_y,
        gameWProfiles.at(hero.current_gun).x_vel*x_factor, gameWProfiles.at(hero.current_gun).y_vel*y_factor,
        hero.rot_gun, hero.horisontal_gun, hero.vertical_gun, hero.gun_sprite_nr );
        gameAttacks.push_back(*obj);
        delete obj;
    } else {
    };


    // if room switch true destroy all attacks
    //cout << "1  " << room_prev << " " << room_current << " " << game_room_switch() << endl;
    if ( game_room_switch() == true ) {

        for ( int i = 0; i < gameAttacks.size(); i++ ) {
            gameAttacks.at(i).destroy = true;
        }

    } else {
    };



    //update attacks
    for ( int i = 0; i < gameAttacks.size(); i++ ) {
        gameAttacks.at(i).update_and_render();
    }



    // removal from render req based on filter
    gameAttacks.erase(
    std::remove_if(gameAttacks.begin(), gameAttacks.end(),
    [](const attack & o) { return o.destroy == true; }),
    gameAttacks.end());

    //cout << gameAttacks.size() <<endl;

};

// Enemy manager function
void game::enemy_manager() {


    // Room 2
    if ( room_current == 2 && enemy_config == true ) {

        enemy * new_enemy_1 = new enemy(1);
        gameEnemys.push_back( *new_enemy_1 );
        delete new_enemy_1;


        enemy_config = false;
    } else {
    }


    for ( int i = 0 ; i < gameEnemys.size() ; i++ ) {
        gameEnemys.at(i).setRender();
    }

    // Remove destroyed enemies
    gameEnemys.erase(
    std::remove_if(gameEnemys.begin(), gameEnemys.end(),
    [](const enemy & o) { return o.destroy == true; }),
    gameEnemys.end());


};

// room switched true false

bool game::game_room_switch() {
    bool return_value = false;

    if ( room_current != room_prev ) {
        return_value = true;
    } else {
    }



    return return_value;

};

void game::portals_run_render() {


    for ( int i = 0; i < room_portals.at(room_current).portals.size() ; i++ ) {
        room_portals.at(room_current).portals.at(i).portal_render();
        room_portals.at(room_current).portals.at(i).transport(hero, room_current);
        //cout << room_portals.at(room_current).portals.size() << endl;
    }

};



void game::game_main(){


        hero.updateV( buttons, physics_objects.at( physics_current ) );
        hero.setPos(buttons, physics_objects.at( physics_current ));
        hero.setContact(room_current);
        hero.setRender();
        portals_run_render();
        createAttacks(buttons);

        // Enemy prototype
        enemy_manager();




        room_render_req(room_current); // in environment


        // audio prof of principle
        if ( buttons.getSelectState() == true ) {

//							audio.Play_FX(FX.at(0), 1);
                game_is_running = false;


        }


// room prev

room_prev = room_current;
};


void game::game_loop() {

    while ( game_is_running == true ) {
        auto start = std::chrono::system_clock::now();
        screen.render_clear();

        buttons.updateState();


        switch (game_state_current) {

            case 0:
                game_main();
            break;


            default:
            break;

        };
        screen.determine_current_offset(hero, room_current );

        //screen.filler_dev(room_current);
        screen.filler_general(room_current);
        game_frame();

        auto end = std::chrono::high_resolution_clock::now();
        elapsed_seconds = end-start;
        time = elapsed_seconds.count();
        time_ms = time * 1000;
            if ( time_ms < fps ) {
                usleep( (fps-time_ms) * 1000); //ms
            } else {

            }
            auto final_end = std::chrono::high_resolution_clock::now();
            elapsed_seconds = final_end-start;
            time = elapsed_seconds.count();
            //cout << time << ".\n";



        }
    };

//};

void game::game_fbp_clear() {
// clear the screen directly without going through the render buffer

    for (int i = 0; i < 240; i++) {
        for (int ii = 0; ii < 320*2;ii++){
            *((char*)(fbp + 1 +(ii + i*640))) = 0;
        }

    }

};

void game::game_frame() {
// produce image on the screen
//*( screen.render_array_pointer +i*320*2 + ii )

//    for (int i = 0; i < 240; i++) {
//        for (int ii = 0; ii < 320*2;ii++){
//            if ( *((char*)(fbp + 0 +(ii + i*640))) == screen.getColor(ii, i) ) {
//
//            } else {
//                *((char*)(fbp + 0 +(ii + i*640))) = screen.getColor(ii, i);
//            }
//
//
//        }
//
//    }

    for (int i = 0; i < 240; i++) {
        for (int ii = 0; ii < 320*2;ii++){

            if ( *((char*)(fbp + 0 +(ii + i*640))) == *( screen.render_array_pointer +i*320*2 + ii ) ) {

            } else {
                *((char*)(fbp + 0 +(ii + i*640))) = *( screen.render_array_pointer +i*320*2 + ii );
            }


        }

    }
//memset(fbp, 0xff, (240*320*2) );
//memcpy(fbp+1, screen.render_array_pointer, (240*320*2) );
};

