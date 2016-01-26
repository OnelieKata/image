#ifndef YUV_H
#define YUV_H

#include <QRgb>

class Yuv
{
    int y;
    int u;
    int v;

public :

    Yuv();
    Yuv(QRgb pixel);
    int getY();
    int getU();
    int getV();


}; // class Yuv


#endif // YUV_H
