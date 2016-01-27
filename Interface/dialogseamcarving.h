#ifndef DIALOGSEAMCARVING_H
#define DIALOGSEAMCARVING_H
#include <QtWidgets>
class DialogSeamCarving : public QDialog
{
    Q_OBJECT
public:
    DialogSeamCarving();

public slots :
    void dialogFinish(int exec);

signals :
    void signalApplicationSeamCarving(int l,int h);

private:
   QSpinBox *largeur ;
   QSpinBox *hauteur ;
};

#endif // DIALOGSEAMCARVING_H
