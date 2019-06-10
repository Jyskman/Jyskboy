#include <iostream>
#include "setup_sprites.h"
#include "sprite_objects.h"
#include <vector>
#include "render.h"

using namespace std;



int champ_v4_still_width = 25;
int champ_v4_still_height = 30;
int champ_v4_still_size = 25 * 30 * 3 + 1;
unsigned char champ_v4_still[25 * 30 * 2 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\000\000\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000"
 "\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\000\000\000\000\377\377\377\377\377\377\377\377\377\377\000\000\000"
 "\000\000\000\000\000,c\206\061\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\000\000\206\061\000\000\377\377\377\377\377\377"
 "\377\377\000\000,c,cY\316Y\316Y\316Y\316\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\000\000,c\206\061\000\000\000\000\377"
 "\377\000\000\206\061,c,cY\316Y\316Y\316Y\316\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000\206\061,c\206\061\206"
 "\061\000\000\000\000\206\061\206\061\206\061\206\061\206\061\206\061\000\000\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000"
 "\000\206\061\206\061,c\206\061\206\061\000\000\000\000\000\000\000\000\000\000\206\061\206\061\000\000\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\000\000\000\000\206\061\206\061,c,c\206\061\206\061\206\061\206\061\206\061\000\000"
 "\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\000\000\000\000\206\061\000\000\206\061\206\061\206\061,c\206\061\206\061\206\061\206"
 "\061\206\061\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\000\000\206\061\000\000\206\061\206\061\000\000\206\061\206\061\206\061"
 "\206\061\206\061\206\061\206\061\206\061\000\000\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\000\000\206\061,c\000\000\000\000\377\377"
 "\000\000\000\000,c\206\061\206\061\206\061\206\061\206\061\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
 "\000\000\377\377\377\377\000\000\206\061\206\061,c\000\000\377\377\377\377\377\377\377\377"
 "\000\000\000\000\000\000\000\000\000\000\000\000\206\061\262\224\262\224\262\224\262\224\262\224\206"
 "\061\000\000\377\377\377\377\000\000\206\061\206\061,c\000\000\377\377\377\377\377\377\377"
 "\377\000\000\206\061,c,c\000\000\206\061\206\061\206\061\262\224\262\224\262\224\262\224"
 "\206\061\000\000\377\377\000\000\206\061\206\061,c,c\000\000\377\377\377\377\377\377\000\000"
 "\000\000\206\061\206\061,c\000\000\000\000\000\000\206\061\206\061\206\061\206\061\206\061\206\061"
 "\000\000\377\377\000\000\206\061\206\061,c\000\000\377\377\377\377\377\377\377\377\000\000\000"
 "\000\000\000\206\061\206\061\000\000\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377"
 "\377\377\000\000\206\061\000\000\000\000\377\377\377\377\377\377\000\000\206\061\206\061\000\000"
 "\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\000\000\000\000\377\377\377\377\377\377\377\377\000\000\000\000\000\000\206\061"
 "\000\000\377\377\377\377\000\000\206\061\206\061\000\000\000\000\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\206\061\206\061"
 "\000\000\000\000\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\000\000\206\061\206\061\206\061"
 "\206\061,c\000\000\000\000\377\377\377\377\377\377\377\377\000\000,c\206\061\206\061\206"
 "\061\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000\206\061"
 "\206\061,c,c,c\000\000\377\377\377\377\377\377\377\377\377\377\000\000,c,c\206\061\206"
 "\061\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000\206\061\206\061"
 "\206\061,c,c\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000,c,c\206"
 "\061\206\061\206\061\000\000\377\377\377\377\377\377\377\377\377\377\000\000\206\061\206"
 "\061,c,c,c\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000,c,c,c,c"
 "\206\061\000\000\377\377\377\377\377\377\377\377\000\000\206\061\206\061\206\061\206\061"
 "\206\061,c\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000"
 "\206\061\206\061\206\061\206\061\000\000\377\377\377\377\377\377\377\377\000\000\000\000\000"
 "\000\000\000\000\000\206\061\206\061\000\000\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\000\000\206\061\206"
 "\061\206\061\206\061,c\000\000\206\061\000\000\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\000\000,c\206\061\206\061\206\061\206\061\000\000\377\377\000\000\206\061"
 "\206\061,c,c,c,c,c\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377"
 "\000\000,c,c,c,c,c\206\061\206\061\000\000\000\000\206\061\206\061\206\061\206\061\206\061\206"
 "\061\206\061\206\061\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000"
 "\206\061\206\061\206\061\206\061\206\061\206\061\206\061\000\000\000\000\000\000\000\000\000\000\000\000"
 "\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000"
 "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000");



#define TEST_WIDTH (15)
#define TEST_HEIGHT (7)
#define TEST_BYTES_PER_PIXEL (2) /* 2:RGB16, 3:RGB, 4:RGBA */
#define TEST_PIXEL_DATA ((unsigned char*) TEST_pixel_data)
int block_4_width = 15;
int block_4_height = 7;
int block_4_size = 15 * 7 * 2 + 1;
unsigned char block_4[15 * 7 * 2 + 1] =
("\036\357\036\377\377\377\377\377\377\036\357\036\036\357\036\001\000\001\000\001\000\000\000\000\000"
 "\000\000\000\000\000\000\001\200\005\000\001\200\005\200\005\000\001\200\005c\037c\037c\037c\037\000\001\000\001\200"
 "\005\000\001\377\377c\037\000\001\377\377c\037\000\001\377\377\377\377\377\377c\037c\037\377"
 "\377\377\377\200\005\200\005\377\377c\037\000\001\377\377c\037c\037\000\001\000\001\377\377\377"
 "\377\000\001\377\377\377\377c\037c\037\377\377\000\001c\037\377\377\377\377c\037\000\001\000"
 "\001\377\377\377\377c\037\000\001\377\377c\037\377\377\377\377\377\377c\037\377\377"
 "\000\001\000\001\000\001\377\377\377\377\377\377c\037c\037\377\377c\037\377\377\377\377\377"
 "\377\377\377\377\377\000\001\377\377\377\377\377\377\377\377\377\377c\037\377\377"
 "\377\377c\037c\037");


int block_5_width = 15;
int block_5_height = 15;
int block_5_size = 15 * 15 * 2 + 1;
unsigned char block_5[15 * 15 * 2 + 1] =
("\025f\025\025f\025\025f\025\036\357\036\036\357\036\037c\037c\037\354`\003\033\354`\003\033\354"
 "`c\037\"\023\"\023\"\023\"\023\"\023`\336\"\023\"\023\"\023\"\023\"\023\"\023\"\023c\037"
 "c\037\"\023\"\023\"\023`\336`\336\"\023`\336`\336`\336\"\023\300\331\"\023\"\023c"
 "\037c\037\"\023\"\023\"\023`\336\300\331`\336`\336`\336`\336`\336\300\331\"\023"
 "\"\023c\037c\037\"\023\"\023\"\023`\336\300\331\300\331`\336`\336`\336\300\331\300"
 "\331\"\023\"\023c\037c\037\"\023\"\023`\336`\336`\336`\336\300\331\300\331\300\331"
 "\300\331\300\331`\336\"\023\"\023c\037\"\023\"\023`\336`\336`\336\300\331\300\331"
 "`\336\300\331`\336\300\331\300\331\"\023\"\023c\037\"\023`\336`\336`\336`\336"
 "\300\331\300\331`\336`\336`\336`\336\300\331\300\331\"\023c\037\"\023`\336`\336"
 "`\336`\336\300\331\300\331`\336`\336`\336\300\331`\336\"\023\"\023c\037\"\023"
 "`\336`\336`\336`\336\300\331\300\331`\336\300\331\300\331\300\331`\336c\037"
 "c\037c\037`\336`\336\300\331\300\331`\336\300\331\300\331`\336\300\331\300\331"
 "`\336`\336c\037\"\023c\037\"\023\"\023\"\023`\336`\336\300\331\300\331`\336`\336"
 "`\336\"\023\"\023c\037\"\023c\037\"\023\"\023\"\023`\336`\336\300\331\300\331`\336"
 "`\336\"\023\"\023\"\023c\037c\037c\037\"\023\"\023\"\023\"\023\300\331\300\331`\336"
 "`\336\300\331\"\023\"\023\"\023c\037c\037c\037c\037c\037\"\023\"\023\"\023`\336`\336"
 "\"\023\300\331\"\023\"\023\"\023c\037c\037");


int block_6_width = 7;
int block_6_height = 15;
int block_6_size = 15 * 7 * 2 + 1;
unsigned char block_6[15 * 7 * 2 + 1] =
("\013J!\013J!\013I\000I\011H@\002\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001"
 "I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I"
 "\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001"
 "I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I\001I"
 "\001I\001I\001I\001I\001I\001I\001I\001I");



std::vector<sprite_objects> all_sprites;
std::vector<sprite_objects*> sprite_pointers;


void setup_sprites(render& parameter) {



    sprite_objects block4(1, (unsigned char*)block_4 ,block_4, block_4_size, block_4_width, block_4_height,1);
    all_sprites.push_back(block4);
    sprite_pointers.push_back(&block4);

    sprite_objects champ_body_still_v4(1,(unsigned char*)champ_v4_still , champ_v4_still, champ_v4_still_size, champ_v4_still_width, champ_v4_still_height,100 );
    all_sprites.push_back(champ_body_still_v4);
    sprite_pointers.push_back(&champ_body_still_v4);

    sprite_objects block5(1, (unsigned char*)block_5 ,block_5, block_5_size, block_5_width, block_5_height,3);
    all_sprites.push_back(block5);
    sprite_pointers.push_back(&block5);

    sprite_objects block6(1, (unsigned char*)block_6 ,block_6, block_6_size, block_6_width, block_6_height,2);
    all_sprites.push_back(block6);
    sprite_pointers.push_back(&block6);

    for (int i = 0; i < all_sprites.size(); i++) {
        all_sprites.at(i).Relation_Spritenr_type();

    }


// Will attempt to implement another principle of drawing, bypassing the use of global vector variables
// render could contain pointers


parameter.load_sprite_data((unsigned char*)block_4, block_4_width, block_4_height );
parameter.load_sprite_data((unsigned char*)champ_v4_still, champ_v4_still_width, champ_v4_still_height );
parameter.load_sprite_data((unsigned char*)block_5, block_5_width, block_5_height );
parameter.load_sprite_data((unsigned char*)block_6, block_6_width, block_6_height );
};
