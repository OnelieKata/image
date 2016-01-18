#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <QImage>
#include <QPoint>
#include <cmath>
#include "filtre.h"
#include "histo.h"

static QImage decoupage(QImage const& image,QPoint const& debut, QPoint const& fin);
static QImage negative(QImage const& image);
static QImage niveauDeGris(QImage const& image);
static QRgb pixelRVBaGris(QRgb const& pixel);
static QImage redimensionner1(QImage const& image, int largeur,int hauteur);
static QImage redimensionner2(QImage const& image, int largeur,int hauteur);
static QImage convolution(QImage const& image, Filtre filtre);
static QImage max(QImage &I1, QImage &I2);
static QImage sobel(QImage const& image);
static QImage prewitt(QImage const& image);
static QImage fusionBasic(QImage const& arrierePlan,QImage const& image);
static bool estEnNiveauDeGris(QImage const& image);
static QImage normalisation(QImage const& image,Histo histo);
static QImage afficheHistogramme(Histo histo);
static QImage egalisation(QImage const& image,Histo histo);



#endif // FONCTIONS_H
