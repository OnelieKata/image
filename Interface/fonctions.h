#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <QImage>
#include <QPoint>
#include <cmath>
#include "filtre.h"
#include "histo.h"


class Fonctions {
public:

static QImage decoupage(QImage const& image,QPoint const& debut, QPoint const& fin);
static QImage negative(QImage const& image);
static QImage niveauDeGris(QImage const& image);
static QRgb pixelRVBaGris(QRgb const& pixel);
static QImage redimensionner1(QImage const& image, int largeur,int hauteur);
static QImage redimensionner2(QImage const& image, int largeur,int hauteur);
static QImage convolution(QImage const& image, Filtre filtre);
static QImage max(QImage &I1, QImage &I2);
static int min(int a, int b);
static int min(int a, int b, int c);
static QImage sobel(QImage const& image);
static QImage prewitt(QImage const& image);
static QImage fusionBasic(QImage const& arrierePlan,QImage const& image);
static bool estEnNiveauDeGris(QImage const& image);
static QImage normalisation(QImage const& image,Histo histo);
static QImage afficheHistogramme(Histo histo);
static QImage afficheHistogramme(Histo histo,int numComposante);
static QImage afficheHistogrammeCumulee(Histo histo);
static QImage afficheHistogrammeCumulee(Histo histo,int numComposanteCumulee);
static QImage egalisation(QImage const& image,Histo histo);
static QImage gradientH(QImage const& image);
static QImage gradientV(QImage const& image);
static QImage gradient(QImage const& image);
static QImage seamCarvingV(QImage const& image);

};

#endif // FONCTIONS_H
