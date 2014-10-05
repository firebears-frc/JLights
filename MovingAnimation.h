#ifndef MovingAnimation_h
#define MovingAnimation_h
#include "Animation.h"

class MovingAnimation : public Animation {
  
public:
  MovingAnimation(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

};
#endif
