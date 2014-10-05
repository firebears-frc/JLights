#ifndef Words_h
#define Words_h
#include "Animation.h"

class Words : public Animation {
  
public:
  Words(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

    /*,
  sine[] = { // Brightness table for ecto effect
    0, 28, 96, 164, 192, 164, 96, 28, 0, 28, 96, 164, 192, 164, 96, 28 }*/;

};
#endif
