#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <QImage>
#include <QPoint>
#include <cmath>
#include "Filtre.h"

QImage decoupage(QImage const& image,QPoint const& debut, QPoint const& fin);
QImage negative(QImage const& image);
QImage niveauDeGris(QImage const& image);
QRgb pixelRVBaGris(QRgb const& pixel);
QImage redimentionner1(QImage const& image, int largeur,int hauteur);
QImage redimentionner2(QImage const& image, int largeur,int hauteur);
QImage convolution(QImage const& image, Filtre filtre);



#endif // FONCTIONS_H
