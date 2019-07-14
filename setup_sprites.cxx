#include <iostream>
#include "setup_sprites.h"
#include "sprite_objects.h"
#include <vector>
#include "render.h"

using namespace std;



int champ_v4_still_width = 25;
int champ_v4_still_height = 30;
int champ_v4_still_size = 25 * 30 * 2 + 1;
unsigned char champ_v4_still[25 * 30 * 2 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\"\203\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\"\203\"\203\377\377\377\377\377\377\377"
 "\377\377\377\"\203\"\203\"\203\"\203\342\307\241\353\"\203\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\""
 "\203\241\353\"\203\377\377\377\377\377\377\377\377\"\203\342\307\342\307\000"
 "\370\000\370\000\370\000\370\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\"\203\342\307\241\353\"\203\"\203\377"
 "\377\"\203\241\353\342\307\342\307\000\370\000\370\000\370\000\370\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\""
 "\203\241\353\342\307\241\353\241\353\"\203\"\203\241\353\241\353\241\353\241"
 "\353\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\342\307\241"
 "\353\241\353\"\203\"\203\"\203\"\203\"\203\241\353\241\353\"\203\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\"\203\"\203\241\353\241\353\342\307\342\307\241\353\241\353\241\353\241\353"
 "\241\353\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\"\203\"\203\241\353\"\203\241\353\241\353\241\353"
 "\342\307\241\353\241\353\241\353\241\353\241\353\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353"
 "\"\203\241\353\241\353\"\203\241\353\241\353\241\353\241\353\241\353\241\353"
 "\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\"\203\241\353\342\307\"\203\"\203\377\377\"\203"
 "\"\203\342\307\241\353\241\353\241\353\241\353\241\353\"\203\"\203\"\203\""
 "\203\"\203\"\203\"\203\"\203\377\377\377\377\"\203\241\353\241\353\342\307"
 "\"\203\377\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203\"\203"
 "\241\353\000\370\000\370\000\370\000\370\000\370\241\353\"\203\377\377\377\377\"\203"
 "\241\353\241\353\342\307\"\203\377\377\377\377\377\377\377\377\"\203\241\353"
 "\342\307\342\307\"\203\241\353\241\353\241\353\000\370\000\370\000\370\000\370\241"
 "\353\"\203\377\377\"\203\241\353\241\353\342\307\342\307\"\203\377\377\377"
 "\377\377\377\"\203\"\203\241\353\241\353\342\307\"\203\"\203\"\203\241\353"
 "\241\353\241\353\241\353\241\353\241\353\"\203\377\377\"\203\241\353\241\353"
 "\342\307\"\203\377\377\377\377\377\377\377\377\"\203\"\203\"\203\241\353\241"
 "\353\"\203\377\377\377\377\"\203\"\203\"\203\"\203\"\203\"\203\"\203\377\377"
 "\377\377\"\203\241\353\"\203\"\203\377\377\377\377\377\377\"\203\241\353\241"
 "\353\"\203\"\203\"\203\"\203\"\203\"\203\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\"\203\"\203\377\377\377\377\377\377\377"
 "\377\"\203\"\203\"\203\241\353\"\203\377\377\377\377\"\203\241\353\241\353"
 "\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\"\203\"\203\"\203\"\203\241\353\241\353\"\203\"\203\377\377\377\377"
 "\377\377\377\377\"\203\"\203\"\203\"\203\"\203\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\241\353\241\353"
 "\342\307\"\203\"\203\377\377\377\377\377\377\377\377\"\203\342\307\241\353"
 "\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\"\203\241\353\241\353\342\307\342\307\342\307\"\203\377\377\377\377\377"
 "\377\377\377\377\377\"\203\342\307\342\307\241\353\241\353\"\203\377\377\377"
 "\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\241\353\342\307"
 "\342\307\"\203\377\377\377\377\377\377\377\377\377\377\377\377\"\203\342\307"
 "\342\307\241\353\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377"
 "\377\"\203\241\353\241\353\342\307\342\307\342\307\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\"\203\342\307\342\307\342\307\342\307\241\353"
 "\"\203\377\377\377\377\377\377\377\377\"\203\241\353\241\353\241\353\241\353"
 "\241\353\342\307\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\"\203\241\353\241\353\241\353\241\353\"\203\377\377\377\377\377\377\377"
 "\377\"\203\"\203\"\203\"\203\"\203\241\353\241\353\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203"
 "\377\377\377\377\377\377\"\203\241\353\241\353\241\353\241\353\342\307\241"
 "\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\"\203\342\307\241\353\241\353\241\353\241\353\"\203\377\377\"\203\241\353"
 "\241\353\342\307\342\307\342\307\342\307\342\307\"\203\"\203\377\377\377\377"
 "\377\377\377\377\377\377\377\377\"\203\342\307\342\307\342\307\342\307\342"
 "\307\241\353\241\353\"\203\"\203\241\353\241\353\241\353\241\353\241\353\241"
 "\353\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377"
 "\"\203\241\353\241\353\241\353\241\353\241\353\241\353\241\353\"\203\"\203"
 "\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203"
 "\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377");



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


 //* GIMP RGB C-Source image dump (champ_v3_torso.c) */
int champ_torso_width = 25;
int champ_torso_height = 17;
int champ_torso_size = 25 * 17 * 2 + 1;
unsigned char champ_torso[25 * 17 * 2 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\"\203\"\203\"\203\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\377\377"
 "\377\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\342\307\241\353\""
 "\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\"\203\241\353\"\203\377\377\377\377\377\377\377\377\"\203"
 "\342\307\342\307\000\370\000\370\000\370\000\370\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\342\307\241\353"
 "\"\203\"\203\377\377\"\203\241\353\342\307\342\307\000\370\000\370\000\370\000\370"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\"\203\241\353\342\307\241\353\241\353\"\203\"\203\241\353\241"
 "\353\241\353\241\353\241\353\241\353\"\203\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241"
 "\353\342\307\241\353\241\353\"\203\"\203\"\203\"\203\"\203\241\353\241\353"
 "\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\"\203\"\203\241\353\241\353\342\307\342\307\241\353\241"
 "\353\241\353\241\353\241\353\"\203\"\203\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203"
 "\241\353\241\353\241\353\342\307\241\353\241\353\241\353\241\353\241\353\""
 "\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\241"
 "\353\241\353\241\353\241\353\241\353\241\353\"\203\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\"\203\"\203\342\307\241\353\241\353\241\353\241"
 "\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\"\203\"\203\"\203\"\203\"\203\"\203\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\"\203"
 "\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\"\203\"\203\"\203\"\203\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241"
 "\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377");

 // legs champ

int champ_legs_width = 25;
int champ_legs_height = 17;
int champ_legs_size = 25 * 17 * 2 + 1;
unsigned char champ_legs[25 * 17 * 2 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\""
 "\203\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\"\203\"\203\241\353\241\353\342\307\"\203\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\""
 "\203\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\"\203\241\353\241\353\"\203\"\203\"\203\"\203\"\203\""
 "\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\"\203\241\353"
 "\"\203\377\377\377\377\"\203\241\353\241\353\"\203\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203"
 "\241\353\241\353\"\203\"\203\377\377\377\377\377\377\377\377\"\203\"\203\""
 "\203\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\"\203\241\353\241\353\241\353\241\353\342\307\"\203\"\203\377\377\377"
 "\377\377\377\377\377\"\203\342\307\241\353\241\353\241\353\"\203\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\342\307"
 "\342\307\342\307\"\203\377\377\377\377\377\377\377\377\377\377\"\203\342\307"
 "\342\307\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377"
 "\377\"\203\241\353\241\353\241\353\342\307\342\307\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\"\203\342\307\342\307\241\353\241\353\241\353"
 "\"\203\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\342\307"
 "\342\307\342\307\"\203\377\377\377\377\377\377\377\377\377\377\377\377\"\203"
 "\342\307\342\307\342\307\342\307\241\353\"\203\377\377\377\377\377\377\377"
 "\377\"\203\241\353\241\353\241\353\241\353\241\353\342\307\"\203\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353\241\353\241\353"
 "\241\353\"\203\377\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203"
 "\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\"\203\"\203\"\203\"\203\"\203\377\377\377\377\377\377\"\203\241"
 "\353\241\353\241\353\241\353\342\307\241\353\241\353\"\203\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\"\203\342\307\241\353\241\353\241"
 "\353\241\353\"\203\377\377\377\377\"\203\241\353\342\307\342\307\342\307\342"
 "\307\342\307\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\""
 "\203\342\307\342\307\342\307\342\307\342\307\241\353\"\203\377\377\377\377"
 "\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203\377\377\377\377\377"
 "\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377");

int champ_jump_width = 25;
int champ_jump_height = 17;
int champ_jump_size = 25 * 17 * 2 + 1;
unsigned char champ_jump[25 * 17 * 2 + 1] =
 ("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\""
 "\203\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\"\203\"\203\241\353\241\353\342\307\"\203\"\203\"\203\"\203"
 "\"\203\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\"\203\"\203\"\203\241\353"
 "\241\353\"\203\"\203\"\203\342\307\241\353\241\353\241\353\"\203\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\"\203\241\353\241\353\"\203\"\203\"\203\"\203\"\203\"\203\342\307\342\307"
 "\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\"\203\"\203\241\353\"\203\377\377\377"
 "\377\377\377\377\377\"\203\342\307\342\307\241\353\241\353\241\353\"\203\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203"
 "\"\203\"\203\"\203\377\377\377\377\377\377\377\377\377\377\"\203\342\307\342"
 "\307\342\307\342\307\241\353\"\203\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203\377\377\377"
 "\377\377\377\377\377\377\377\"\203\241\353\241\353\241\353\241\353\"\203\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203"
 "\241\353\241\353\241\353\241\353\"\203\377\377\377\377\377\377\377\377\377"
 "\377\"\203\"\203\"\203\"\203\"\203\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\"\203\241\353\241\353\342\307\342\307\"\203"
 "\377\377\377\377\377\377\377\377\"\203\342\307\241\353\241\353\241\353\241"
 "\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241"
 "\353\241\353\241\353\342\307\342\307\"\203\377\377\377\377\377\377\"\203\342"
 "\307\342\307\342\307\342\307\342\307\241\353\"\203\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\"\203\241\353\241\353\342\307\342\307\342"
 "\307\"\203\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203\"\203\"\203"
 "\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241\353"
 "\241\353\241\353\241\353\342\307\"\203\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\"\203\"\203\"\203\"\203\"\203\241\353\241"
 "\353\"\203\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\"\203\241"
 "\353\241\353\241\353\241\353\342\307\241\353\241\353\"\203\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\"\203\241\353\342\307\342\307\342\307"
 "\342\307\342\307\"\203\"\203\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203\"\203\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377");


int champ_gun_width = 18;
int champ_gun_height = 8;
int champ_gun_size = 18 * 8 * 2 + 1;
unsigned char champ_gun[18 * 8 * 2 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\241\273\241\273\241\273\241\273\241\273\241\273\241\273\241\273\241\273\241"
 "\273\241\273\241\273\241\273\241\273\241\273\377\377\377\377\377\377\241\273"
 "\210\355\210\355\210\355\210\355\210\355\210\355\210\355\210\355\210\355\210"
 "\355\210\355\210\355\210\355\210\355\241\273\377\377\377\377\241\273\210\355"
 ".\366.\366.\366\276w\206\212\276w\210\355\276w\276w\276w\276w\276w\210\355"
 "\241\273\377\377\377\377\241\273\241\273\241\273\241\273\241\273\241\273\241"
 "\273\241\273\210\355.\366.\366.\366.\366.\366\210\355\241\273\377\377\377"
 "\377\241\273\241\273\241\273\241\273\241\273\241\273\241\273\241\273\241\273"
 "\241\273\241\273\241\273\241\273\241\273\210\355\241\273\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\241\273\241\273"
 "\241\273\241\273\241\273\241\273\241\273\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377");

int champ_gun_up_width = 8;
int champ_gun_up_height = 18;
int champ_gun_up_size = 18 * 8 * 2 + 1;
unsigned char champ_gun_up[8 * 18 * 2 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\241\273\241\273\241\273\241\273\377\377\377\377\377\377\241\273\210\355"
 "\210\355\210\355\210\355\241\273\377\377\377\377\241\273\210\355\276w.\366"
 "\241\273\241\273\377\377\377\377\241\273\210\355\276w.\366\241\273\241\273"
 "\377\377\377\377\241\273\210\355\276w.\366\241\273\241\273\377\377\377\377"
 "\241\273\210\355\276w.\366\241\273\241\273\377\377\377\377\241\273\210\355"
 "\276w.\366\241\273\241\273\377\377\377\377\241\273\210\355.\366.\366\241\273"
 "\241\273\377\377\377\377\241\273\210\355\276w\241\273\241\273\377\377\377"
 "\377\377\377\241\273\210\355\206\212\241\273\241\273\377\377\377\377\377\377"
 "\241\273\210\355\276w\241\273\241\273\377\377\377\377\377\377\241\273\210"
 "\355.\366\241\273\241\273\377\377\377\377\377\377\241\273\210\355.\366\241"
 "\273\241\273\377\377\377\377\377\377\241\273\210\355.\366\241\273\241\273"
 "\377\377\377\377\377\377\241\273\210\355\210\355\241\273\241\273\377\377\377"
 "\377\377\377\241\273\241\273\241\273\241\273\241\273\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377");

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

    sprite_objects champtorso(1, (unsigned char*)champ_torso ,champ_torso, champ_torso_size, champ_torso_width, champ_torso_height,101);
    all_sprites.push_back(champtorso);
    sprite_pointers.push_back(&champtorso);

    sprite_objects champlegs(1, (unsigned char*)champ_legs ,champ_legs, champ_legs_size, champ_legs_width, champ_legs_height,102);
    all_sprites.push_back(champlegs);
    sprite_pointers.push_back(&champlegs);

    sprite_objects champjump(1, (unsigned char*)champ_jump ,champ_jump, champ_jump_size, champ_jump_width, champ_jump_height,103);
    all_sprites.push_back(champjump);
    sprite_pointers.push_back(&champjump);

    sprite_objects champgun(1, (unsigned char*)champ_gun ,champ_gun, champ_gun_size, champ_gun_width, champ_gun_height,104);
    all_sprites.push_back(champgun);
    sprite_pointers.push_back(&champgun);

    sprite_objects champgunup(1, (unsigned char*)champ_gun_up ,champ_gun_up, champ_gun_up_size, champ_gun_up_width, champ_gun_up_height,105);
    all_sprites.push_back(champgunup);
    sprite_pointers.push_back(&champgunup);

    for (int i = 0; i < all_sprites.size(); i++) {
        all_sprites.at(i).Relation_Spritenr_type();

    }


// Will attempt to implement another principle of drawing, bypassing the use of global vector variables
// render could contain pointers


parameter.load_sprite_data((unsigned char*)block_4, block_4_width, block_4_height );
parameter.load_sprite_data((unsigned char*)champ_v4_still, champ_v4_still_width, champ_v4_still_height );
parameter.load_sprite_data((unsigned char*)block_5, block_5_width, block_5_height );
parameter.load_sprite_data((unsigned char*)block_6, block_6_width, block_6_height );
parameter.load_sprite_data((unsigned char*)champ_torso, champ_torso_width, champ_torso_height );
parameter.load_sprite_data((unsigned char*)champ_legs, champ_legs_width, champ_legs_height );
parameter.load_sprite_data((unsigned char*)champ_jump, champ_jump_width, champ_jump_height );
parameter.load_sprite_data((unsigned char*)champ_gun, champ_gun_width, champ_gun_height );
parameter.load_sprite_data((unsigned char*)champ_gun_up, champ_gun_up_width, champ_gun_up_height );
};
