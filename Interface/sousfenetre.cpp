#include "sousfenetre.h"

SousFenetre::SousFenetre()
{
    listeImage = new std::vector<QImage*>;
    indiceImageActive = -1;
    myLabel=new Label;
    scrollArea=new QScrollArea;
}

QImage* SousFenetre::getImage(){
    return listeImage->at(indiceImageActive);
}

Label* SousFenetre::getLabel(){
    return myLabel;
}

void SousFenetre::ajouterImage(QImage *image){
    if(indiceImageActive<listeImage->size()-1){
        for(int i=indiceImageActive;i<listeImage->size()-1;i++){
            listeImage->pop_back();
        }
    }
    listeImage->push_back(image);
    ++indiceImageActive;

}

void SousFenetre::closeEvent(QCloseEvent *event){
    emit signalFermetureSousFenetre(this);
    event->accept();
}

QImage* SousFenetre::imageActive(){
    return listeImage->at(indiceImageActive);
}

void SousFenetre::chargerImage(){

 /*   QImage* image = imageActive();
    /*QImage* image = imageActive();
    myLabel->setPixmap(QPixmap::fromImage(*image));
    //this->resize(image->width()+1,image->height());
    this->setWidget(myLabel);
    // this->resize(300,300);
    scrollArea->setWidget(myLabel);
    this->setWidget(scrollArea);*/
    QImage* image = imageActive();
    myLabel->setPixmap(QPixmap::fromImage(*listeImage->at(indiceImageActive)));
    this->resize(image->width()+1,image->height());
    this->setWidget(myLabel);
    emit signalAfficherHistogramme(image);
}

void SousFenetre::annulerAction(){
    if(indiceImageActive>0){
        indiceImageActive--;
        chargerImage();
    }else{

        //QMessageBox::critical(this,"pb","pb");
    }
}

void SousFenetre::retablirAction(){
    if(indiceImageActive<listeImage->size()-1){
        indiceImageActive++;
        chargerImage();
    }else{
        QMessageBox::critical(this,"pb","pb");
    }
}

