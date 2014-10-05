#include <Adafruit_NeoPixel.h>
#include "Words.h"

const int8_t PROGMEM
  fireBears[] = {
    1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1,
    1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1,
    1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1};

Words::Words(void) { }

void Words::reset(variables_t *vars) {

}

void Words::loop(variables_t *vars) {
  int prog = (millis()/500)%6;
  if(prog >= 5) {
    vars->toQuit = 1;
    return;
  }
  int i, j;
  for (i = 0; i < 30; i++) {//draw
    if(fireBears[i+(30*prog)]) {
      vars->color[i]=Animation::getColor(i,1, vars->isCopper);
    }else{
      vars->color[i]=Adafruit_NeoPixel::Color(0,0,0);
    }
  }
//  delay(5);
}
