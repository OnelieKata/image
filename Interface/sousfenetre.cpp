#include "sousfenetre.h"

SousFenetre::SousFenetre()
{
    listeImage = new std::vector<QImage*>;
    indiceImageActive = -1;
    myLabel=new Label;
    //connect(myLabel,SIGNAL(signalRedimensionnement(QImage*)),this,SLOT(slotRedimensionnementImage()));
}

std::vector<QImage*>* SousFenetre::getlisteImage(){
    return listeImage;
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
    myLabel = new Label;
    myLabel->setPixmap(QPixmap::fromImage(*listeImage->at(indiceImageActive)));
    this->setWidget(myLabel);
}

void SousFenetre::annulerAction(){
    if(indiceImageActive>0){
        indiceImageActive--;
        chargerImage();
    }else{
        QMessageBox::critical(this,"pb","pb");
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

void SousFenetre::slotRedimensionnementImage(QImage *image){
    ajouterImage(image);
    chargerImage();
}

/*void SousFenetre::resizeEvent(QResizeEvent *event){
    this->getLabel()->setScaledContents(true);
}*/
