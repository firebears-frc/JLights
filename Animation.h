#ifndef Animation_h
#define Animation_h
#include <Adafruit_NeoPixel.h>

typedef struct{
  uint8_t anim_type; // which animation is being used on strip
  uint8_t isCopper;
  uint32_t *color; /** Array of colors for the pulsing pixels. */
  uint32_t *color_store;
  uint8_t color_len; // how many pixels are on strip
  uint8_t *color_pos; //where each color is on bouncing animation
  uint8_t *color_hom; //where each color originally was on bouncing animation
  uint8_t *color_dir; //where each color is facing on bouncing animation
  uint8_t objectCount; //how many objects in bouncing animation
//  uint8_t *colorPalletR; //array of predefined colors for use in animations
//  uint8_t *colorPalletG; //array of predefined colors for use in animations
//  uint8_t *colorPalletB; //array of predefined colors for use in animations
  uint8_t progress; // progress of moving pixels in FireBears Anim & CatchFire Anim
  uint8_t time; //time passed for catching fire
  uint8_t isSparking; //whether fire is sparking in catching fire
  uint8_t isPausing; //whether fire is not showing in catching fire
  uint8_t toQuit; //whether should turn to fb anim from cf anim
  uint32_t lastTime; //last time run
  uint32_t SLastTime; //switching animation last time
  boolean reset; //whether animation needs to call reset
  uint8_t mode;
  uint8_t defColInPallet; //default color in pallet
  char Goto_Anim;
}variables_t;

/**
 * Abstract parent class for other animation classes.
 */
class Animation {
public:
  Animation();
  virtual void loop(Adafruit_NeoPixel strip, variables_t *vars);
  virtual void reset(variables_t *vars);
  virtual uint32_t getColor(int i, double div, uint8_t isCopper);
};

#endif
