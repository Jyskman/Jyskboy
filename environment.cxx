
#include <iostream>
#include <vector>
#include "environment.h"
#include "render.h"

using namespace std;




block::block(int x_pos, int y_pos, int palette, int type) {

x_location = x_pos;
y_location = y_pos;
current_palette = palette;
block_type = type;

};


void block::render_request(){

render_requests * obj = new render_requests(block_type, x_location, y_location);

render_req.push_back(*obj);
delete obj;
};
