#ifndef __COLORING_SCHEME_CLASS_ABSTRACT__
#define __COLORING_SCHEME_CLASS_ABSTRACT__

#include <cmath>
#include <iostream>
using namespace std;

class ColoringSchemeClass{

   public:
         
      virtual void value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B) = 0;

      virtual ~ColoringSchemeClass(){
	  }

   private:

};

#include "./ColoringSchemeClassX.h"
#include "./ColoringSchemeClassBW.h"
#include "./ColoringSchemeClassHot.h"
#include "./ColoringSchemeClassBlue.h"

#endif
