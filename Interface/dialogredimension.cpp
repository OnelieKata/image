#include "dialogredimension.h"

DialogRedimension::DialogRedimension(){
    largeur = new QSpinBox(this);
    hauteur = new QSpinBox(this);
    largeur->setMinimum(0);
    largeur->setMaximum(1500);
    hauteur->setMinimum(0);
    hauteur->setMaximum(1500);
    QPushButton *bouton1 = new QPushButton("Ok");
    QPushButton *bouton2 = new QPushButton("Annuler");
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(bouton1);
    layout2->addWidget(bouton2);

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Largeur : ", largeur);
    layout->addRow("Hauteur : ", hauteur);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layout);
    layoutPrincipal->addLayout(layout2);

    this->setLayout(layoutPrincipal);

    connect(bouton1,SIGNAL(clicked()),this,SLOT(accept()));
    connect(bouton2,SIGNAL(clicked()),this,SLOT(reject()));
    connect(this,SIGNAL(finished(int)),this,SLOT(dialogFinish(int)));
}

void DialogRedimension::dialogFinish(int exec){
    if(exec==QDialog::Accepted){
        int l = largeur->value();
        int h = hauteur->value();
        emit signalApplicationRedimension(l,h);
    }
}
