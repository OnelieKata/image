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
        QImage* getImage();
        Label *getLabel();
        void ajouterImage(QImage *image);
        QImage *imageActive();
        void chargerImage();
        void annulerAction();
        void retablirAction();

    protected:
        void closeEvent(QCloseEvent *event);
        //void resizeEvent(QResizeEvent *event);

    private:
        std::vector<QImage*> *listeImage;
        int indiceImageActive;
        Label *myLabel;
        QScrollArea *scrollArea;

    public slots:
        //void slotRedimensionnementImage(QImage *image);

    signals :
        void signalFermetureSousFenetre(SousFenetre *sousFenetre);
        void signalAfficherHistogramme(QImage *image);

};

#endif // SOUSFENETRE_H
