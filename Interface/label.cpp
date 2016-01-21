#include "label.h"

Label::Label()
{
    rubberBand=NULL;
}

QPoint Label::getOrigin(){
    return origin;
}

QPoint Label::getPoint(){
    return point;
}

QRubberBand* Label::getRubberBand(){
    return rubberBand;
}

void Label::mousePressEvent(QMouseEvent *event){
    if(rubberBand!=NULL){
        rubberBand->hide();
    }
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
   if(point.x()>this->width()-1)
       point.setX(this->width()-1);
   if(point.x()<0)
       point.setX(0);
   if(point.y()>this->height()-1)
       point.setY(this->height()-1);
   if(point.y()<0){
       point.setY(0);
   }
}

/*
void Label::resizeEvent(QResizeEvent *event){
    this->setScaledContents(true);
    QImage *image=Fonctions::redimensionner2(this->pixmap()->toImage(),this->width(),this->height());
    //this->setPixmap(QPixmap::fromImage(*image));
    //this->show();
    //std::cout<<this->width()<<" "<<this->height()<<std::endl;
    emit signalRedimensionnement(image);
    event->accept();

}
*/
