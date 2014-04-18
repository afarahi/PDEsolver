#include "ColoringSchemeClassHot.h"

void ColoringSchemeClassHot::value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B){

   R = (int)(( (value-minV) / (maxV-minV) * 255 )) + 100;
   G = R - 100;
   if ( R > 255){
      R = 255;	   
   }
   B = (int)(( (log(value - minV + 1)) / log( maxV - minV + 1) * 255 ))
        - 150;
   if ( B < 0){
      B = 0;	   
   }
}

