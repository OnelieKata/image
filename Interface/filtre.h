#ifndef FILTRE_H
#define FILTRE_H

#include <cmath>

class Filtre
{
    int n; // taille du filtre --> dimension (2n+1) * (2n+1)
    float *T; // tableau contenant les valeurs du filtre
    void filtre_moyenne();
    void filtre_chapeau();
    void filtre_gaussien();
    void filtre_sobel1();
    void filtre_sobel2();
    void filre_augmenterContrast();
    void filtre_renforcementDesBords();
    void filtre_laplacien();
    void filtre_repoussage();
    void filtre_prewitt1();
    void filtre_prewitt2();

public :
    static const int Moyenne  = 1;
    static const int Chapeau  = 2;
    static const int Gaussien = 3;
    static const int Sobel1 = 4;
    static const int Sobel2 = 5;
    static const int AugmenterContrast = 6;
    static const int RenforcementDesBords = 7;
    static const int Laplacien = 8;
    static const int Repoussage = 9;
    static const int Prewitt1 = 10;
    static const int Prewitt2 = 11;

    Filtre();
    Filtre(int n0, int type_filtre = Moyenne);
    Filtre(int n0,float const* tableau);
    Filtre(Filtre &K);
    Filtre& operator=(const Filtre &K);
    ~Filtre();
    float operator()(int i, int j);
    int taille();
    int dimension();
    void print();
    float somme();


};


#endif // FILTRE_H
