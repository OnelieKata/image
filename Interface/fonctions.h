#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <QImage>
#include <QPoint>
#include <cmath>
#include "filtre.h"
#include "histo.h"


class Fonctions {
public:

static QImage* decoupage(QImage const& image,QPoint const& debut, QPoint const& fin);
static QImage* negative(QImage const& image);
static QImage* niveauDeGris(QImage const& image);
static QRgb pixelRVBaGris(QRgb const& pixel);
static QImage* redimensionner1(QImage const& image, int largeur,int hauteur);
static QImage* redimensionner2(QImage const& image, int largeur,int hauteur); // a corriger
static QImage* convolution(QImage const& image, Filtre filtre);
static QImage* max(QImage const& image1, QImage const& image2);
static int min(int a, int b);
static int min(int a, int b, int c);
static QImage* sobel(QImage const& image);
static QImage* prewitt(QImage const& image);
static QImage* fusionBasic(QImage const& arrierePlan,QImage const& image);
static bool estEnNiveauDeGris(QImage const& image);
static QImage* normalisation(QImage const& image,Histo histo);
static QImage* afficheHistogramme(Histo histo,int ComposanteEnBinaire = 7); // exemple 111=7 affiche le rouge,vert et bleu
static QImage* afficheHistogrammeCumulee(Histo histo,int ComposanteEnBinaire = 7); // exemple 101=5 affiche le rouge et bleu
static QImage* egalisation(QImage const& image,Histo histo);
static QImage* gradientH(QImage const& image);
static QImage* gradientV(QImage const& image);
static QImage* gradient(QImage const& image);
static QImage* seamCarvingV(QImage const& image);
static QImage* seamCarvingH(QImage const& image);
static QImage* pivoterAGauche(QImage const& image);
static QImage* pivoterADroite(QImage const& image);

};

#endif // FONCTIONS_H
