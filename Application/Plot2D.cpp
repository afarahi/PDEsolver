#include <algorithm>

#include "Plot2D.h"
#include "ui_Plot2DWindow.h"
#include <QtGui>
#include <iostream>

using namespace std;

Plot2DWindow::Plot2DWindow(QWidget *parent):
                           QMainWindow(parent),ui(new Ui::Plot2DWindow){
   ui->setupUi(this);
   paint = new QPainter;
   setMinimumSize(20, 20);
}

Plot2DWindow::~Plot2DWindow(){
   delete phiMatrix;
   delete image;
   delete paint;
   delete ui;
   cout << "Freeing mem" << endl;
}

void Plot2DWindow::paintEvent(QPaintEvent *){

   int R, G, B;
   int i = 0,j = 0;

   double max_ele, min_ele;

   // Get min and max value from the Phi Matrix
   max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));
   
   //paint = new QPainter;
   paint->begin(this);
   
   // Set Image width, height and color to RGB2555
   image = new QImage(picWidth,picHeight,QImage::Format_ARGB32_Premultiplied);
   QRgb value;
   
   for(i=0;i<picHeight;i++)
   {
      for(j=0;j<picWidth;j++)
      {
         R = (int)((phiMatrix[j+i*picWidth]-min_ele)/(max_ele-min_ele)*255);
         G = 255 - R;
         B = abs(128 - R);
         value = qRgb(R, G, B);
         image->setPixel(j, i, value);
      }
   }
   //image->scaled(200,200, Qt::IgnoreAspectRatio);
   paint->drawImage(10,10, *image);
   paint->end();
   
}

bool Plot2DWindow::initialCondition(int width, int height)
{
   picWidth = width;
   picHeight = height;
   resize(picWidth+20,picHeight+20);
   return true;
}

void Plot2DWindow::showResult(double *Phi)
{
   phiMatrix = Phi;
}

