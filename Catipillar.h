#ifndef Catipillar_h
#define Catipillar_h
#include "Animation.h"

class Catipillar : public Animation {
  
public:
  Catipillar(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars);

private:

};
#endif
