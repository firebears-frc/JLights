#ifndef FireBearsAnimation_h
#define FireBearsAnimation_h
#include "Animation.h"

class FireBearsAnimation : public Animation {
  
public:
  FireBearsAnimation(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

};
#endif
