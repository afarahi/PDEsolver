#ifndef __COLORING_SCHEME_CLASS_HOT__
#define __COLORING_SCHEME_CLASS_HOT__

#include "ColoringSchemeClass.h"

class ColoringSchemeClassHot:public ColoringSchemeClass{

   public:
      
      void value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B);

   private:

};


#endif
