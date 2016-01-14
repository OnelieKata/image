#include "mainwindow.h"

MainWindow::MainWindow()
{
    listeSousFenetre = new QList<SousFenetre*>;

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

    actionEnregistrer = new QAction("&Enregistrer",this);
    menuFichier->addAction(actionEnregistrer);
    actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionEnregistrer, SIGNAL(triggered()),this,SLOT(slotEnregistrer()));

    actionQuitter = new QAction("&Quitter",this);
    menuFichier->addAction(actionQuitter);
    actionQuitter->setShortcut(QKeySequence("Alt+F4"));
    connect(actionQuitter, SIGNAL(triggered()),qApp,SLOT(quit()));

    /*******************************************************************************************************
    *******************************************************************************************************/

    menuEdition =menuBar()->addMenu("&Edition");

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
    QLabel* myLabel = new QLabel;
    QImage myImage;

    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    if(!fichier.isEmpty()){
        myImage.load(fichier);
        SousFenetre *sousFenetre= new SousFenetre;
        connect(sousFenetre,SIGNAL(signalFermetureSousFenetre(SousFenetre*)),this,SLOT(slotFermetureSousFenetre(SousFenetre*)));
        listeSousFenetre->push_back(sousFenetre);
        myLabel->setPixmap(QPixmap::fromImage(myImage));
        sousFenetre->ajouterImage(myImage);

        sousFenetre->setWidget(myLabel);
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
    SousFenetre* sfActive = listeSousFenetre->first();
    QMdiSubWindow* swActive = zoneCentrale->currentSubWindow();

    for(unsigned int i=0;i<listeSousFenetre->size();i++){
        if(listeSousFenetre->at(i)==swActive){
            sfActive = listeSousFenetre->at(i);
           // QMessageBox::information(this,"test","");
           // std::cout<<"sous fenetre ouverte est :"<<i<<std::endl;
        }
    }
    return sfActive->getlisteImage()->back();
}

void MainWindow::slotEnregistrer(){
    QImage image = imageActive();
    image.save("/home/tiretfa/Bureau/test1.png");
}
