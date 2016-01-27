#ifndef CREATIONFILTRE_H
#define CREATIONFILTRE_H
#include <QtWidgets>
#include <iostream>

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
    QList<QList<QDoubleSpinBox *> > monTableauStab;
};
#endif // CREATIONFILTRE_H
