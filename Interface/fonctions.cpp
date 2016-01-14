#include "Fonctions.h"
#include <iostream>
#include <string>
#include <QRgb>

using namespace std;

QImage decoupage(QImage const& image,QPoint const& debut, QPoint const& fin)
{
    int debx(debut.x());
    int finx(fin.x());
    int deby(debut.y());
    int finy(fin.y());
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


QImage negative(QImage const& image)
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

QImage niveauDeGris(QImage const& image){
    int height=image.height();
    int width=image.width();
    QImage im(width,height,image.format());

    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
        {
            im.setPixel(i,j, pixelRVBaGris(image.pixel(i,j)) );
        }

    }
    return im;
}

QRgb pixelRVBaGris(QRgb const& pixel){
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

QImage redimentionner1(QImage const& image, int largeur2,int hauteur2)
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

QImage redimentionner2(QImage const& image, int largeur2,int hauteur2)
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

QImage convolution(QImage const& image, Filtre filtre)
{
    int largeur = image.width();
    int hauteur = image.height();
    QImage im(largeur,hauteur,image.format());
    int n = filtre.taille();
    float rouge,vert,bleu;
    for(int x=n;x<largeur-n;x++){
        for(int y=n;y<hauteur-n;y++){
            rouge=0;
            vert=0;
            bleu=0;
            for(int i=-n;i<=n;i++){
                for(int j=-n;j<=n;j++){
                    rouge+= filtre(i,j)*qRed(image.pixel(x+i,y+i));
                    vert+= filtre(i,j)*qGreen(image.pixel(x+i,y+i));
                    bleu+= filtre(i,j)*qBlue(image.pixel(x+i,y+i));
                }
            }
            rouge = rouge<0 ? 0 : ( rouge>255 ? 255 : rouge);
            vert = vert<0 ? 0 : ( vert>255 ? 255 : vert);
            bleu = bleu<0 ? 0 : ( bleu>255 ? 255 : bleu);
            im.setPixel(x,y,qRgb(rouge,vert,bleu));
        }
    }

    //recuperation du contour
    for (int i= 0 ;i<largeur;i++)
    {
        if(i<n || i>=(largeur-n))
        {
            for (int j= 0 ;j<hauteur;j++)
            {
                im.setPixel(i,j,image.pixel(i,j));
            }
        }
        else
        {
            int j=0;
            while( j<hauteur){
                im.setPixel(i,j,image.pixel(i,j));
                if(j==n-1){
                    j=hauteur-n;
                }
                else{
                    j++;
                }
            }
        }
    }


    return im;

}







