#ifndef OneColor_h
#define OneColor_h
#include "Animation.h"

class OneColor : public Animation {
  
public:
  OneColor(void);
  virtual void loop(variables_t *vars);
  virtual void reset(variables_t *vars, uint8_t def);

private:

};
#endif
