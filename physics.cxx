
// Phys engine


#include <iostream>
#include <vector>

#include "physics.h"

physics::physics() {


state = 1;


};


void physics::setState(int param) {
    state = param;
};


float physics::getG(int state) {

return g[state];

};
