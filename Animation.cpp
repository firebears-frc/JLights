#define NO_COLORS
#include "Animation.h"
#include <Adafruit_NeoPixel.h>

//                                              50xr 32xr 21.25xr 34xr 32xr 32xr
const uint8_t COLOR_PALLET_R[]={255,  220, 175,  255, 220,  255, 220,  175,255,  0,   0, 255};
const uint8_t COLOR_PALLET_G[]={7,    1,   1,    1,   0,    0,   1,    0,  5,   0,  255, 255};
const uint8_t COLOR_PALLET_B[]={2,    1,   1,    0,   1,    1,   0,    1,  1,  20,    0, 255};

/** 
 * Abstract Animation class.
 */
Animation::Animation() { }

void Animation::loop(Adafruit_NeoPixel strip, variables_t *var) { }
void Animation::reset(variables_t *var) { }
uint32_t Animation::getColor(int i, double div, uint8_t isCopper) {
  div = div * (isCopper+1);
  return Adafruit_NeoPixel::Color(COLOR_PALLET_G[i]/div, COLOR_PALLET_R[i]/div, COLOR_PALLET_B[i]/div);
}
