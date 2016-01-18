#ifndef FILTRE_H
#define FILTRE_H

#include <cmath>

class Filtre
{
    int n; // taille du filtre --> dimension (2n+1) * (2n+1)
    float *T; // tableau contenant les valeurs du filtre

    // creer un filtre moyenne de taille n
    void filtre_moyenne();

    // creer un filtre chapeau de taille n
    void filtre_chapeau();

    // creer un filtre gaussien de taille n
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

    // crée un filtre de taille 0
    Filtre();

    // crée un filtre de taille n0 suivant le type t (par défaut Moyenne)
    Filtre(int n0, int type_filtre = Moyenne);

    // crée un filtre de taille n0 suivant le noyau definit dans tableau
    Filtre(int n0,float const* tableau);

    // constructeur par copie
    Filtre(Filtre &K);

    // affectation
    Filtre& operator=(const Filtre &K);

    // destructeur
    ~Filtre();

    // acces à la valeur d'indice (i,j), -n <= i,j <= n
    float operator()(int i, int j);

    // renvoie la taille du filtre
    int taille();

    // renvoie la dimension du filtre
    int dimension();

    // ecrire le filtre à l'ecran
    void print();

    // somme des éleménts du filtre
    float somme();


}; // class FiltreLineaire


#endif // FILTRE_H
