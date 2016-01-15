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

namespace Ui{
    class QMainWindow;
}

class MainWindow  : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        QImage imageActive();

    protected:
        void closeEvent(QCloseEvent *e);

    private:
        QList<SousFenetre*>* listeSousFenetre;

        QMdiArea *zoneCentrale;
        QDockWidget *dockLeft;
        QDockWidget *dockRight;
   /***********************************/
        QMenu *menuFichier;

        QAction *actionNouveauFichier;
        QAction *actionOuvrir;
        QAction *actionQuitter;
        QAction *actionEnregistrer;
   /***********************************/
        QMenu *menuEdition;


   /***********************************/
        QMenu *menuAffichage;
   /***********************************/
        QMenu *menuOutils;

        QAction *actionAfficherPaletteOutils;
        QAction *actionAfficherVoletInformations;
   /***********************************/
        QMenu *menuAide;

    public slots:
        void slotOuvrirImage();
        void slotNouveauFichier();
        void slotAfficherPaletteOutils();
        void slotAfficherVoletInformations();
        void slotFermetureSousFenetre(SousFenetre *sousFenetre);
        void slotEnregistrer();
        void slotNiveauDeGris();
};

#endif // MAINWINDOW_H
