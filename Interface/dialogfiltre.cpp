#include "dialogfiltre.h"

DialogFiltre::DialogFiltre(){



    listeFiltres = new QComboBox(this);
    listeFiltres->addItem("Moyenne");
    listeFiltres->addItem("Chapeau");
    listeFiltres->addItem("Gaussien");
    listeFiltres->addItem("Sobel1");
    listeFiltres->addItem("Sobel2");
    listeFiltres->addItem("AugmenterContrast");
    listeFiltres->addItem("RenforcementDesBords");
    listeFiltres->addItem("Laplacien");
    listeFiltres->addItem("Repoussage");
    listeFiltres->addItem("Prewitt1");
    listeFiltres->addItem("Prewitt2");

    degreFiltre = new QSpinBox(this);


    QPushButton *bouton1 = new QPushButton("Ok");
    QPushButton *bouton2 = new QPushButton("Annuler");
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(bouton1);
    layout2->addWidget(bouton2);

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Degré de filtrage", degreFiltre);
    layout->addRow("Type de filtre", listeFiltres);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layout);
    layoutPrincipal->addLayout(layout2);

    this->setLayout(layoutPrincipal);

    connect(bouton1,SIGNAL(clicked()),this,SLOT(accept()));
    connect(bouton2,SIGNAL(clicked()),this,SLOT(reject()));
    connect(this,SIGNAL(finished(int)),this,SLOT(dialogFinish(int)));

    //this->exec();
}

void DialogFiltre::dialogFinish(int exec){
    if(exec==QDialog::Accepted){
        int type = listeFiltres->currentIndex()+1;
        int deg = degreFiltre->value();

        emit signalApplicationFiltre(type,deg);
    }
}
