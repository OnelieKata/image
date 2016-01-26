#include "creationfiltre.h"

CreationFiltre::CreationFiltre()
{

    QPushButton *bouton1 = new QPushButton("Ok");
    QPushButton *bouton2 = new QPushButton("Annuler");
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(bouton1);
    layout2->addWidget(bouton2);

    QGridLayout *layout = new QGridLayout;
    QDoubleSpinBox *b1 = new QDoubleSpinBox;
    QDoubleSpinBox *b2 = new QDoubleSpinBox;
    QDoubleSpinBox *b3 = new QDoubleSpinBox;
    QDoubleSpinBox *b4 = new QDoubleSpinBox;
    QDoubleSpinBox *b5 = new QDoubleSpinBox;
    QDoubleSpinBox *b6 = new QDoubleSpinBox;
    QDoubleSpinBox *b7 = new QDoubleSpinBox;
    QDoubleSpinBox *b8 = new QDoubleSpinBox;
    QDoubleSpinBox *b9 = new QDoubleSpinBox;
/*
    QList<*QDoubleSpinBox> *matrice = new QList<*QDoubleSpinBox>;
    for(int i=0;i<9;i++){
        matrice->push_back(QDoubleSpinBox(this));
    }
*/
    layout->addWidget(b1,0,0);
    layout->addWidget(b2,0,1);
    layout->addWidget(b3,0,2);
    layout->addWidget(b4,1,0);
    layout->addWidget(b5,1,1);
    layout->addWidget(b6,1,2);
    layout->addWidget(b7,2,0);
    layout->addWidget(b8,2,1);
    layout->addWidget(b9,2,2);



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

        double* tab = new double[9];


        double b = b1->value();
        QMessageBox::information(this,"info","ça marche!! :)");

        tab[1] = (float)(b2->value());
        tab[2] = (float)b3->value();
        tab[3] = (float)b4->value();
        tab[4] = (float)b5->value();
        tab[5] = b6->value();
        tab[6] = b7->value();
        tab[7] = b8->value();
        tab[8] = b9->value();
        emit signalCreationFiltre((float*)tab);
    }
}
