#ifndef BouncingAnimation_h
#define BouncingAnimation_h
#include "Animation.h"

class BouncingAnimation : public Animation {
  
public:
  BouncingAnimation(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

};
#endif
