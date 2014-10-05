#include <Adafruit_NeoPixel.h>
#include "OneColor.h"

OneColor::OneColor(void) { }

void OneColor::reset(variables_t *vars, uint8_t def) {
  vars->defColInPallet = def;
}

void OneColor::loop(variables_t *vars) {
  int i;
  for (i = 0; i < vars->color_len; i++) {//draw
     vars->color[i]=Animation::getColor(vars->defColInPallet, 1, vars->isCopper);
//     Adafruit_NeoPixel::Color(COLOR_PALLET_R[],COLOR_PALLET_G[vars->defColInPallet],COLOR_PALLET_B[vars->defColInPallet]);
  }
//  delay(5);
}
