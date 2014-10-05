#include <Adafruit_NeoPixel.h>
#include "FireBearsAnimation.h"

FireBearsAnimation::FireBearsAnimation(void) { }

void FireBearsAnimation::reset(variables_t *vars) {
  Serial.println("changing to fire");
  vars->progress = 0;
  vars->lastTime = 0;
}

void FireBearsAnimation::loop(variables_t *vars) {
  if(millis()>vars->lastTime+100) {
    vars->lastTime = millis();
    int i;
    int j;
    int k;
    
    vars->progress = vars->progress+1;
    if(vars->progress > vars->color_len) {
      vars->progress = 0;
    }
    for (i = 0; i < vars->color_len; i++) {//draw
      k = rand()%9;
      vars->color[i] = Animation::getColor(k, 1, vars->isCopper);
      if(rand()%20 == 0) {
        vars->color[i] = Animation::getColor(11, 1, vars->isCopper);
      }
    }
  }
}
