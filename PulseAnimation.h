#ifndef PulseAnimation_h
#define PulseAnimation_h
#include "Animation.h"

/*
 * Cause the NeoPixels to pulse between given colors and black.
 * We can define a list of colors.  Each pixel is time shifted a little
 * so it doesn't peak at the same time as its neighbors.
 */
class PulseAnimation : public Animation {
  
public:
  PulseAnimation(Adafruit_NeoPixel strip);
  virtual void loop(Adafruit_NeoPixel strip);

  /** Array of colors for the pulsing pixels. */
  uint32_t *_color;
  int _color_len;
  unsigned long _time_cycle;

private:
  int f(unsigned long t);
  uint32_t fadeColor(uint32_t c, int brightness);
};
#endif




