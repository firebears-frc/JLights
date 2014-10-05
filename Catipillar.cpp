#include <Adafruit_NeoPixel.h>
#include "Catipillar.h"

Catipillar::Catipillar(void) { }

void Catipillar::reset(variables_t *vars) {
  Serial.println("Changing To Blink");
  int i;
  uint8_t k;
  for(i = 0; i < vars->color_len; i++) {
    k = rand()%128;
    vars->color_store[i] = Adafruit_NeoPixel::Color(k,k,k);
  }
  vars->lastTime = 0;
}

void Catipillar::loop(variables_t *vars) {
  if(millis() > vars->lastTime+1) {
    vars->lastTime = millis();
    int i;
    for (i = 0; i < vars->color_len; i++) {//draw
      if(rand()%3) {
        vars->color[i] = Adafruit_NeoPixel::Color(2,0,2);
  //      strip.setPixelColor(i, strip.Color(0,0,0));
      }else{
        vars->color[i] = vars->color_store[i];
  //      strip.setPixelColor(i, strip.Color(vars->color[i],vars->color[i],vars->color[i]));
      }
    }
  }
}
