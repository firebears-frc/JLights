#ifndef Glowing_h
#define Glowing_h
#include "Animation.h"

class Glowing : public Animation {
  
public:
  Glowing(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

};
#endif
