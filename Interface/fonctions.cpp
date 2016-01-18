#include "fonctions.h"
#include <iostream>
#include <string>
#include <QRgb>
#include <cmath>
#include "filtre.h"
#include <QPainter>


using namespace std;

QImage Fonctions::decoupage(QImage const& image,QPoint const& debut, QPoint const& fin)
{
    int debx(debut.x()<fin.x()?debut.x():fin.x());
    int finx(debut.x()>fin.x()?debut.x():fin.x());
    int deby(debut.y()<fin.y()?debut.y():fin.y());
    int finy(debut.y()>fin.y()?debut.y():fin.y());
    int width=finx-debx+1;
    int height=finy-deby+1;
    QImage im(width,height,image.format());
    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
        {
            im.setPixel(i,j,image.pixel(i+debx,j+deby) );
        }
    }
    return im;

}


QImage Fonctions::negative(QImage const& image)
{
    int height=image.height();
    int width=image.width();
    QImage im(width,height,image.format());

    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
        {
            im.setPixel(i,j, qRgb(255-qRed(image.pixel(i,j)) ,255-qGreen(image.pixel(i,j)),255-qBlue(image.pixel(i,j))) );
        }

    }
    return im;
}

QImage Fonctions::niveauDeGris(QImage const& image){
    int height=image.height();
    int width=image.width();
    QImage im(width,height,image.format());

    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
        {
            im.setPixel(i,j, Fonctions::pixelRVBaGris(image.pixel(i,j)) );
        }

    }
    return im;
}

QRgb Fonctions::pixelRVBaGris(QRgb const& pixel){
    int rouge(qRed(pixel));
    int vert(qGreen(pixel));
    int bleu(qBlue(pixel));
    int gris= rouge*0.2125 + vert*0.7154 + bleu*0.0721 ;
    if (gris<0)
    {
        gris=0;
    }
    else if(gris>255)
    {
        gris=255;
    }
    return qRgb(gris,gris,gris);
}

QImage Fonctions::redimensionner1(QImage const& image, int largeur2,int hauteur2)
{
    int hauteur1=image.height();
    int largeur1=image.width();
    QImage im(largeur2,hauteur2,image.format());

    for (int x2=0; x2<largeur2; x2++)
    {
        for (int y2=0; y2<hauteur2; y2++)
        {
            // indices du pixel correspondant dans I1
            int x1 = (int)round(x2*(largeur1-1.0)/(largeur2-1.0));
            int y1 = (int)round(y2*(hauteur1-1.0)/(hauteur2-1.0));
            im.setPixel(x2,y2, image.pixel(x1,y1) );
        }
    }


    return im;
}

QImage Fonctions::redimensionner2(QImage const& image, int largeur2,int hauteur2)
{
    int hauteur1=image.height();
    int largeur1=image.width();
    QImage im(largeur2,hauteur2,image.format());
    int xe,ye;
    float xf,yf,x1,y1;
    int rouge,vert,bleu;
    for (int x2=0; x2<largeur2-1; x2++){
            for (int y2=0; y2<hauteur2-1; y2++){
                    x1=x2*largeur1/largeur2;
                    xe=(int)x1;
                    xf=x1-xe;

                    y1=y2*hauteur1/hauteur2;
                    ye=(int)y1;
                    yf=y1-ye;

                    rouge= (1-xf) * ( (1-yf) * qRed(image.pixel(xe,ye)) + yf * qRed(image.pixel(xe,ye+1)) )
                            + xf * ( (1-yf) * qRed(image.pixel(xe+1,ye)) + yf * qRed(image.pixel(xe+1,ye+1)) );
                    vert= (1-xf) * ( (1-yf) * qGreen(image.pixel(xe,ye)) + yf * qGreen(image.pixel(xe,ye+1)) )
                            + xf * ( (1-yf) * qGreen(image.pixel(xe+1,ye)) + yf * qGreen(image.pixel(xe+1,ye+1)) );
                    bleu= (1-xf) * ( (1-yf) * qBlue(image.pixel(xe,ye)) + yf * qBlue(image.pixel(xe,ye+1)) )
                            + xf * ( (1-yf) * qBlue(image.pixel(xe+1,ye)) + yf * qBlue(image.pixel(xe+1,ye+1)) );
                    rouge = rouge<0 ? 0 : ( rouge>255 ? 255 : rouge);
                    vert = vert<0 ? 0 : ( vert>255 ? 255 : vert);
                    bleu = bleu<0 ? 0 : ( bleu>255 ? 255 : bleu);
                    im.setPixel(x2,y2,   qRgb(rouge,vert,bleu) );

            }
    }

    for (int i= 0 ;i<largeur2-1;i++)
    {
        im.setPixel(i,hauteur2-1,im.pixel(i,hauteur2-2));
    }
    for (int j= 0 ;j<hauteur2;j++)
    {
        im.setPixel(largeur2-1,j,im.pixel(largeur2-2,j));
    }
    return im;
}


QImage Fonctions::convolution(QImage const& image, Filtre filtre)
{
    int largeur = image.width();
    int hauteur = image.height();
    QImage im(largeur,hauteur,image.format());
    int n = filtre.taille();
    float rouge,vert,bleu;
    for(int x=0;x<largeur;x++){
        for(int y=0;y<hauteur;y++){
            rouge=0;
            vert=0;
            bleu=0;
            for(int i=-n;i<=n;i++){
                for(int j=-n;j<=n;j++){
                    int xr = x+i;
                    int yr = y+j;
                    if (xr<0)  xr = 0;
                    if (xr>=largeur) xr = largeur-1;
                    if (yr<0)  yr = 0;
                    if (yr>=hauteur) yr = hauteur-1;


                    rouge+= filtre(i,j)*qRed(image.pixel(xr,yr));
                    vert+= filtre(i,j)*qGreen(image.pixel(xr,yr));
                    bleu+= filtre(i,j)*qBlue(image.pixel(xr,yr));
                }
            }
            rouge = rouge<0 ? 0 : ( rouge>255 ? 255 : rouge);
            vert = vert<0 ? 0 : ( vert>255 ? 255 : vert);
            bleu = bleu<0 ? 0 : ( bleu>255 ? 255 : bleu);
            im.setPixel(x,y,qRgb(rouge,vert,bleu));
        }
    }
    return im;

}

QImage Fonctions::max(QImage &I1, QImage &I2)
{
        int L = I1.width();
        int H = I1.height();
        QImage Ires(L,H,I1.format());
        for (int i=0; i<L; i++)
        {
            for (int j=0; j<H; j++)
            {
                int gris = I1.pixel(i,j)<I2.pixel(i,j) ? qRed(I2.pixel(i,j)) : qRed(I1.pixel(i,j)) ;
                Ires.setPixel(i,j, qRgb(gris,gris,gris));
            }
        }
        return Ires;
}

QImage Fonctions::sobel(QImage const& image)
{
    Filtre filtre1(1,Filtre::Sobel1);
    Filtre filtre2(1,Filtre::Sobel2);
    QImage gris = niveauDeGris(image);
    QImage im1=Fonctions::convolution(gris,filtre1);
    QImage im2=Fonctions::convolution(gris,filtre2);
    QImage im3=max(im1,im2);
    return im2;

}

QImage Fonctions::prewitt(QImage const& image)
{
    Filtre filtre1(1,Filtre::Prewitt1);
    Filtre filtre2(1,Filtre::Prewitt2);
    QImage gris = niveauDeGris(image);
    QImage im1=Fonctions::convolution(gris,filtre1);
    QImage im2=Fonctions::convolution(gris,filtre2);
    QImage im3=max(im1,im2);
    return im2;

}

QImage Fonctions::fusionBasic(QImage const& arrierePlan,QImage const& image)
{
    QImage im(arrierePlan);
    QPainter painter(&im);
    painter.setOpacity(0.8);
    painter.drawImage(0,0,image);
    painter.end();
    return im;

}

bool Fonctions::estEnNiveauDeGris(QImage const& image)
{
    int largeur = image.width();
    int hauteur = image.height();
    for(int x=0;x<largeur;x++){
        for(int y=0;y<hauteur;y++){
            QRgb couleur = image.pixel(x,y);
            if(qRed(couleur) != qGreen(couleur) || qRed(couleur) != qBlue(couleur) ){
                return false;
            }

        }
    }
    return true;
}

QImage Fonctions::normalisation(QImage const& image,Histo histo)
{
    int largeur = image.width();
    int hauteur = image.height();
    QImage im(largeur,hauteur,image.format());
    int minRouge(histo.getMin(1));
    int maxRouge(histo.getMax(1));
    int minVert(histo.getMin(2));
    int maxVert(histo.getMax(2));
    int minBleu(histo.getMin(3));
    int maxBleu(histo.getMax(3));

    for(int x=0;x<largeur;x++){
        for(int y=0;y<hauteur;y++){
            int valeurPixelNormaliseRouge= ((qRed(image.pixel(x,y))-minRouge) * 255  )/(maxRouge-minRouge);
            int valeurPixelNormaliseVert= ((qGreen(image.pixel(x,y))-minVert) * 255  )/(maxVert-minVert);
            int valeurPixelNormaliseBleu= ((qBlue(image.pixel(x,y))-minBleu) * 255  )/(maxBleu-minBleu);
            im.setPixel(x,y,qRgb(valeurPixelNormaliseRouge,valeurPixelNormaliseVert,valeurPixelNormaliseBleu));
        }
    }

    return im;
}




QImage Fonctions::afficheHistogramme(Histo histo)
{
    int largeur(256);
    int hauteur(200);
    int max=histo.getMaxValeur();
    int num(0);
    QImage image(largeur,hauteur,QImage::Format_RGB32);
    //remplissage de noir
    for(int x=0;x<largeur;x++)
    {
        for(int y=0;y<hauteur;y++)
        {
            image.setPixel(x,y,qRgb(0,0,0));
        }
    }

    for(int x=0;x<largeur;x++)
    {

        for(int y=0;y<hauteur;y++)
        {
            num=(histo.getComposante(x,1)*hauteur) /max;
            if(num>=(hauteur-1-y)){
                image.setPixel(x,y,qRgb(255,qGreen(image.pixel(x,y)),qBlue(image.pixel(x,y)) ));
            }

            num=(histo.getComposante(x,2) *hauteur) /max;
            if(num>=(hauteur-1-y)){
                image.setPixel(x,y,qRgb(qRed(image.pixel(x,y)),255,qBlue(image.pixel(x,y)) ));
            }
            num=(histo.getComposante(x,3) *hauteur) /max;
            if(num>=(hauteur-1-y)){
                image.setPixel(x,y,qRgb(qRed(image.pixel(x,y)),qGreen(image.pixel(x,y)),255 ));
            }

        }
    }
    return image;
}



QImage Fonctions::egalisation(QImage const& image,Histo histo)
{
    int largeur = image.width();
    int hauteur = image.height();
    QImage im(largeur,hauteur,image.format());
    int nbPixel(histo.getNbPixel());

    for(int x=0;x<largeur;x++){
        for(int y=0;y<hauteur;y++){
            int valeurPixelEgaliseRouge= (histo.getComposanteCumulee(qRed(image.pixel(x,y)),1) * 255) / nbPixel;
            int valeurPixelEgaliseVert= (histo.getComposanteCumulee(qGreen(image.pixel(x,y)),2) * 255) / nbPixel;
            int valeurPixelEgaliseBleu= (histo.getComposanteCumulee(qBlue(image.pixel(x,y)),3) * 255) / nbPixel;
            im.setPixel(x,y,qRgb(valeurPixelEgaliseRouge,valeurPixelEgaliseVert,valeurPixelEgaliseBleu));
        }
    }

    return im;
}

































