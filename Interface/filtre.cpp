#include "Filtre.h"
#include <iostream>
#include <string>

using namespace std;


// creer un filtre moyenne de taille n
void Filtre::filtre_moyenne()
{
    int p=0;
    float v = 1.0/(float)((2*n+1)*(2*n+1));
    for (int i=-n; i<=n; i++)
    for (int j=-n; j<=n; j++)
    {
        T[p++] = v;
    }
}

// creer un filtre chapeau de taille n
void Filtre::filtre_chapeau()
{
    int p=0;
    float v = 1.0/powf((float)(n+1),4.0);
    for (int i=-n; i<=n; i++)
    for (int j=-n; j<=n; j++)
    {
        T[p++] = v*(n+1-fabsf(i))*(n+1-fabsf(j));
    }
}

// creer un filtre gaussien de taille n
void Filtre::filtre_gaussien()
{
    int p=0;
    float s = 0.0;
    float a = (float)(n*n)/3.0;
    for (int i=-n; i<=n; i++)
    for (int j=-n; j<=n; j++)
    {
        s += T[p++] = exp((float)(-i*i-j*j)/a);
    }

    // normalisation
    int surface((2*n+1)*(2*n+1));
    for (p=0; p<surface; p++)
    {
        T[p] /= s;
    }
}


// crée un filtre de taille 0
Filtre::Filtre()
{
    n = 0;
    T = new float[1];
    T[0] = 1.0;
}

// crée un filtre de taille n0 suivant le type t (par défaut Moyenne)
Filtre::Filtre(int n0, int type_filtre)
{
    if (n0<0) n0=-n0;
    n = n0;
    int surface = (2*n+1)*(2*n+1);
    T = new float[surface];
    switch (type_filtre)
    {
        case Moyenne  : filtre_moyenne();  break;
        case Chapeau  : filtre_chapeau();  break;
        case Gaussien : filtre_gaussien(); break;
        default       : filtre_moyenne();  break;
    }
}

Filtre::Filtre(int n0,float const* tableau)
{
    if (n0<0) n0=-n0;
    n = n0;
    int surface = (2*n+1)*(2*n+1);
    T = new float[surface];
    for(int i=0;i<surface;i++){
        T[i]=tableau[i];
    }
}


// constructeur par copie
Filtre::Filtre(Filtre &K)
{
    n = K.n;
    int surface = (2*n+1)*(2*n+1);
    T = new float[surface];
    for (int i=0; i<surface; i++)
        T[i] = K.T[i];
}

// affectation
Filtre& Filtre::operator=(const Filtre &K)
{
    if (this != &K)
    {
        delete[] T;
        n = K.n;
        int surface = (2*n+1)*(2*n+1);
        T = new float[surface];
        for (int i=0; i<surface; i++)
            T[i] = K.T[i];
    }
    return *this;
}

// destructeur
Filtre::~Filtre()
{
    delete[] T;
}

// acces à la valeur d'indice (i,j), -n <= i,j <= n
float Filtre::operator()(int i, int j)
{
    if (-i>n || -j>n || i>n || j>n) return 0.0;
    return T[(i+n)+(2*n+1)*(j+n)];
}

// renvoie la taille du filtre
int Filtre::taille() { return n; }

// renvoie la dimension du filtre
int Filtre::dimension() { return 2*n+1; }

// ecrire le filtre à l'ecran
void Filtre::print()
{
    int p=0;
    cout << "\n" ;
    for (int i=-n; i<=n; i++)
    {
        for (int j=-n; j<=n; j++)
        {
            cout << T[p++] << " " ;
        }
        cout << "\n" ;
    }
}

// somme des éleménts du filtre
float Filtre::somme()
{
    int surface = (2*n+1)*(2*n+1);
    float s = 0.0;
    for (int i=0; i<surface; i++)
    {
        s += T[i];
    }
    return s;
}
