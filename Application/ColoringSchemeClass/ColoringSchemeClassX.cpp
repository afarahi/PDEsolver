#include "ColoringSchemeClassX.h"

void ColoringSchemeClassX::value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B){

   R = (int)(( (value-minV) / (maxV-minV) * 255 ));
   B = (int)(( 255 - (value-minV) / (maxV-minV) * 255 ));
   G = 0.0;

   /*
   R = (int)(( (value-minV) / (maxV-minV) * 255 ) + 85);
   if ( R > 255 ){
      R -= 255;
   }
   G = R + 85;
   if ( G > 255 ){
      G -= 255;
   }
   B = G + 85;
   if ( B > 255 ){
      B -= 255;
   }
   */
}

