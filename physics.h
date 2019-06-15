#ifndef PHYS
#define PHYS





class physics {

public:
float g[10] = {0.9,0,0,0,0,0,0,0,0,0};
physics();

void setState(int param);
float getG(int state);
int state;

float air_resistance[10];
//float g[10];

};









#endif // PHYS
