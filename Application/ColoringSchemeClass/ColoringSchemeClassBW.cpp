#include "ColoringSchemeClassBW.h"

void ColoringSchemeClassBW::value2RGB(double value, double minV, double maxV,
                     int &R, int &G, int &B){

   R = (int)(( (value-minV) / (maxV-minV) * 255 ));
   G = R;
   B = R;
   
}

