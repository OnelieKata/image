#ifndef SOUSFENETRE_H
#define SOUSFENETRE_H

#include <QtWidgets>
#include <QMainWindow>
#include <iostream>
#include <QRubberBand>

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
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

    private:
        std::vector<QImage> *listeImage;
        int indiceImageActive;
        QRubberBand *rubberBand;
        QPoint origin;

    signals :
        void signalFermetureSousFenetre(SousFenetre *sousFenetre);

};

#endif // SOUSFENETRE_H
