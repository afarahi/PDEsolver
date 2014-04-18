#include <algorithm>

#include "Plot2D.h"
#include "ui_Plot2DWindow.h"
#include <QtGui>
#include <iostream>

using namespace std;

// Draw 2D plot Error plot and numerical solution plot

Plot2DWindow::Plot2DWindow(QWidget *parent):
   QMainWindow(parent),ui(new Ui::Plot2DWindow){
   ui->setupUi(this);
   paint = new QPainter;
   coloringScheme = new ColoringSchemeClassBW;
   image = new QImage(1,1,QImage::Format_ARGB32_Premultiplied);
   colorBar = new QRectF(20,10,20,20);
   paint = new QPainter(this);
}

Plot2DWindow::~Plot2DWindow(){
   delete phiMatrix;
   delete image;
   delete paint;
   delete colorBar;
   delete ui;
}

// Choose different color scheme
void Plot2DWindow::setColoringScheme(string schemeName){
   delete coloringScheme;   
   if ( schemeName == "BlackWhite" ){
      coloringScheme = new ColoringSchemeClassBW;
   }
   else if ( schemeName == "Blue" ){
      coloringScheme = new ColoringSchemeClassBlue;
   }
   else if ( schemeName == "Colorful"){
      coloringScheme = new ColoringSchemeClassX;
   }
   else if ( schemeName == "Hot"){
      coloringScheme = new ColoringSchemeClassHot;
   }
   else{
      coloringScheme = new ColoringSchemeClassBW;	   
   }
}

// Automatically called during show the picture
void Plot2DWindow::paintEvent(QPaintEvent *){

   int R, G, B;
   int i = 0,j = 0;

   paint->begin(this);
   
   QRgb value, minRgb, maxRgb;;
   
   for(i=0;i<picHeight;i++){  
      for(j=0;j<picWidth;j++){
       
         coloringScheme->value2RGB(phiMatrix[j+i*picWidth],
                                   min_ele, max_ele, R, G, B);

         value = qRgb(R, G, B);
         image->setPixel(j, i, value);

      }
   }

   //*image = image->scaled(400,800, Qt::IgnoreAspectRatio);
   paint->drawImage(10,10, *image);
   
   // Draw a color bar.
   QLinearGradient linearGrad(QPointF(picWidth + 30, 10),
                              QPointF(picWidth + 30, 10+picHeight));
   
   // Match the color scheme
   int numIntervals = 7;
   double labelSize = (max_ele - min_ele)/numIntervals;
   double textSize = picHeight/numIntervals;
   coloringScheme->value2RGB(min_ele, min_ele, max_ele, R, G, B);
   minRgb = qRgb(R, G, B);
   QColor minColor(minRgb);
   coloringScheme->value2RGB(max_ele, min_ele, max_ele, R, G, B);
   maxRgb = qRgb(R,G,B);
   QColor maxColor(maxRgb);
   
   linearGrad.setColorAt(0, minRgb);
   linearGrad.setColorAt(1, maxRgb);
   QBrush brush(linearGrad);
   paint->fillRect(*colorBar, brush);
   
   for (int i = 0; i <= numIntervals; i++)
   {
      QString labelNum = QString::number(min_ele + i * labelSize,'g',4);
      paint->drawText(QPointF(picWidth+20+20,15+i * textSize), labelNum);
   }

   paint->end();
   
}


bool Plot2DWindow::initialCondition(int width, int height)
{
   delete image;
   delete paint;
   delete colorBar;
   
   picWidth = width;
   picHeight = height;
   this->setGeometry(100, 100,picWidth+130, picHeight);
   this->setMinimumSize(picWidth+20, picHeight+20);

   // Set Image width, height and color to RGB2555
   image = new QImage(picWidth,picHeight,QImage::Format_ARGB32_Premultiplied);
   paint = new QPainter(this);
   colorBar = new QRectF(picWidth+20,10,20,picHeight);

   return true;
}


// Pass the calculated result to the plot
// Set the min and max of the whole picture.
void Plot2DWindow::showResult(double *Phi)
{
   this->setWindowTitle(("PDE simulation 2D Plot Numerical Solution"));
   phiMatrix = Phi;
   // Get min and max value from the Phi Matrix
   max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));

}

// Pass the calculated error to the plot
// Set the min and max of the whole picture.
void Plot2DWindow::showError(double* ExactPhi, double* NumericalPhi){
   
   this->setWindowTitle(("PDE simulation 2D Plot Error"));
   double *tempMatrix = new double[picHeight*picWidth];

   for(int i=0;i<picHeight;i++)
   {
      for(int j=0;j<picWidth;j++)
      {
         tempMatrix[j+i*picWidth] = (ExactPhi[j+i*picWidth]
                                   - NumericalPhi[j+i*picWidth]);
      }
   }

   phiMatrix = tempMatrix;
   max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));
   //delete tempMatrix;
}

