#ifndef DIALOG_H
#define DIALOG_H
#include <QtWidgets>
#include <iostream>

class Dialog: public QDialog
{
    Q_OBJECT
public:
    Dialog(int type);

public slots :
    void dialogFinish(int exec);

signals :
    void signalApplicationFiltre(int type,int degre);
private:
    QComboBox *listeFiltres ;
    QSpinBox *degreFiltre ;



};

#endif // DIALOG_H
