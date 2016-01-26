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

    tabifyDockWidget(dockRight2,dockRight);

    QWidget *contenuPalette=new QWidget;
    dockLeft->setWidget(contenuPalette);
    bouton = new QPushButton("Niveau de gris");
    bouton2 = new QPushButton("Crop");
    bouton3 = new QPushButton("Filtres");
    bouton4 = new QPushButton("Redimensionnement");
    bouton5 = new QPushButton("Seam Carving");
    boutonNegatif = new QPushButton("Negatif");
    boutonFusion = new QPushButton("Fusion");
    boutonNormaliser = new QPushButton("Normaliser");
    boutonEgaliser = new QPushButton("Egaliser");


    QVBoxLayout *dockLeftLayout= new QVBoxLayout;
    dockLeftLayout->addWidget(bouton);
    dockLeftLayout->addWidget(bouton2);
    dockLeftLayout->addWidget(bouton3);
    dockLeftLayout->addWidget(bouton4);
    dockLeftLayout->addWidget(bouton5);
    dockLeftLayout->addWidget(boutonNegatif);
    dockLeftLayout->addWidget(boutonFusion);
    dockLeftLayout->addWidget(boutonNormaliser);
    dockLeftLayout->addWidget(boutonEgaliser);
    contenuPalette->setLayout(dockLeftLayout);

    connect(bouton,SIGNAL(clicked()),this,SLOT(slotNiveauDeGris()));
    connect(bouton2,SIGNAL(clicked()),this,SLOT(slotCrop()));
    connect(bouton3,SIGNAL(clicked()),this,SLOT(slotFiltres()));
    connect(bouton4,SIGNAL(clicked()),this,SLOT(slotRedimension()));
    connect(bouton5,SIGNAL(clicked()),this,SLOT(slotApplicationSeamCarving()));

    QVBoxLayout *dockRightLayout=new QVBoxLayout;
    QWidget *contenuRGB = new QWidget;
    dockRight->setWidget(contenuRGB);
    QGridLayout *dockRightGridLayout = new QGridLayout;

    rouge= new QLabel("Rouge :");
    vert= new QLabel("Vert :");
    bleu= new QLabel("Bleu :");
    valeurRouge= new QLineEdit;
    valeurVert= new QLineEdit;
    valeurBleu= new QLineEdit;
    valeurRouge->setReadOnly(true);
    valeurVert->setReadOnly(true);
    valeurBleu->setReadOnly(true);
    histoRouge = new QLabel;
    histoVert = new QLabel;
    histoBleu = new QLabel;

    dockRightGridLayout->addWidget(rouge,0,0);
    dockRightGridLayout->addWidget(vert,1,0);
    dockRightGridLayout->addWidget(bleu,2,0);
    dockRightGridLayout->addWidget(valeurRouge,0,1);
    dockRightGridLayout->addWidget(valeurVert,1,1);
    dockRightGridLayout->addWidget(valeurBleu,2,1);

    dockRightLayout->addLayout(dockRightGridLayout);

    dockRightLayout->addWidget(histoRouge);
    dockRightLayout->addWidget(histoVert);
    dockRightLayout->addWidget(histoBleu);

    contenuRGB->setLayout(dockRightLayout);

    QVBoxLayout *dockRight2Layout=new QVBoxLayout;
    QWidget *contenuYUV = new QWidget;
    dockRight2->setWidget(contenuYUV);
    QGridLayout *dockRight2GridLayout = new QGridLayout;

    y= new QLabel("Y :");
    u= new QLabel("U :");
    v= new QLabel("V :");
    valeurY= new QLineEdit;
    valeurU= new QLineEdit;
    valeurV= new QLineEdit;
    valeurY->setReadOnly(true);
    valeurU->setReadOnly(true);
    valeurV->setReadOnly(true);
    histoY = new QLabel;
    histoU = new QLabel;
    histoV = new QLabel;

    dockRight2GridLayout->addWidget(y,0,0);
    dockRight2GridLayout->addWidget(u,1,0);
    dockRight2GridLayout->addWidget(v,2,0);
    dockRight2GridLayout->addWidget(valeurY,0,1);
    dockRight2GridLayout->addWidget(valeurU,1,1);
    dockRight2GridLayout->addWidget(valeurV,2,1);

    dockRight2Layout->addLayout(dockRight2GridLayout);

    dockRight2Layout->addWidget(histoY);
    dockRight2Layout->addWidget(histoU);
    dockRight2Layout->addWidget(histoV);

    contenuYUV->setLayout(dockRight2Layout);



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
        connect(sousFenetre->getLabel(),SIGNAL(signalAfficherRGB(int,int,int)),this,SLOT(slotAfficherRGB(int,int,int)));
        connect(sousFenetre->getLabel(),SIGNAL(signalAfficherYUV(QRgb)),this,SLOT(slotAfficherYUV(QRgb)));
        connect(sousFenetre,SIGNAL(signalFermetureSousFenetre(SousFenetre*)),this,SLOT(slotFermetureSousFenetre(SousFenetre*)));
        connect(sousFenetre,SIGNAL(signalAfficherHistogramme(QImage*)),this,SLOT(slotAfficherHistogramme(QImage*)));
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
     connect(sousFenetre->getLabel(),SIGNAL(signalAfficherRGB(int,int,int)),this,SLOT(slotAfficherRGB(int,int,int)));
     connect(sousFenetre->getLabel(),SIGNAL(signalAfficherYUV(QRgb)),this,SLOT(slotAfficherYUV(QRgb)));
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

 void MainWindow::slotAfficherRGB(int rouge,int vert,int bleu){
     valeurRouge->setText(QString::number(rouge));
     valeurVert->setText(QString::number(vert));
     valeurBleu->setText(QString::number(bleu));
 }

 void MainWindow::slotAfficherYUV(QRgb point){
     Yuv pointYuv(point);
     valeurY->setText(QString::number(pointYuv.getY()));
     valeurU->setText(QString::number(pointYuv.getU()));
     valeurV->setText(QString::number(pointYuv.getV()));
 }

 void MainWindow::slotAfficherHistogramme(QImage *image){
     Histo *histo=new Histo(*image);
     QImage *histogrammeRouge=Fonctions::afficheHistogramme(*histo,4);
     QImage *histogrammeVert=Fonctions::afficheHistogramme(*histo,2);
     QImage *histogrammeBleu=Fonctions::afficheHistogramme(*histo,1);
     histoRouge->setPixmap(QPixmap::fromImage(*histogrammeRouge));
     histoRouge->show();
     histoVert->setPixmap(QPixmap::fromImage(*histogrammeVert));
     histoVert->show();
     histoBleu->setPixmap(QPixmap::fromImage(*histogrammeBleu));
     histoBleu->show();
     histo=new Histo(*image,false);
     QImage *histogrammeY=Fonctions::afficheHistogramme(*histo,4);
     QImage *histogrammeU=Fonctions::afficheHistogramme(*histo,2);
     QImage *histogrammeV=Fonctions::afficheHistogramme(*histo,1);
     histoY->setPixmap(QPixmap::fromImage(*histogrammeY));
     histoY->show();
     histoU->setPixmap(QPixmap::fromImage(*histogrammeU));
     histoU->show();
     histoV->setPixmap(QPixmap::fromImage(*histogrammeV));
     histoV->show();
 }
