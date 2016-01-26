#include "histo.h"

using namespace std;

Histo::Histo() : min1(0) , max1(0),min2(0) , max2(0),min3(0) , max3(0), maxValeur(0), nbPixel(0)
{
    remplirTab();

}

Histo::Histo(QImage const& image,bool estEnRVB) : min1(-1) , max1(-1),min2(-1) , max2(-1),min3(-1) , max3(-1), maxValeur(0), nbPixel(0)
{
    remplirTab();
    int largeur=image.width();
    int hauteur=image.height();
    nbPixel=largeur*hauteur;
    for(int j=0;j<hauteur;j++)
    {
        for(int i=0;i<largeur;i++)
        {
            if(estEnRVB){
                composante1[qRed(image.pixel(i,j))]++;
                composante2[qGreen(image.pixel(i,j))]++;
                composante3[qBlue(image.pixel(i,j))]++;
            }else{
                Yuv yuv=Yuv(image.pixel(i,j));
                composante1[yuv.getY()]++;
                composante2[yuv.getU()]++;
                composante3[yuv.getV()]++;
            }
        }

    }
    composanteCumulee1[0]=composante1[0];
    composanteCumulee2[0]=composante2[0];
    composanteCumulee3[0]=composante3[0];
    for(int i=1;i<Taille;i++)
    {
        composanteCumulee1[i]=composanteCumulee1[i-1]+composante1[i];
        composanteCumulee2[i]=composanteCumulee2[i-1]+composante2[i];
        composanteCumulee3[i]=composanteCumulee3[i-1]+composante3[i];
    }
    rechercheMin();
    rechercheMax();
    rechercheMaxValeur();
}

int Histo::getComposante(int indice,int numComposante)
{
    switch ( numComposante )
    {
    case 1:
        return composante1[indice];
        break;
    case 2:
        return composante2[indice];
        break;
    case 3:
        return composante3[indice];
        break;
    default:
        return composante1[indice];
        break;
    }

}

int Histo::getComposanteCumulee(int indice,int numComposante)
{
    switch ( numComposante )
    {
    case 1:
        return composanteCumulee1[indice];
        break;
    case 2:
        return composanteCumulee2[indice];
        break;
    case 3:
        return composanteCumulee3[indice];
        break;
    default:
        return composanteCumulee1[indice];
        break;
    }
}


int Histo::getMin(int num )
{
    switch (num)
    {
    case 1: return min1;
    case 2: return min2;
    case 3: return min3;
    default: return min1;
    }
}

int Histo::getMax(int num )
{
    switch (num)
    {
    case 1: return max1;
    case 2: return max2;
    case 3: return max3;
    default: return max1;
    }
}

int Histo::getMaxValeur()
{
    return maxValeur;
}

int Histo::getNbPixel()
{
    return nbPixel;
}


void Histo::remplirTab()
{


    for(int i=0;i<Taille;i++)
    {
        composante1[i]=0;
        composante2[i]=0;
        composante3[i]=0;
        composanteCumulee1[i]=0;
        composanteCumulee2[i]=0;
        composanteCumulee3[i]=0;
    }

}

void Histo::rechercheMin()
{
    for(int i=0;i<Taille;i++)
    {
        if(min1 != -1)
        {
            break;
        }
        if(composante1[i]!=0){
            min1=i;
        }
    }

    for(int i=0;i<Taille;i++)
    {
        if(min2 != -1)
        {
            break;
        }
        if(composante2[i]!=0){
            min2=i;
        }
    }

    for(int i=0;i<Taille;i++)
    {
        if(min3 != -1)
        {
            break;
        }
        if(composante3[i]!=0){
            min3=i;
        }
    }
}

void Histo::rechercheMax()
{

    for(int i=Taille-1;i>=0;i--)
    {
        if(max1 != -1)
        {
            break;
        }
        if(composante1[i]!=0){
            max1=i;
        }
    }

    for(int i=Taille-1;i>=0;i--)
    {
        if(max2 != -1)
        {
            break;
        }
        if(composante2[i]!=0){
            max2=i;
        }
    }

    for(int i=Taille-1;i>=0;i--)
    {
        if(max3 != -1)
        {
            break;
        }
        if(composante3[i]!=0){
            max3=i;
        }
    }
}

void Histo::rechercheMaxValeur()
{
    for(int i=0;i<Taille;i++)
    {
        if(maxValeur<composante1[i]){
            maxValeur=composante1[i];
        }
        if(maxValeur<composante2[i]){
            maxValeur=composante2[i];
        }
        if(maxValeur<composante3[i]){
            maxValeur=composante3[i];
        }
    }
}

void Histo::afficher()
{
    for(int i=0;i<Taille;i++){
        cout << "valeur de "<<i<<" : "<<composante1[i] << endl;
    }
}

















