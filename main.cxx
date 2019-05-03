

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

// flatpak run org.gimp.GIMP//stable
// 'global' variables to store screen info
char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;




// flatpak run org.gimp.GIMP//stable
// GIT commands
// git add --all && git commit -m "comment"
// git push -u origin master


// application entry point
int main(int argc, char* argv[])
{
wiringPiSetup () ;



    int fbfd = 0;
    struct fb_var_screeninfo orig_vinfo;
    long int screensize = 0;


    // Open the file for reading and writing
    fbfd = open("/dev/fb1", O_RDWR);
    if (!fbfd) {
      printf("Error: cannot open framebuffer device.\n");
      return(1);
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
    else {
        // draw... Here prog begin //////////////////////////7

        render screen(1);
        button_input buttons(1);
        setup_sprites();
		all_sprites.at(0).sprite_test();



		champ en_1(1, (100 * 100 * 3 + 1), 100, 100); // will want to pass the sprite object vector/or the specific sprite?
		en_1.setX(200);
		en_1.setY(100);
        en_1.setRender();

		soundmanager audio;

        block b1(60, 60, 1, 1);
        b1.setRender();


		screen.clear();

		//screen.filler_dev(en_1);
        screen.filler_general();

			// clear fbp - will remove when screen clear works
			for (int i = 0; i < 240; i++) {
				for (int ii = 0; ii < 320*2;ii++){
					*((char*)(fbp + 1 +(ii + i*640))) = 0;
				}

			}

			// Render
			for (int i = 0; i < 240; i++) {
				for (int ii = 0; ii < 320*2;ii++){
					*((char*)(fbp + 1 +(ii + i*640))) = screen.getColor(ii, i);

				}

			}



			for (int i = 0; i < 100; i++) {
				usleep(100 * 1000); //ms
				buttons.updateState();
					//~ if ( buttons.getJumpstate() == 1 ) {
						//~ printf("1");
					//~ } else {
						//~ printf("0");
					//~ }
					buttons.printAll();
					audio.Play_Music();
					if ( buttons.getShootState() == true ) {

							audio.Play_FX(FX.at(0), 1);

					}
					if ( buttons.getJumpState() == true ) {

							audio.Play_FX(FX.at(3), 2);

					}

			}




    }


    // cleanup
    Close_audio();

    munmap(fbp, screensize);
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
        printf("Error re-setting variable information.\n");
    }
    close(fbfd);

    return 0;

}




// End
