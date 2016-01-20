#include "mainwindow.h"

MainWindow::MainWindow()
{
    listeSousFenetre = new QList<SousFenetre*>;
    setMouseTracking(true);
    this->setWindowTitle("Titre");
    setMinimumSize(1200,800);

    zoneCentrale= new QMdiArea;
    setCentralWidget(zoneCentrale);

    dockLeft= new QDockWidget("Palette d'outils",this);
    addDockWidget(Qt::LeftDockWidgetArea,dockLeft);
    dockLeft->setMinimumWidth(200);

    dockRight= new QDockWidget("Informations",this);
    addDockWidget(Qt::RightDockWidgetArea,dockRight);
    dockRight->setMinimumWidth(200);

    QWidget *contenuPalette=new QWidget;
    dockLeft->setWidget(contenuPalette);
    QPushButton *bouton = new QPushButton("Niveau de gris");
    QPushButton *bouton2 = new QPushButton("Flouter");
    QPushButton *bouton4 = new QPushButton("Filtres");
    QVBoxLayout *dockLeftLayout= new QVBoxLayout;
    dockLeftLayout->addWidget(bouton);
    dockLeftLayout->addWidget(bouton2);
    dockLeftLayout->addWidget(bouton4);
    contenuPalette->setLayout(dockLeftLayout);
    connect(bouton,SIGNAL(clicked()),this,SLOT(slotNiveauDeGris()));
    connect(bouton2,SIGNAL(clicked()),this,SLOT(slotFlouter()));
    connect(bouton4,SIGNAL(clicked()),this,SLOT(slotFiltres()));
    /*dockLeft->setLayout();
    dockLeft->setWidget(bouton);
    dockLeft->setWidget(bouton2);
    QHBoxLayout *layout=new QHBoxLayout;
    layout->addWidget(bouton);
    layout->addWidget(bouton2);
    dockLeft->setLayout(layout);
*/
    /*******************************************************************************************************
    *******************************************************************************************************/

    menuFichier =menuBar()->addMenu("&Fichier");

    actionNouveauFichier = new QAction("&Nouveau fichier",this);
    menuFichier->addAction(actionNouveauFichier);
    actionNouveauFichier->setShortcut(QKeySequence("Ctrl+N"));
    connect(actionNouveauFichier, SIGNAL(triggered()),this,SLOT(slotNouveauFichier()));

    actionOuvrir = new QAction("Ouvrir",this);
    menuFichier->addAction(actionOuvrir);
    actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
    connect(actionOuvrir, SIGNAL(triggered()),this,SLOT(slotOuvrirImage()));

    actionEnregistrerSous = new QAction("&Enregistrer sous",this);
    menuFichier->addAction(actionEnregistrerSous);
    actionEnregistrerSous->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionEnregistrerSous, SIGNAL(triggered()),this,SLOT(slotEnregistrerSous()));

    actionQuitter = new QAction("&Quitter",this);
    menuFichier->addAction(actionQuitter);
    actionQuitter->setShortcut(QKeySequence("Alt+F4"));
    connect(actionQuitter, SIGNAL(triggered()),qApp,SLOT(quit()));

    /*******************************************************************************************************
    *******************************************************************************************************/

    menuEdition =menuBar()->addMenu("&Edition");

    actionAnnuler = new QAction("&Annuler",this);
    menuEdition->addAction(actionAnnuler);
    actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
    connect(actionAnnuler, SIGNAL(triggered()),this,SLOT(slotAnnuler()));

    actionRetablir = new QAction("&Retablir",this);
    menuEdition->addAction(actionRetablir);
    actionRetablir->setShortcut(QKeySequence("Ctrl+Y"));
    connect(actionRetablir, SIGNAL(triggered()),this,SLOT(slotRetablir()));

    /*******************************************************************************************************
    *******************************************************************************************************/

    menuAffichage =menuBar()->addMenu("&Affichage");

    /*******************************************************************************************************
    *******************************************************************************************************/

    menuOutils =menuBar()->addMenu("&Outils");

    actionAfficherPaletteOutils = new QAction("&Afficher la palette d'outils",this);
    menuOutils->addAction(actionAfficherPaletteOutils);
    //actionAfficherPaletteOutils->setShortcut(QKeySequence("Alt+F4"));
    actionAfficherPaletteOutils->setCheckable(true);
    actionAfficherPaletteOutils->setChecked(true);
    connect(actionAfficherPaletteOutils, SIGNAL(triggered()),this,SLOT(slotAfficherPaletteOutils()));

    actionAfficherVoletInformations = new QAction("&Afficher le volet d'information",this);
    menuOutils->addAction(actionAfficherVoletInformations);
    //actionAfficherPaletteOutils->setShortcut(QKeySequence("Alt+F4"));
    actionAfficherVoletInformations->setCheckable(true);
    actionAfficherVoletInformations->setChecked(true);
    connect(actionAfficherVoletInformations, SIGNAL(triggered()),this,SLOT(slotAfficherVoletInformations()));

    /*******************************************************************************************************
    *******************************************************************************************************/

    menuAide =menuBar()->addMenu("&Aide");





}


void MainWindow::slotOuvrirImage()
{
    QImage myImage;

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString("/home/tiretfa/Images"), "Images (*.png *.gif *.jpg *.jpeg)");
    if(!fichier.isEmpty()){
        myImage.load(fichier);
        SousFenetre *sousFenetre= new SousFenetre;
        connect(sousFenetre,SIGNAL(signalFermetureSousFenetre(SousFenetre*)),this,SLOT(slotFermetureSousFenetre(SousFenetre*)));
        listeSousFenetre->push_back(sousFenetre);
        sousFenetre->ajouterImage(myImage);
        sousFenetre->chargerImage();


        zoneCentrale->addSubWindow(sousFenetre);

        sousFenetre->show();

        std::cout<<"Taille :"<< listeSousFenetre->size() << std::endl;
    }
}


void MainWindow::slotNouveauFichier()
{
    std::cout << "Nouveau fichier!";

}

void MainWindow::slotAfficherPaletteOutils(){
    if(actionAfficherPaletteOutils->isChecked()){
        dockLeft->setVisible(true);
    }
    else{
       dockLeft->setVisible(false);
    }
}

void MainWindow::slotAfficherVoletInformations()
{
    if(actionAfficherVoletInformations->isChecked()){
        dockRight->setVisible(true);
    }
    else{
        dockRight->setVisible(false);
    }
}

void MainWindow::closeEvent(QCloseEvent *e){
    std::cout <<"Fenetre fermée";
    e->accept();

}


void MainWindow::slotFermetureSousFenetre(SousFenetre *sousFenetre){
    listeSousFenetre->removeOne(sousFenetre);
}


QImage MainWindow::imageActive(){
    QImage img ;
    SousFenetre* sfActive = new SousFenetre;
    QMdiSubWindow* swActive = zoneCentrale->currentSubWindow();
    if(swActive==NULL){
        return img;
    }
    for(int i=0;i<listeSousFenetre->size();i++){
        if(listeSousFenetre->at(i)==swActive){
            sfActive = listeSousFenetre->at(i);
            break;
        }
    }
    return sfActive->getlisteImage()->back();
}

SousFenetre* MainWindow::sousFenetreActive(){
    SousFenetre* sfActive = new SousFenetre;
    QMdiSubWindow* swActive = zoneCentrale->currentSubWindow();
    for(int i=0;i<listeSousFenetre->size();i++){
        if(listeSousFenetre->at(i)==swActive){
            sfActive = listeSousFenetre->at(i);
            break;
        }
    }
    return sfActive;
}

 void MainWindow::slotEnregistrerSous(){
    QImage image = imageActive();
    QString fichier = QFileDialog::getSaveFileName(this, "EnregistrerSous un fichier", QString("/home/tiretfa/Images/sans_titre.png"), "Images (*.png *.gif *.jpg *.jpeg)");
    if(!image.isNull()){
        image.save(fichier);
    }else{
        QMessageBox::critical(this,"erreur","Il n'y a aucune image ouverte");
    }
}

void MainWindow::slotAnnuler(){
    SousFenetre* sfActive = sousFenetreActive();
    sfActive->annulerAction();
    sfActive->show();
}

void MainWindow::slotRetablir(){
    SousFenetre* sfActive = sousFenetreActive();
    sfActive->retablirAction();
    sfActive->show();
}

 void MainWindow::slotNiveauDeGris(){
     SousFenetre* sfActive=sousFenetreActive();
     QImage image = Fonctions::niveauDeGris(sfActive->imageActive());
     sfActive->ajouterImage(image);
     sfActive->chargerImage();
     sfActive->show();
 }

 void MainWindow::slotFlouter(){
     SousFenetre* sfActive=sousFenetreActive();
     Filtre filtre(3,Filtre::Moyenne);
     QImage image = Fonctions::convolution(sfActive->imageActive(),filtre);
     sfActive->ajouterImage(image);
     sfActive->chargerImage();
     sfActive->show();
 }

 void MainWindow::slotFiltres(){

    QDialog* secondeFenetre = new QDialog;

    QSpinBox degreFiltre(secondeFenetre);

    QComboBox *listeFiltres = new QComboBox(secondeFenetre);
    listeFiltres->addItem("Moyenne");
    listeFiltres->addItem("Chapeau");
    listeFiltres->addItem("Sobel1");
    listeFiltres->addItem("Sobel2");
    listeFiltres->addItem("AugmenterContrast");
    listeFiltres->addItem("RenforcementDesBords");
    listeFiltres->addItem("Laplacien");
    listeFiltres->addItem("Repoussage");
    listeFiltres->addItem("Prewitt1");
    listeFiltres->addItem("Prewitt2");

    QPushButton *bouton1 = new QPushButton("Ok");
    QPushButton *bouton2 = new QPushButton("Annuler");
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(bouton1);
    layout2->addWidget(bouton2);

    QFormLayout *layout = new QFormLayout;
    layout->addRow("degré de filtrage", &degreFiltre);
    layout->addRow("type de filtre", listeFiltres);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layout);
    layoutPrincipal->addLayout(layout2);

    secondeFenetre->setLayout(layoutPrincipal);
    if(){
        QMessageBox::information(this,"a","a");
      }

    connect(bouton1,SIGNAL(clicked()),secondeFenetre,SLOT(accept()));
    connect(bouton2,SIGNAL(clicked()),secondeFenetre,SLOT(reject()));
    //connect(secondeFenetre,SIGNAL(finished(int)),this,SLOT(dialogFinish(int)));

    secondeFenetre->exec();
 }
