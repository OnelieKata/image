#include "label.h"

Label::Label()
{

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
   //rubberBand->hide();
}
