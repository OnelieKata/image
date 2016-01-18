#ifndef HISTO_H
#define HISTO_H
#include <QImage>
#include <iostream>
#include <string>

class Histo
{
    static const int Taille  = 256;

public:
    Histo();
    Histo(QImage const& image);
    int getComposante(int indice,int numComposante = 1);
    int getComposanteCumulee(int indice,int numComposante = 1);
    int getMin(int num = 1);
    int getMax(int num = 1);
    int getMaxValeur();
    int getNbPixel();
    void remplirTab();
    void rechercheMin();
    void rechercheMax();
    void rechercheMaxValeur();
    void afficher();

private:
    int composante1[Taille];
    int composante2[Taille];
    int composante3[Taille];
    int composanteCumulee1[Taille];
    int composanteCumulee2[Taille];
    int composanteCumulee3[Taille];
    int min1;
    int max1;
    int min2;
    int max2;
    int min3;
    int max3;
    int maxValeur; // le nombre maximal de pixel de meme couleur
    int nbPixel;

};

#endif // HISTO_H
