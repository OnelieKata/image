#ifndef SOUSFENETRE_H
#define SOUSFENETRE_H

#include <QtWidgets>
#include <QMainWindow>
#include <iostream>

class SousFenetre : public QMdiSubWindow
{
    Q_OBJECT

    public:
        SousFenetre();
       // QMdiSubWindow* getsubWindow();
        std::vector<QImage>* getlisteImage();
        void ajouterImage(QImage image);
        QImage imageActive();
        void chargerImage();

    protected:
        void closeEvent(QCloseEvent *event);

    private:
      //  QMdiSubWindow *subWindow;
        std::vector<QImage> *listeImage;
        int indiceImageActive;

    signals :
        void signalFermetureSousFenetre(SousFenetre *sousFenetre);

};

#endif // SOUSFENETRE_H
