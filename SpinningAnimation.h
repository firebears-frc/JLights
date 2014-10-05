#ifndef SpinningAnimation_h
#define SpinningAnimation_h
#include "Animation.h"

/**
 * Animation class that causes a single pixel to just move forward.
 * On an LED ring, the light will spin around.
 */
class SpinningAnimation : public Animation {
public:
  SpinningAnimation(Adafruit_NeoPixel strip);
  virtual void loop(Adafruit_NeoPixel strip);
  
  /** Color of the spinning pixel */
  uint32_t _color;
  
  /** Milliseconds for the pixel to travel across all the pixels. */
  unsigned long _time_delay;

private:
  unsigned long _timeout;
  uint32_t _black;
  int _current_pixel;
};
#endif
