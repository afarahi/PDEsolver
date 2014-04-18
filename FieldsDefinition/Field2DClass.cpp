#include "./Field2DClass.h"

Field2DClass::Field2DClass( ){
   xGridSize = 2;
   yGridSize = 2;
   Phi = new double[xGridSize*yGridSize];
   initPhi = new double[xGridSize*yGridSize];
   cout << "2D FIELD CONSTRUCTED SUCCESSFULLY !" << endl;
}
      
Field2DClass::~Field2DClass( ){
   delete [] Phi;
   delete [] initPhi;
   cout << "2D FIELD DECONSTRUCTED SUCCESSFULLY !" << endl;
}

bool Field2DClass::initialize( int xGridSizeInput, int yGridSizeInput,
                               double vxInput, double vyInput ){
  
   int maxFreq = 5;
  
   delete [] Phi;
   delete [] initPhi;
   double x, y, rndPhase1, rndPhase2;
     
   xGridSize = xGridSizeInput;
   yGridSize = yGridSizeInput;
   
   gridSize = xGridSize * yGridSize;

   Phi = new double[gridSize];
   initPhi = new double[gridSize];

   for (int i = 0; i < gridSize; i++){
      Phi[i] = 0.0;
   }

   for (int iFreq = 1; iFreq < maxFreq; iFreq++){

      for (int jFreq = 1; jFreq < maxFreq; jFreq++){

         rndPhase1 = (float)(rand()%1000) / 1000.0 * 2.0 * 3.14159;
         rndPhase2 = (float)(rand()%1000) / 1000.0 * 2.0 * 3.14159;

         for (int i = 0; i < gridSize; i++){
            x = (double)(i%xGridSize) + 0.5;
            y = (double)(i/xGridSize) + 0.5;

            Phi[i] += sin( 2.0 * iFreq * 3.14159 * x / (double)xGridSize 
                           + rndPhase1 )
                   * sin( 2.0 * jFreq * 3.14159 * y / (double)yGridSize
                          + rndPhase2 );
         }
      }
   }

   for (int i = 0; i < gridSize; i++){
      initPhi[i] = Phi[i];
   }

   vx = vxInput;
   vy = vyInput;

   return true;

}      


double Field2DClass::returnExactSolution (const double time,
                                         int xIndex, int yIndex) {
   
   xIndex = xIndex - (int) (vx * time);
   yIndex = yIndex - (int) (vy * time);
   tempTime = time;
   while ( xIndex < 0 ){
      xIndex += xGridSize;   
   }
   while ( xIndex >= xGridSize ){
      xIndex -= xGridSize;   
   }

   while ( yIndex < 0 ){
      yIndex += yGridSize;   
   }
   while ( yIndex >= yGridSize ){
      yIndex -= yGridSize;   
   }

   return initPhi[xIndex+xGridSize*yIndex];

}
