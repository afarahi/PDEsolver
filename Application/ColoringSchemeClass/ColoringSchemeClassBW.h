#ifndef __COLORING_SCHEME_CLASS_BW__
#define __COLORING_SCHEME_CLASS_BW__

#include "ColoringSchemeClass.h"

class ColoringSchemeClassBW:public ColoringSchemeClass{

   public:
      
      void value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B);

   private:

};


#endif
