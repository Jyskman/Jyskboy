
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

#include <chrono>
#include <ctime>
using namespace std;


char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

int fbfd = 0;
struct fb_var_screeninfo orig_vinfo;
long int screensize = 0;





game::game(int a) : buttons(1), screen(1), audio() {


// when game is created these items are also
game_state_current = 0;
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
    vinfo.bits_per_pixel = 8;
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

setup_sprites();
all_sprites.at(0).sprite_test();
room_setup();
champ en_1(1, (100 * 100 * 3 + 1), 100, 100);
};

void game::game_main(){





		 // will want to pass the sprite object vector/or the specific sprite?
//		en_1.setX(100);
//		en_1.setY(100);

        room_render_req();


        if ( buttons.getShootState() == true ) {

//							audio.Play_FX(FX.at(0), 1);
                game_is_running = false;

        }

//			for (int i = 0; i < 10; i++) {
//				usleep(100 * 1000); //ms
//				buttons.updateState();
//					//~ if ( buttons.getJumpstate() == 1 ) {
//						//~ printf("1");
//					//~ } else {
//						//~ printf("0");
//					//~ }
//					buttons.printAll();
//					//audio.Play_Music();
//					if ( buttons.getShootState() == true ) {
//
//							audio.Play_FX(FX.at(0), 1);
//
//					}
//					if ( buttons.getJumpState() == true ) {
//
//							audio.Play_FX(FX.at(3), 2);
//
//					}
//
//			}


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
        screen.filler_general();
        game_frame();
        auto end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        float time = elapsed_seconds.count();
        float time_ms = time * 1000;
            if ( time_ms < fps ) {
                usleep( (fps-time_ms) * 1000); //ms
            } else {

            }
            auto final_end = std::chrono::system_clock::now();
            elapsed_seconds = final_end-start;
            time = elapsed_seconds.count();
            cout << " MS " << time << ".\n";



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
    for (int i = 0; i < 240; i++) {
        for (int ii = 0; ii < 320*2;ii++){
            *((char*)(fbp + 1 +(ii + i*640))) = screen.getColor(ii, i);

        }

    }

};
