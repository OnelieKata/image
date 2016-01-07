#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <QImage>
#include <QLabel>
#include <QString>
#include <iostream>

using namespace std;
int main (int argc, char* argv[])
{
    QApplication a(argc, argv);

    QLabel myLabel;
    QImage myImage;

    myImage.load("/tmp/blackbuck.ppm");
    uchar * truc = myImage.bits();
    QRgb    pix;

    cout << endl << "profondeur :        " << myImage.depth() << endl;

    for (int y = 0; y < myImage.height(); ++y)
    {
       for (int x = 0; x < myImage.width(); ++x)
       {

             pix = myImage.pixel(x, y);
             cout << endl << qBlue(pix) << "   " << qGreen(pix) << "   " << qRed(pix);
             cout << "         " << int(*(truc++));
             cout << "   "  << int(*(truc++));
             cout << "   " << int(*(truc++)) << endl;
             truc++;    // pour l'alpha
             myImage.setPixel(x,y,qRgb(255-qRed(pix),255-qGreen(pix),255-qBlue(pix)));
          }
       }

/*
    //myImage.load("/home/tiretfa/Bureau/test/Mario_(New_Super_Mario_Bros._2).png");
     //myImage.load("/home/tiretfa/Documents/imageProjet/Image/test/
    //myImage.load("/home/tiretfa/Documents/imageProjet/Image/test/P4220687.jpg");

    QImage img;
    img.load("/tmp/blackbuck.ppm");
    myLabel.setPixmap(QPixmap::fromImage(img));
    myLabel.show();
    for (int y = 0; y < img.height(); y++) {
        QRgb* rgb = (QRgb*)img.scanLine(y); // Il faut que l'image soit en ARGB32 (je pense, voir la doc)
        for (int x = 0; x < img.width(); x++) {
            rgb[x] = qRgba(255 - qRed(rgb[x]), 255 - qGreen(rgb[x]), 255 - qBlue(rgb[x]), qAlpha(rgb[x]));
        }
    }
    img.save("machin.png");
*/

     myLabel.setPixmap(QPixmap::fromImage(myImage));
     myLabel.show();

  return a.exec();
}
