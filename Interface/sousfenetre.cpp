#include "sousfenetre.h"

SousFenetre::SousFenetre()
{
    listeImage = new std::vector<QImage*>;
    indiceImageActive = -1;
    myLabel=new Label;
    scrollArea=new QScrollArea;
}

QImage* SousFenetre::getImage(){
    if(listeImage->size()>0){
        return listeImage->at(indiceImageActive);
    }else{
        return NULL;
    }
}

Label* SousFenetre::getLabel(){
    return myLabel;
}

void SousFenetre::ajouterImage(QImage *image){

    if(indiceImageActive<listeImage->size()-1){
        for(int i=indiceImageActive;i<listeImage->size()-1;i++){
            listeImage->pop_back();
        }
        indiceImageActive = listeImage->size()-1;
    }
    listeImage->push_back(image);
    indiceImageActive++;

}

void SousFenetre::closeEvent(QCloseEvent *event){
    emit signalFermetureSousFenetre(this);
    event->accept();
}

QImage* SousFenetre::imageActive(){
    return listeImage->at(indiceImageActive);
}

void SousFenetre::chargerImage(){

    QImage* image = imageActive();
    myLabel->setPixmap(QPixmap::fromImage(*image));
    myLabel->setFixedSize(image->size());
    scrollArea->setWidget(myLabel);
    this->resize(image->width(),image->height());
    this->setWidget(scrollArea);
    this->move(0,0);
    emit signalAfficherHistogramme(image);
}

void SousFenetre::annulerAction(){
    if(indiceImageActive>0){
        indiceImageActive--;
        chargerImage();
    }
}

void SousFenetre::retablirAction(){
    if(indiceImageActive<listeImage->size()-1){
        indiceImageActive++;
        chargerImage();
    }
}

