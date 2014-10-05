#include <Adafruit_NeoPixel.h>
#include "SpinningAnimation.h"

SpinningAnimation::SpinningAnimation(Adafruit_NeoPixel strip) {
  _time_delay = 1000;
  _timeout = millis();
  _current_pixel = 0;
  _color = strip.Color(0, 64, 64);
  _black = strip.Color(0, 0, 0);
}

void SpinningAnimation::loop(Adafruit_NeoPixel strip) {
  unsigned long time_now = millis();
  if (time_now > _timeout) {
    strip.setPixelColor(_current_pixel, _black);
    _current_pixel = _current_pixel + 1;
    if (_current_pixel >= strip.numPixels()) {
      _current_pixel = 0; 
    }
    strip.setPixelColor(_current_pixel, _color);
    _timeout = time_now + (_time_delay / (strip.numPixels()));
  }
}

