#ifndef SOUSFENETRE_H
#define SOUSFENETRE_H

#include <QtWidgets>
#include <QMainWindow>
#include <iostream>
#include <QRubberBand>
#include <label.h>

class SousFenetre : public QMdiSubWindow
{
    Q_OBJECT

    public:
        SousFenetre();
        std::vector<QImage>* getlisteImage();
        void ajouterImage(QImage image);
        QImage imageActive();
        void chargerImage();
        void annulerAction();
        void retablirAction();

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        std::vector<QImage> *listeImage;
        int indiceImageActive;

    signals :
        void signalFermetureSousFenetre(SousFenetre *sousFenetre);

};

#endif // SOUSFENETRE_H
