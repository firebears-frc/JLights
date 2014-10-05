#include <Adafruit_NeoPixel.h>
#include "MovingAnimation.h"

MovingAnimation::MovingAnimation(void) { }

void MovingAnimation::reset(variables_t *vars) {
  Serial.println("changing to moving");
  int i;
  for(i = 0; i < vars->color_len; i++) {
    vars->color_store[i] = Adafruit_NeoPixel::Color(0, 0, rand()%64+64);
    vars->color_pos[i] = rand()%vars->color_len;
  }
  vars->lastTime = 0;
}

void MovingAnimation::loop(variables_t *vars) {
  int i;
  if(millis() > vars->lastTime + 25) {
    vars->lastTime = millis();
    for (i = 0; i < vars->color_len; i++) {//clear
      vars->color[i] = Adafruit_NeoPixel::Color(0,127,0);
    }
    for (i=0; i< vars->color_len; i++) {//set
      vars->color[vars->color_pos[i]] = vars->color_store[i];
    }
    for (i=0; i< vars->color_len; i++) {//move
      vars->color_pos[i] = vars->color_pos[i]+(rand()%2);
      if(vars->color_pos[i] > (vars->color_len-1)) { vars->color_pos[i] = vars->color_pos[i]-vars->color_len; }
    }
  }
}
