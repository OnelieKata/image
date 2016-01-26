#ifndef CREATIONFILTRE_H
#define CREATIONFILTRE_H
#include <QtWidgets>

class CreationFiltre : public QDialog
{
    Q_OBJECT
public:
    CreationFiltre();

public slots:
    void dialogFinish(int exec);

signals :
    void signalCreationFiltre(float* tab);

private:
    QDoubleSpinBox *b1;
    QDoubleSpinBox *b2;
    QDoubleSpinBox *b3;
    QDoubleSpinBox *b4;
    QDoubleSpinBox *b5;
    QDoubleSpinBox *b6;
    QDoubleSpinBox *b7;
    QDoubleSpinBox *b8;
    QDoubleSpinBox *b9;
};
#endif // CREATIONFILTRE_H
