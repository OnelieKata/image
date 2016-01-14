#ifndef HISTO_H
#define HISTO_H
#include <QImage>
#include <iostream>
#include <string>

class Histo
{
public:
    Histo();
    Histo(QImage const& image);
    int* getComposante(int const& num);
    void remplirTab();
    void afficher();
private:
    int composante1[256];
    int composante2[256];
    int composante3[256];

};

#endif // HISTO_H
