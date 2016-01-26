#ifndef DIALOGREDIMENSION_H
#define DIALOGREDIMENSION_H
#include <QtWidgets>
class DialogRedimension: public QDialog
{
    Q_OBJECT
public:
    DialogRedimension();

public slots :
    void dialogFinish(int exec);

signals :
    void signalApplicationRedimension(int l,int h);

private:
   QSpinBox *largeur ;
   QSpinBox *hauteur ;
};

#endif // DIALOGREDIMENSION_H
