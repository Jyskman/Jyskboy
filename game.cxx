
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

#include<list>



#include "test.h"

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
    room_setup( this );
    physics_setup();
    setupWeaponprofiles();
    setup_animation_profiles();
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
            hero.setX(30);
            hero.setY(30);
};

void game::setup_animation_profiles() {
// configure animation patterns
animation_profile * obj = new animation_profile(2, 10, 0, 7);
animation_profiles.push_back(*obj);
delete obj;

animation_profile * obj_2 = new animation_profile(2, 11, 0, 8);
animation_profiles.push_back(*obj_2);
delete obj_2;

animation_profile * obj_3 = new animation_profile(2, 12, 0, 8);
animation_profiles.push_back(*obj_3);
delete obj_3;

animation_profile * obj_4 = new animation_profile(2, 13, 0, 8);
animation_profiles.push_back(*obj_4);
delete obj_4;

//load the pattern of the first animation profile @0
animation_profiles.at(0).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(0);
//animation_profiles.at(0).load_animate_to_cycle(10);
animation_profiles.at(0).load_animate_main_index(501);
animation_profiles.at(0).load_animate_sub_index_1(0);
animation_profiles.at(0).load_animate_physics(false);
animation_profiles.at(0).load_animate_duo(true);


animation_profiles.at(0).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(10);
//animation_profiles.at(0).load_animate_to_cycle(20);
animation_profiles.at(0).load_animate_main_index(502);
animation_profiles.at(0).load_animate_sub_index_1(0);
animation_profiles.at(0).load_animate_physics(false);
animation_profiles.at(0).load_animate_duo(true);


animation_profiles.at(0).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(20);
//animation_profiles.at(0).load_animate_to_cycle(30);
animation_profiles.at(0).load_animate_main_index(503);
animation_profiles.at(0).load_animate_sub_index_1(0);
animation_profiles.at(0).load_animate_physics(false);
animation_profiles.at(0).load_animate_duo(true);


animation_profiles.at(0).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(30);
//animation_profiles.at(0).load_animate_to_cycle(40);
animation_profiles.at(0).load_animate_main_index(504);
animation_profiles.at(0).load_animate_sub_index_1(0);
animation_profiles.at(0).load_animate_physics(false);
animation_profiles.at(0).load_animate_duo(true);


animation_profiles.at(0).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(40);
//animation_profiles.at(0).load_animate_to_cycle(50);
animation_profiles.at(0).load_animate_main_index(505);
animation_profiles.at(0).load_animate_sub_index_1(0);
animation_profiles.at(0).load_animate_physics(false);
animation_profiles.at(0).load_animate_duo(true);


// // // // // // // // // // // //
//load the pattern of the second animation profile @0
animation_profiles.at(1).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(0);
//animation_profiles.at(0).load_animate_to_cycle(10);
animation_profiles.at(1).load_animate_main_index(506);
animation_profiles.at(1).load_animate_sub_index_1(0);
animation_profiles.at(1).load_animate_physics(false);
animation_profiles.at(1).load_animate_duo(false);
animation_profiles.at(1).load_animate_quad(true);

animation_profiles.at(1).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(10);
//animation_profiles.at(0).load_animate_to_cycle(20);
animation_profiles.at(1).load_animate_main_index(507);
animation_profiles.at(1).load_animate_sub_index_1(0);
animation_profiles.at(1).load_animate_physics(false);
animation_profiles.at(1).load_animate_duo(false);
animation_profiles.at(1).load_animate_quad(true);

animation_profiles.at(1).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(20);
//animation_profiles.at(0).load_animate_to_cycle(30);
animation_profiles.at(1).load_animate_main_index(508);
animation_profiles.at(1).load_animate_sub_index_1(0);
animation_profiles.at(1).load_animate_physics(false);
animation_profiles.at(1).load_animate_duo(false);
animation_profiles.at(1).load_animate_quad(true);

animation_profiles.at(1).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(20);
//animation_profiles.at(0).load_animate_to_cycle(30);
animation_profiles.at(1).load_animate_main_index(509);
animation_profiles.at(1).load_animate_sub_index_1(0);
animation_profiles.at(1).load_animate_physics(false);
animation_profiles.at(1).load_animate_duo(false);
animation_profiles.at(1).load_animate_quad(true);

// // // // // // // // // // // //
//load the pattern of the third animation profile @0
animation_profiles.at(2).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(0);
//animation_profiles.at(0).load_animate_to_cycle(10);
animation_profiles.at(2).load_animate_main_index(510);
animation_profiles.at(2).load_animate_sub_index_1(0);
animation_profiles.at(2).load_animate_physics(false);
animation_profiles.at(2).load_animate_duo(false);
animation_profiles.at(2).load_animate_quad(true);

animation_profiles.at(2).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(10);
//animation_profiles.at(0).load_animate_to_cycle(20);
animation_profiles.at(2).load_animate_main_index(511);
animation_profiles.at(2).load_animate_sub_index_1(0);
animation_profiles.at(2).load_animate_physics(false);
animation_profiles.at(2).load_animate_duo(false);
animation_profiles.at(2).load_animate_quad(true);

animation_profiles.at(2).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(20);
//animation_profiles.at(0).load_animate_to_cycle(30);
animation_profiles.at(2).load_animate_main_index(512);
animation_profiles.at(2).load_animate_sub_index_1(0);
animation_profiles.at(2).load_animate_physics(false);
animation_profiles.at(2).load_animate_duo(false);
animation_profiles.at(2).load_animate_quad(true);

animation_profiles.at(2).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(20);
//animation_profiles.at(0).load_animate_to_cycle(30);
animation_profiles.at(2).load_animate_main_index(513);
animation_profiles.at(2).load_animate_sub_index_1(0);
animation_profiles.at(2).load_animate_physics(false);
animation_profiles.at(2).load_animate_duo(false);
animation_profiles.at(2).load_animate_quad(true);

// V small explosion
//load the pattern of the 4th animation profile @0
animation_profiles.at(3).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(0);
//animation_profiles.at(0).load_animate_to_cycle(10);
animation_profiles.at(3).load_animate_main_index(514);
animation_profiles.at(3).load_animate_sub_index_1(0);
animation_profiles.at(3).load_animate_physics(false);
animation_profiles.at(3).load_animate_duo(false);
animation_profiles.at(3).load_animate_quad(true);

animation_profiles.at(3).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(10);
//animation_profiles.at(0).load_animate_to_cycle(20);
animation_profiles.at(3).load_animate_main_index(515);
animation_profiles.at(3).load_animate_sub_index_1(0);
animation_profiles.at(3).load_animate_physics(false);
animation_profiles.at(3).load_animate_duo(false);
animation_profiles.at(3).load_animate_quad(true);

animation_profiles.at(3).load_animate_type(1); // type 1 simple
//animation_profiles.at(0).load_animate_from_cycle(20);
//animation_profiles.at(0).load_animate_to_cycle(30);
animation_profiles.at(3).load_animate_main_index(516);
animation_profiles.at(3).load_animate_sub_index_1(0);
animation_profiles.at(3).load_animate_physics(false);
animation_profiles.at(3).load_animate_duo(false);
animation_profiles.at(3).load_animate_quad(true);


// setup for animations
animation_profiles.at(0).set_sprite_numbers();
animation_profiles.at(0).set_to_from_cycles(2);

animation_profiles.at(1).set_sprite_numbers();
animation_profiles.at(1).set_to_from_cycles(2);

animation_profiles.at(2).set_sprite_numbers();
animation_profiles.at(2).set_to_from_cycles(2);

animation_profiles.at(3).set_sprite_numbers();
animation_profiles.at(3).set_to_from_cycles(2);
};

void game::setupWeaponprofiles(){


weaponProfile * obj = new weaponProfile(201, 202 ,10, 10, 1, 3);
gameWProfiles.push_back(*obj);
delete obj;

weaponProfile * obj2 = new weaponProfile(203, 204 ,10, 10, 1, 1);
gameWProfiles.push_back(*obj2);
delete obj2;

weaponProfile * obj3 = new weaponProfile(205, 206 ,10, 10, 1, 1);
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

        // casing variables and vel
        int ammo_location_x = 0;
        int ammo_location_y = 0;
        int ammo_v_x = -5;
        int ammo_v_y = -3;

        modifier_random(ammo_v_x, 2, 1);
        modifier_random(ammo_v_y, 2, 1);
        int ammo_mirror = 0;
        int animation_cycles_to_terminate = 40;


            //cout << " sprite_nr " << hero.gun_sprite_nr << " " << all_sprites.at( hero.gun_sprite_nr ).sprite_height << " " << all_sprites.at( hero.gun_sprite_nr ).sprite_widht << endl;
            switch ( hero.gun_direction ) {
                case 1:

                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 - all_sprites.at( attack_to_create ).getHeight()/2 ;
                attack_location_y = hero.RSV_y_gun - all_sprites.at( hero.gun_sprite_nr ).getHeight() -1;

                ammo_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2;
                ammo_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2+3;
                ammo_v_x = ammo_v_x;
                ammo_v_y = ammo_v_y*0;
                break;
                case 2:
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth() - all_sprites.at( attack_to_create ).getWidth();
                attack_location_y = hero.RSV_y_gun ;

                ammo_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth()/2;
                ammo_location_y =  hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 ;
                ammo_v_x = ammo_v_x;
                ammo_v_y = ammo_v_y;

                break;
                case 3:
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth() -1;
                attack_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 - all_sprites.at( attack_to_create ).getHeight()/2 - 1;

                ammo_location_x =  hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth()/2 ;
                ammo_location_y =  hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 ;
                ammo_v_x = ammo_v_x;
                ammo_v_y = ammo_v_y;

                break;
                case 4:
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth() - all_sprites.at( attack_to_create ).getWidth();
                attack_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight() - all_sprites.at( attack_to_create ).getHeight() ;

                ammo_location_x =  hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getWidth()/2 ;
                ammo_location_y =  hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 ;
                ammo_v_x = ammo_v_y ;
                ammo_v_y = ammo_v_x ;

                break;
                case 5:
                attack_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2 - all_sprites.at( attack_to_create ).getHeight()/2 ;
                attack_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight() -1;

                ammo_location_x = hero.RSV_x_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2;
                ammo_location_y = hero.RSV_y_gun + all_sprites.at( hero.gun_sprite_nr ).getHeight()/2+3;
                ammo_v_x = ammo_v_y;
                ammo_v_y = ammo_v_x;

                break;
                case 6:
                break;
                default:
                break;
            };
            // Attack mirror
            if ( hero.current_sprite_direction == false ) {
                ammo_v_x = ammo_v_x*-1;
                ammo_mirror = 2*(ammo_location_x - hero.width/2-1);
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

            bool cross = false;
            //cout << hero.rot_gun << endl;
            if ( hero.gun_direction == 2 || hero.gun_direction == 4 ) {
                cross = true;
            } else {
            };

            attack_location_x = attack_location_x - attack_mirror;
            ammo_location_x = ammo_location_x - ammo_mirror;
        //cout << hero.y_velocity << endl;
        attack * obj = new attack(attack_to_create,gameWProfiles.at(hero.current_gun).damage, hero.x_location+attack_location_x, hero.y_location+attack_location_y,
        gameWProfiles.at(hero.current_gun).x_vel*x_factor, gameWProfiles.at(hero.current_gun).y_vel*y_factor,
        hero.rot_gun, hero.horisontal_gun, hero.vertical_gun, hero.gun_sprite_nr, cross, hero.current_sprite_direction, gameWProfiles.at(hero.current_gun).hitbox_t );
        gameAttacks.push_back(*obj);
        delete obj;

        //render_primitive_line(hero.x_location+ammo_location_x, hero.y_location+ammo_location_y, hero.x_location+ammo_location_x+5, hero.y_location+ammo_location_y-5, 1, 401  );

        modifier_random(animation_cycles_to_terminate, 10,10);

        animation_requests * obj_2 = new animation_requests( 0 ,2, hero.rot_gun, hero.horisontal_gun,true , animation_cycles_to_terminate , hero.x_location+ammo_location_x , hero.y_location+ammo_location_y,
        ammo_v_x+(int)hero.x_velocity, ammo_v_y+hero.y_velocity );
        anime_req.push_back(*obj_2);
        delete obj_2;

//        animation_requests * obj_3 = new animation_requests(1, 50, hero.x_location+ammo_location_x+1 , hero.y_location+ammo_location_y,
//        ammo_v_x+(int)hero.x_velocity, ammo_v_y+hero.y_velocity );
//        anime_req.push_back(*obj_3);
//        delete obj_3;

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


    if ( (game_room_switch() == true) || initial_config == true ) {


        create_and_reset_enemies(room_current, gameEnemys);



    } else {
    }


    for ( int i = 0 ; i < gameEnemys.size() ; i++ ) {
        gameEnemys.at(i).resolve_damage( gameAttacks, hero );
        gameEnemys.at(i).setRender();

        gameEnemys.at(i).perception(hero);
        gameEnemys.at(i).motion( physics_objects.at( physics_current ) ) ;// here is error big

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

// compare function for sorting the animation vector
bool comparefunction_anim( animation_requests &a , animation_requests &b ) {
//
//    if ( a.x != b.x ) {
//    return false;
//    }
//
//    if ( a.y != b.y ) {
//    return false;
//    }

    if ( a.x != b.x && a.y != b.y && a.x_v != b.x_v && a.y_v != b.y_v ) {
    return false;
    }


    return true;

};

// compare function for sorting the animation vector
bool compare_entry_anim( const animation_requests & e1, const animation_requests & e2) {
  if( e1.x != e2.x)
    return (e1.x < e2.x);
  return (e1.y < e2.y);
}


void game::animations_run_render() {

    //cout << " size before " << anime_req.size() << endl;

//    sort( anime_req.begin(), anime_req.end(), compare_entry_anim );
//
//    anime_req.erase( unique(anime_req.begin(), anime_req.end(), comparefunction_anim ), anime_req.end()   );

    //cout << " size after " << anime_req.size() << endl;

    for ( int i = 0; i < anime_req.size(); i++ ) {

        anime_req.at(i).render_animation();
        anime_req.at(i).update_position( physics_objects.at( physics_current), room_current );
    };


    // Remove animations
    anime_req.erase(
    std::remove_if(anime_req.begin(), anime_req.end(),
    [](const animation_requests & o) { return o.destroy == true; }),
    anime_req.end());


};

// checklim function below
void game::check_lim() {



//~ cout << "lim check" << room_objects.at(room_current).limits.at(0).x_down_right << endl;

	for (int i = 0; i < room_objects.at(room_current).limits.size(); i++) {
		
		// if inside x-bounds
		if ( (int)hero.x_center > room_objects.at(room_current).limits.at(i).x_down_left && (int)hero.x_center < room_objects.at(room_current).limits.at(i).x_up_right  ) {
			// if inside y bound
			if ( (int)hero.y_center > room_objects.at(room_current).limits.at(i).y_down_left && (int)hero.y_center < room_objects.at(room_current).limits.at(i).y_up_right ) {
				//~ cout << "trigger" << endl;
				//~ the set lim values will be set to that of the lim box identified by this condition
				

				room_objects.at(room_current).xlim_low_set = room_objects.at(room_current).limits.at(i).x_down_left_set;
				room_objects.at(room_current).ylim_low_set = room_objects.at(room_current).limits.at(i).y_down_left_set;
				room_objects.at(room_current).xlim_up_set = room_objects.at(room_current).limits.at(i).x_up_right_set;
				room_objects.at(room_current).ylim_up_set = room_objects.at(room_current).limits.at(i).y_up_right_set;
				
				current_lim = i;
				
				
			} else {
			};
			
			
			
		} else {
		

		};
		
		
	}
	
	
	
	
};

// upon room switch the game will reset and correct the limits
void game::check_lim_upon_roomswitch() {
	
	//cout << " current _" << room_current << endl;
	
	if ( game_room_switch() == true ) {
	
			for (int i = 0; i < room_objects.at(room_current).limits.size(); i++) {
				
				// if inside x-bounds
				if ( (int)hero.x_location > room_objects.at(room_current).limits.at(i).x_down_left && (int)hero.x_location < room_objects.at(room_current).limits.at(i).x_up_right  ) {
					// if inside y bound
					if ( hero.y_location > room_objects.at(room_current).limits.at(i).y_down_left && hero.y_location < room_objects.at(room_current).limits.at(i).y_up_right ) {
						cout << "trigger" << endl;
						//~ the set lim values will be set to that of the lim box identified by this condition
						room_objects.at(room_current).xlim_low_set = room_objects.at(room_current).limits.at(i).x_down_left_set;
						room_objects.at(room_current).ylim_low_set = room_objects.at(room_current).limits.at(i).y_down_left_set;
						room_objects.at(room_current).xlim_up_set = room_objects.at(room_current).limits.at(i).x_up_right_set;
						room_objects.at(room_current).ylim_up_set = room_objects.at(room_current).limits.at(i).y_up_right_set;
						
					} else {
					};

				} else {

				};
				
			};
			
			room_objects.at(room_current).xlim_low = hero.x_location - 160;
			room_objects.at(room_current).xlim_up = hero.x_location + 160;

			room_objects.at(room_current).ylim_low = hero.y_location - 200;
			room_objects.at(room_current).ylim_up = hero.y_location + 200;

			if ( room_objects.at(room_current).ylim_low < room_objects.at(room_current).ylim_low_set ) {
				room_objects.at(room_current).ylim_low = room_objects.at(room_current).ylim_low_set;

			} else {
			}; 
			if ( room_objects.at(room_current).ylim_up > room_objects.at(room_current).ylim_up_set ) {
				room_objects.at(room_current).ylim_up = room_objects.at(room_current).ylim_up_set;

			} else {
			};
			if ( room_objects.at(room_current).xlim_low < room_objects.at(room_current).xlim_low_set ) {
				room_objects.at(room_current).xlim_low = room_objects.at(room_current).xlim_low_set;

			} else {
			}; 
			if ( room_objects.at(room_current).xlim_up > room_objects.at(room_current).xlim_up_set ) {
				room_objects.at(room_current).xlim_up = room_objects.at(room_current).xlim_up_set;

			} else {
			};
	
	
	
	} else {
	};


	
};


void game::game_main(){


        if ( hero.hero_life > 0 ) {
            createAttacks(buttons);
            hero.updateV( buttons, physics_objects.at( physics_current ) );
            hero.setPos(buttons, physics_objects.at( physics_current ));
            hero.setContact(room_current);


        }
        hero.setRender(buttons, physics_objects.at( physics_current ), room_current );
		check_lim();


        

        portals_run_render();




        room_render_req(room_current); // in environment
		enemy_manager();

		animations_run_render();


       roomblocks_attack_interaction(room_current, gameAttacks);


        // audio prof of principle
        if ( buttons.getSelectState() == true ) {

//							audio.Play_FX(FX.at(0), 1);
                game_is_running = false;


        }


// room prev
cout << game_room_switch() << endl;
check_lim_upon_roomswitch();
//~ room_objects.at(room_current).update_limits_upon_room_switch(hero, game_room_switch(), screen );
room_prev = room_current;
initial_config = false;
};


void game::game_loop() {

//testfunc();

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

