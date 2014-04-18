#ifndef __COLORING_SCHEME_CLASS_X__
#define __COLORING_SCHEME_CLASS_X__

#include "ColoringSchemeClass.h"

class ColoringSchemeClassX:public ColoringSchemeClass{

   public:
      
      void value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B);

   private:

};


#endif
