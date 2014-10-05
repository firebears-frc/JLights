#include <Adafruit_NeoPixel.h>
#include "BouncingAnimation.h"

BouncingAnimation::BouncingAnimation(void) { }

void BouncingAnimation::reset(variables_t *vars) {
  Serial.println("changing to bounce");
  int i;
  boolean j = true;
  for(i = 0; i < vars->objectCount; i++) {
    vars->color_store[i] = Adafruit_NeoPixel::Color(0, rand()%64+128, 0);
    vars->color_pos[i] = i*5+2;
    vars->color_hom[i] = i*5+2;
    vars->color_dir[i] = j;
    j=!j;
  }
  vars->lastTime = 0;
}

void BouncingAnimation::loop(variables_t *vars) {
  int i = 0;
  int j = 0;
  if(millis() > vars->lastTime+50) {
    vars->lastTime = millis();
    for(i = 0; i < vars->objectCount; i++) {
      vars->color_store[i] = Adafruit_NeoPixel::Color(96, 127, 127);
    }
    for (i = 0; i < vars->color_len; i++) {//clear
      vars->color[i] = Adafruit_NeoPixel::Color(rand()%64+63,0,0);
    }
    for (i=0; i< vars->objectCount; i++) {//set
      for(j = 0; j < 2; j++) {
        if(vars->color_pos[i]+j < vars->color_len) {
          vars->color[vars->color_pos[i]+j]= vars->color_store[i];
        }
      }
    }
    for (i=0; i<vars->objectCount; i++) {//move
      if(vars->color_dir[i]) {
        vars->color_pos[i] = vars->color_pos[i]+1;
      }else{
        vars->color_pos[i] = vars->color_pos[i]-1;
      }
      if((vars->color_pos[i] >= vars->color_hom[i]+2) || (vars->color_pos[i] <= vars->color_hom[i]-2)) { vars->color_dir[i] = !vars->color_dir[i]; }
    }
  }
}
