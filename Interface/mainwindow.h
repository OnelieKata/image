#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sousfenetre.h>
#include <filtre.h>
#include <fonctions.h>
#include <histo.h>
#include <QtWidgets>
#include <QMenu>
#include <QAction>
#include <iostream>
#include <QDockWidget>
#include <QList>
#include <label.h>
#include <dialogfiltre.h>
#include <dialogredimension.h>
#include <creationfiltre.h>
#include <dialogseamcarving.h>

namespace Ui{
    class QMainWindow;
}

class MainWindow  : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        QImage *imageActive();
        SousFenetre *sousFenetreActive();

    protected:

    private:
        QList<SousFenetre*>* listeSousFenetre;

        QMdiArea *zoneCentrale;

        QDockWidget *dockLeft;
        QPushButton *boutonNiveauDeGris;
        QPushButton *boutonCrop;
        QPushButton *boutonFiltres;
        QPushButton *boutonRedimensionnement;
        QPushButton *boutonSeamCarving;
        QPushButton *boutonCreationFiltre;
        QPushButton *boutonNegatif;
        QPushButton *boutonFusion;
        QPushButton *boutonNormaliser;
        QPushButton *boutonEgaliser;
        QPushButton *boutonGradient;
        QPushButton *boutonMiroir;

        QDockWidget *dockRight;
        QLabel *rouge;
        QLabel *vert;
        QLabel *bleu;
        QLineEdit *valeurRouge;
        QLineEdit *valeurVert;
        QLineEdit *valeurBleu;
        QLabel *histoRouge;
        QLabel *histoVert;
        QLabel *histoBleu;

        QDockWidget *dockRight2;
        QLabel *y;
        QLabel *u;
        QLabel *v;
        QLineEdit *valeurY;
        QLineEdit *valeurU;
        QLineEdit *valeurV;
        QLabel *histoY;
        QLabel *histoU;
        QLabel *histoV;

   /***********************************/
        QMenu *menuFichier;

        QAction *actionOuvrir;
        QAction *actionQuitter;
        QAction *actionEnregistrerSous;
   /***********************************/
        QMenu *menuEdition;

        QAction *actionAnnuler;
        QAction *actionRetablir;

   /***********************************/
        QMenu *menuAffichage;

        QAction *actionRotationDroite;
        QAction *actionRotationGauche;
   /***********************************/
        QMenu *menuOutils;

        QAction *actionAfficherPaletteOutils;
        QAction *actionAfficherVoletInformationsRGB;
        QAction *actionAfficherVoletInformationsYUV;
   /***********************************/
        QMenu *menuAide;

    public slots:
        void slotOuvrirImage();
        void slotAfficherPaletteOutils();
        void slotAfficherVoletInformationsRGB();
        void slotAfficherVoletInformationsYUV();
        void slotFermetureSousFenetre(SousFenetre *sousFenetre);
        void slotEnregistrerSous();
        void slotAnnuler();
        void slotRetablir();


        void slotNiveauDeGris();
        void slotCrop();
        void slotFiltres();
        void slotApplicationFiltre(int type,int deg);
        void slotRedimension();
        void slotApplicationRedimension(int,int);
        void slotSeamCarving();
        void slotNegatif();
        void slotFusion();
        void slotNormaliser();
        void slotEgaliser();
        void slotGradient();
        void slotApplicationSeamCarving(int l, int h);
        void slotCreationFiltre();
        void slotApplicationCreationFiltre(float* tab);
        void slotAfficherRGB(int rouge,int vert,int bleu);
        void slotAfficherYUV(QRgb point);
        void slotAfficherHistogramme(QImage *image);
        void slotApplicationHistogramme(QMdiSubWindow*);
        void slotRotationDroite();
        void slotRotationGauche();
        void slotMiroir();

};

#endif // MAINWINDOW_H
