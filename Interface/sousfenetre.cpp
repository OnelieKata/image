#include "sousfenetre.h"

SousFenetre::SousFenetre()
{
    listeImage = new std::vector<QImage>;
    indiceImageActive = -1;
}

std::vector<QImage>* SousFenetre::getlisteImage(){
    return listeImage;
}

void SousFenetre::ajouterImage(QImage image){
    if(indiceImageActive<listeImage->size()-1){
        std::cout<<"indice de l'image active : "<<indiceImageActive<<std::endl<<"indice de fin : "<<listeImage->size()<<std::endl;
        for(int i=indiceImageActive;i<listeImage->size()-1;i++){
            listeImage->pop_back();
        }
    }
    listeImage->push_back(image);
    ++indiceImageActive;

}

void SousFenetre::closeEvent(QCloseEvent *event){
    std::cout<<"Sous fenetre ferme";
    emit signalFermetureSousFenetre(this);
    event->accept();
}

QImage SousFenetre::imageActive(){
    return listeImage->at(indiceImageActive);
}

void SousFenetre::chargerImage(){
    Label* myLabel = new Label;
    myLabel->setPixmap(QPixmap::fromImage(listeImage->at(indiceImageActive)));
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
