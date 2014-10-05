#include <Adafruit_NeoPixel.h>
#include "Glowing.h"

Glowing::Glowing(void) { }

void Glowing::reset(variables_t *vars) {
  vars->lastTime = 0;
  vars->isPausing = false;
}

void Glowing::loop(variables_t *vars) {
  int k = millis()*10 % 127;
  int i;
  if(vars->lastTime > k) {
    if(vars->isPausing) {
      vars->isPausing = false;
    }else{
      vars->isPausing = true;
    }
  }
  vars->lastTime = k;
  if(vars->defColInPallet) { //red
    for (i = 0; i < vars->color_len; i++) {//draw
      if(vars->isPausing) {
        vars->color[i] = Adafruit_NeoPixel::Color(0,127-k,0);
      }else{
        vars->color[i] = Adafruit_NeoPixel::Color(0,k,0);
      }
    }
  }else{//blue alliance
    for (i = 0; i < vars->color_len; i++) {//draw    
      if(vars->isPausing) {
        vars->color[i] = Adafruit_NeoPixel::Color(0,0,127-k);
      }else{
        vars->color[i] = Adafruit_NeoPixel::Color(0,0,k);
      }
    }
  }
}
