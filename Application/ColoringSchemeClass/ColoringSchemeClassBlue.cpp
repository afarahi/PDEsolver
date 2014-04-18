#include "ColoringSchemeClassBlue.h"

void ColoringSchemeClassBlue::value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B){

   R = 0;
   G = 0;
   B = (int)(( (value-minV) / (maxV-minV) * 255 ));
   
}

