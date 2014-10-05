#ifndef CatchingAnimation_h
#define CatchingAnimation_h
#include "Animation.h"

class CatchFire : public Animation {
  
public:
  CatchFire(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

};
#endif
