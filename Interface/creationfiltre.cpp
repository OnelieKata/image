#include "creationfiltre.h"

CreationFiltre::CreationFiltre()
{

    QPushButton *bouton1 = new QPushButton("Ok");
    QPushButton *bouton2 = new QPushButton("Annuler");
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(bouton1);
    layout2->addWidget(bouton2);

    for(int i=0;i<3;i++){
        monTableauStab << QList<QDoubleSpinBox *>();
        for(int j=0;j<3;j++){
          monTableauStab[i] << new QDoubleSpinBox(this);
        }
    }

    QGridLayout *layout = new QGridLayout;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            layout->addWidget(monTableauStab[i][j],i,j);
            monTableauStab[i][j]->setSingleStep(0.1);
            monTableauStab[i][j]->setRange(std::numeric_limits<int>::min(),std::numeric_limits<int>::max());
        }
    }



    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layout);
    layoutPrincipal->addLayout(layout2);

    this->setLayout(layoutPrincipal);

    connect(bouton1,SIGNAL(clicked()),this,SLOT(accept()));
    connect(bouton2,SIGNAL(clicked()),this,SLOT(reject()));
    connect(this,SIGNAL(finished(int)),this,SLOT(dialogFinish(int)));
}
void CreationFiltre::dialogFinish(int exec){
    if(exec==QDialog::Accepted){

        float* tab = new float[9];
        int h = 0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                tab[h] = (float)(monTableauStab[i][j]->value());
                h++;
            }
        }
        emit signalCreationFiltre(tab);

    }
}
