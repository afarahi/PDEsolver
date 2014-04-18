#include <algorithm>

#include "Plot2D.h"
#include "ui_Plot2DWindow.h"
#include <QtGui>
#include <iostream>

using namespace std;

Plot2DWindow::Plot2DWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::Plot2DWindow){
   ui->setupUi(this);
   paint = new QPainter;
   coloringScheme = new ColoringSchemeClassBW;
   image = new QImage(1,1,QImage::Format_ARGB32_Premultiplied);
   paint = new QPainter(this);
}

Plot2DWindow::~Plot2DWindow(){
   delete phiMatrix;
   delete image;
   delete paint;
   delete ui;
}

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

void Plot2DWindow::paintEvent(QPaintEvent *){

   int R, G, B;
   int i = 0,j = 0;

   paint->begin(this);
   
   QRgb value;
   
   for(i=0;i<picHeight;i++){  
      for(j=0;j<picWidth;j++){
       
         coloringScheme->value2RGB(phiMatrix[j+i*picWidth], min_ele, max_ele, R, G, B);

         value = qRgb(R, G, B);
         image->setPixel(j, i, value);

      }
   }

   //*image = image->scaled(400,800, Qt::IgnoreAspectRatio);
   paint->drawImage(10,10, *image);
   paint->end();
   
}

bool Plot2DWindow::initialCondition(int width, int height)
{
   delete image;
   delete paint;
   
   picWidth = width;
   picHeight = height;
   this->setGeometry(100, 100,picWidth, picHeight);
   this->setMinimumSize(picWidth+20, picHeight+20);

   // Set Image width, height and color to RGB2555
   image = new QImage(picWidth,picHeight,QImage::Format_ARGB32_Premultiplied);
   paint = new QPainter(this);

   return true;
}

void Plot2DWindow::showResult(double *Phi)
{
   this->setWindowTitle(("PDE simulation 2D Plot Numerical Solution"));
   phiMatrix = Phi;
   // Get min and max value from the Phi Matrix
   max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));

}

void Plot2DWindow::showError(double* ExactPhi, double* NumericalPhi){
   
   this->setWindowTitle(("PDE simulation 2D Plot Error"));
   double *tempMatrix = new double[picHeight*picWidth];

   for(int i=0;i<picHeight;i++)
   {
      for(int j=0;j<picWidth;j++)
      {
         tempMatrix[j+i*picWidth] = (ExactPhi[j+i*picWidth] - NumericalPhi[j+i*picWidth]);
      }
   }

   phiMatrix = tempMatrix;
   max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));
   //delete tempMatrix;
}

