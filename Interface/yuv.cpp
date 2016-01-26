
#include "Yuv.h"


Yuv::Yuv() :
    y(0),
    u(0),
    v(0)
{

}

Yuv::Yuv(QRgb pixel) :
    y(0),
    u(0),
    v(0)
{
        y=0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
        u=0.492*(qBlue(pixel)-y);
        v=0.877*(qRed(pixel)-y);

}

int Yuv::getY()
{
        return y;
}

int Yuv::getU()
{
        return u;
}

int Yuv::getV()
{
        return v;
}
