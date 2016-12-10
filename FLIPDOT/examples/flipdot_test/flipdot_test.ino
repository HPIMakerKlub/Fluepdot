#include <FLIPDOT.h>


#define Y1 2 // *NOT* inverted in HW
#define Y2 3
#define Y3 4
#define CLOCK 5 // inverted in HW
#define SELECT 6 // inverted in HW
#define RESET 7 // inverted in HW
#define CLEAR 8 // *NOT* inverted in HW

int mapping[20] = {Y1,Y2,Y3,0,0,0,0,0,0,0,0,0,0,0,0,0,CLEAR,SELECT,CLOCK,RESET};

FLIPDOT bvg = FLIPDOT(mapping);
int16_t buffa[25] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int16_t buffb[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void setup() {

}

void loop() {
  
  bvg.render_frame(buffa);
  delay(100);
  bvg.render_frame(buffb);

}
