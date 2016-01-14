#include <QApplication>
#include <QtWidgets>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow fenetre;
    fenetre.QMainWindow::show();

    return app.exec();
}
