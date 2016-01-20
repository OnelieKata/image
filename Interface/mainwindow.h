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
        QDockWidget *dockRight;
        QDockWidget *dockRight2;
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

        void slotFiltres();
        void slotNiveauDeGris();
        void slotCrop();
        void slotApplicationFiltre(int type,int deg);
};

#endif // MAINWINDOW_H
