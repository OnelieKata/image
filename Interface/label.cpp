#include "label.h"

Label::Label()
{

}

QPoint Label::getOrigin(){
    return origin;
}

QPoint Label::getPoint(){
    return point;
}

void Label::mousePressEvent(QMouseEvent *event){
    origin=event->pos();
    if(event->button() == Qt::LeftButton){
        rubberBand = new QRubberBand(QRubberBand::Rectangle,this);
        rubberBand->setGeometry(QRect(origin,QSize()));
        rubberBand->show();
    }
}

void Label::mouseMoveEvent(QMouseEvent *event){
    rubberBand->setGeometry(QRect(origin,event->pos()).normalized());
}

void Label::mouseReleaseEvent(QMouseEvent *event){
   point=event->pos();
   if(point.x()>this->width())
       point.setX(this->width());
   if(point.x()<0)
       point.setX(0);
   if(point.y()>this->height())
       point.setY(this->height());
   if(point.y()<0){
       point.setY(0);
   }
}

void Label::resizeEvent(QResizeEvent *event){
    QImage *image=Fonctions::redimensionner2(this->pixmap()->toImage(),this->width(),this->height());
    emit signalRedimensionnement(image);
}
