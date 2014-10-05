#include <Adafruit_NeoPixel.h>
#include "CatchFire.h"

CatchFire::CatchFire(void) { }

void CatchFire::reset(variables_t *vars) {
  vars->progress = 0;
  vars->time = 0;
  vars->isSparking = true;
  vars->isPausing = true;
  vars->toQuit = false;
  vars->lastTime = millis();
}

void CatchFire::loop(variables_t *vars) {
  int i;
//  Serial.println("burn");
  if((vars->isSparking == true) && (millis()>vars->lastTime+(160-(vars->time*3)))) {
//    Serial.println("eeeee");
    vars->lastTime = millis();
    if(vars->isPausing == true) {
      for (i = 0; i < vars->color_len; i++) {//draw
        vars->color[i]=Adafruit_NeoPixel::Color(0,0,0);
      }
      vars->isPausing = false;
//      Serial.println("pause");
    }else{
      for (i = 0; i < vars->color_len; i++) {//draw
        if(rand()%(8-(vars->time/2)) == 0) {
          vars->color[i]=Adafruit_NeoPixel::Color(255,255,255);
        }
      }
      vars->time++;
      if(vars->time > 14) {
        vars->isSparking = false;
        vars->time = 0;
      }
      vars->isPausing = true;
    }
  }else if((vars->isSparking == false) && (millis()>vars->lastTime+160)){
//    Serial.println("made it!");
    vars->lastTime = millis();
    int j;
    int div = 21-vars->time;
    vars->progress += 1;
    if(vars->progress > vars->color_len) {
      vars->progress = 0;
    }
    for (i = 0; i < vars->color_len; i++) {//draw
      vars->color[i] = Animation::getColor(rand()%9, div, vars->isCopper);
//      Adafruit_NeoPixel::Color(COLOR_PALLET_R[], COLOR_PALLET_G[rand()%9]/div, 0);
    }
/*    for (i = 0; i < vars->color_len/3; i++) {//draw
      vars->color[i] = strip.Color(vars->colorPalletR[rand()%3]/div, vars->colorPalletG[rand()%3]/div, 0);
      j = i + vars->progress;
      if(j >= vars->color_len) {
        j -= vars->color_len;
      }
      vars->color[j]=vars->color[i]);
    }*/
//    Serial.println("endraw!");
    vars->time++;
    if(vars->time >= 20) {
      vars->toQuit = true;
    }
//    Serial.println("todelay!");
  }
}
