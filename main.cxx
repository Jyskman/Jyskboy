

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

// main game
#include "game.h"

// flatpak run org.gimp.GIMP//stable
// 'global' variables to store screen info
//char *fbp = 0;
//struct fb_var_screeninfo vinfo;
//struct fb_fix_screeninfo finfo;




// flatpak run org.gimp.GIMP//stable
// GIT commands
// git add --all && git commit -m "comment"
// git push -u origin master


// application entry point
int main(int argc, char* argv[])
{

 wiringPiSetup ();
        game game1(1);
        game1.game_setup();
        game1.game_loop();

        game1.game_close();
        game1.~game();
    return 0;

}




// End
