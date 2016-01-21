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

    dockRight= new QDockWidget("RGB",this);
    addDockWidget(Qt::RightDockWidgetArea,dockRight);
    dockRight->setMinimumWidth(200);

    dockRight2= new QDockWidget("YUV",this);
    addDockWidget(Qt::RightDockWidgetArea,dockRight2);
    dockRight2->setMinimumWidth(200);

    tabifyDockWidget(dockRight,dockRight2);

    QWidget *contenuPalette=new QWidget;
    dockLeft->setWidget(contenuPalette);
    QPushButton *bouton = new QPushButton("Niveau de gris");
    QPushButton *bouton2 = new QPushButton("Crop");
    QPushButton *bouton3 = new QPushButton("Filtres");
    QPushButton *bouton4 = new QPushButton("Redimensionnement");
    QPushButton *bouton5 = new QPushButton("Seam Carving");

    QVBoxLayout *dockLeftLayout= new QVBoxLayout;
    dockLeftLayout->addWidget(bouton);
    dockLeftLayout->addWidget(bouton2);
    dockLeftLayout->addWidget(bouton3);
    dockLeftLayout->addWidget(bouton4);
    dockLeftLayout->addWidget(bouton5);
    contenuPalette->setLayout(dockLeftLayout);

    connect(bouton,SIGNAL(clicked()),this,SLOT(slotNiveauDeGris()));
    connect(bouton2,SIGNAL(clicked()),this,SLOT(slotCrop()));
    connect(bouton3,SIGNAL(clicked()),this,SLOT(slotFiltres()));
    connect(bouton4,SIGNAL(clicked()),this,SLOT(slotRedimension()));
    connect(bouton5,SIGNAL(clicked()),this,SLOT(slotApplicationSeamCarving()));



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
    actionAfficherPaletteOutils->setCheckable(true);
    actionAfficherPaletteOutils->setChecked(true);
    connect(actionAfficherPaletteOutils, SIGNAL(triggered()),this,SLOT(slotAfficherPaletteOutils()));

    actionAfficherVoletInformationsRGB = new QAction("&Afficher le volet d'information RGB",this);
    menuOutils->addAction(actionAfficherVoletInformationsRGB);
    actionAfficherVoletInformationsRGB->setCheckable(true);
    actionAfficherVoletInformationsRGB->setChecked(true);
    connect(actionAfficherVoletInformationsRGB, SIGNAL(triggered()),this,SLOT(slotAfficherVoletInformationsRGB()));

    actionAfficherVoletInformationsYUV = new QAction("&Afficher le volet d'information YUV",this);
    menuOutils->addAction(actionAfficherVoletInformationsYUV);
    actionAfficherVoletInformationsYUV->setCheckable(true);
    actionAfficherVoletInformationsYUV->setChecked(true);
    connect(actionAfficherVoletInformationsYUV, SIGNAL(triggered()),this,SLOT(slotAfficherVoletInformationsYUV()));

    /*******************************************************************************************************
    *******************************************************************************************************/

    menuAide =menuBar()->addMenu("&Aide");





}


void MainWindow::slotOuvrirImage()
{
    QImage *myImage=new QImage;
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString("/home/tiretfa/Images"), "Images (*.png *.gif *.jpg *.jpeg)");

    if(!fichier.isEmpty()){

        myImage->load(fichier);
        SousFenetre *sousFenetre= new SousFenetre;
        connect(sousFenetre,SIGNAL(signalFermetureSousFenetre(SousFenetre*)),this,SLOT(slotFermetureSousFenetre(SousFenetre*)));
        listeSousFenetre->push_back(sousFenetre);
        sousFenetre->ajouterImage(myImage);
        sousFenetre->chargerImage();

        zoneCentrale->addSubWindow(sousFenetre);
        sousFenetre->show();
    }
}


void MainWindow::slotAfficherPaletteOutils(){
    if(actionAfficherPaletteOutils->isChecked()){
        dockLeft->setVisible(true);
    }
    else{
       dockLeft->setVisible(false);
    }
}

void MainWindow::slotAfficherVoletInformationsRGB()
{
    if(actionAfficherVoletInformationsRGB->isChecked()){
        dockRight->setVisible(true);
    }
    else{
        dockRight->setVisible(false);
    }
}

void MainWindow::slotAfficherVoletInformationsYUV()
{
    if(actionAfficherVoletInformationsYUV->isChecked()){
        dockRight2->setVisible(true);
    }
    else{
        dockRight2->setVisible(false);
    }
}


void MainWindow::slotFermetureSousFenetre(SousFenetre *sousFenetre){
    listeSousFenetre->removeOne(sousFenetre);
}


QImage* MainWindow::imageActive(){
    QImage *img=new QImage ;
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
    QImage *image = imageActive();
    QString fichier = QFileDialog::getSaveFileName(this, "EnregistrerSous un fichier", QString("/home/tiretfa/Images/sans_titre.png"), "Images (*.png *.gif *.jpg *.jpeg)");
    if(!image->isNull()){
        image->save(fichier);
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
     QImage *image = Fonctions::niveauDeGris(*sfActive->imageActive());
     sfActive->ajouterImage(image);
     sfActive->chargerImage();
     sfActive->show();
 }

 void MainWindow::slotFiltres(){
     DialogFiltre *d = new DialogFiltre();
     connect(d,SIGNAL(signalApplicationFiltre(int,int)),this,SLOT(slotApplicationFiltre(int,int)));
     d->exec();
}

 void MainWindow::slotApplicationFiltre(int type, int deg){
     SousFenetre* sfActive=sousFenetreActive();
     Filtre filtre(deg,type);
     QImage *image = Fonctions::convolution(*sfActive->imageActive(),filtre);
     sfActive->ajouterImage(image);
     sfActive->chargerImage();
     sfActive->show();
 }

 void MainWindow::slotCrop(){
     SousFenetre* sfActive=sousFenetreActive();
     QImage *image = Fonctions::decoupage(*sfActive->imageActive(),sfActive->getLabel()->getOrigin(),sfActive->getLabel()->getPoint());
     SousFenetre *sousFenetre= new SousFenetre;
     connect(sousFenetre,SIGNAL(signalFermetureSousFenetre(SousFenetre*)),this,SLOT(slotFermetureSousFenetre(SousFenetre*)));
     listeSousFenetre->push_back(sousFenetre);
     sousFenetre->ajouterImage(image);
     sousFenetre->chargerImage();
     sfActive->getLabel()->getRubberBand()->hide();


     zoneCentrale->addSubWindow(sousFenetre);

     sousFenetre->show();
 }

 void MainWindow::slotRedimension(){
     dialogredimension* d = new dialogredimension();
     connect(d,SIGNAL(signalApplicationRedimension(int,int)),this,SLOT(slotApplicationRedimension(int,int)));
     d->exec();
 }

 void MainWindow::slotApplicationRedimension(int l, int h){
    SousFenetre* sfActive=sousFenetreActive();
    QImage *image=Fonctions::redimensionner2(*sfActive->imageActive(),l,h);
    sfActive->resize(l,h);
    sfActive->ajouterImage(image);
    sfActive->chargerImage();
    sfActive->show();
 }

 void MainWindow::slotSeamCarving(){
     dialogredimension* d = new dialogredimension();
     connect(d,SIGNAL(signalApplicationRedimension(int,int)),this,SLOT(slotApplicationSeamCarving(int,int)));
     d->exec();
 }

 void MainWindow::slotApplicationSeamCarving(){
     SousFenetre* sfActive=sousFenetreActive();
     QImage *image=Fonctions::seamCarvingH(*sfActive->imageActive());
     //sfActive->resize(l,h);
     sfActive->ajouterImage(image);
     sfActive->chargerImage();
     sfActive->show();
 }
