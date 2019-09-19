
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
//~ #include "enemy.h"
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
room_current = 2;
physics_current = 0;
game_is_running = true;

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


weaponProfile * obj = new weaponProfile(201, 10, 10);
gameWProfiles.push_back(*obj);
delete obj;
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
        cout << "attack" << endl;
        setXYfactor();
        cout << hero.gun_direction << endl;

        // need to correct velocity and position according to internal states

        attack * obj = new attack(gameWProfiles.at(hero.current_gun).sprite_nr, hero.x_location, hero.y_location, gameWProfiles.at(hero.current_gun).x_vel*x_factor, gameWProfiles.at(hero.current_gun).y_vel*y_factor);
        gameAttacks.push_back(*obj);
        delete obj;
    } else {
    };

    //cout << gameAttacks.size() <<endl;

    //update attacks
    for ( int i = 0; i < gameAttacks.size(); i++ ) {
        gameAttacks.at(i).update_and_render();
    }



    // removal from render req based on filter
    gameAttacks.erase(
    std::remove_if(gameAttacks.begin(), gameAttacks.end(),
    [](const attack & o) { return o.destroy == true; }),
    gameAttacks.end());

    cout << gameAttacks.size() <<endl;

};



void game::game_main(){


        hero.updateV( buttons, physics_objects.at( physics_current ) );
        hero.setPos(buttons, physics_objects.at( physics_current ));
        hero.setContact(room_current);

        createAttacks(buttons);
        room_render_req(room_current);

        hero.setRender();


        // audio prof of principle
        if ( buttons.getSelectState() == true ) {

//							audio.Play_FX(FX.at(0), 1);
                game_is_running = false;


        }



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

