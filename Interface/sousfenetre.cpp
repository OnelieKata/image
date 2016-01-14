#include "sousfenetre.h"

SousFenetre::SousFenetre()
{
    listeImage = new std::vector<QImage>;
}

std::vector<QImage>* SousFenetre::getlisteImage(){
    return listeImage;
}

void SousFenetre::ajouterImage(QImage image){
    listeImage->push_back(image);
}

void SousFenetre::closeEvent(QCloseEvent *event){
    std::cout<<"Sous fenetre ferme";
    emit signalFermetureSousFenetre(this);
    event->accept();
}
