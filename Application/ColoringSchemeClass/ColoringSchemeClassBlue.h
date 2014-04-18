#ifndef __COLORING_SCHEME_CLASS_BLUE__
#define __COLORING_SCHEME_CLASS_BLUE__

#include "ColoringSchemeClass.h"

class ColoringSchemeClassBlue:public ColoringSchemeClass{

   public:
      
      void value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B);

   private:

};


#endif
