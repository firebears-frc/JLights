#ifndef BlinkAnimation_h
#define BlinkAnimation_h
#include "Animation.h"

class BlinkAnimation : public Animation {
  
public:
  BlinkAnimation(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

};
#endif
