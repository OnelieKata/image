#include "Histo.h"

using namespace std;

Histo::Histo()
{
    remplirTab();

}

Histo::Histo(QImage const& image)
{
    remplirTab();
    int height=image.height();
    int width=image.width();
    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
        {

            composante1[qRed(image.pixel(i,j))]= composante1[qRed(image.pixel(i,j))] +1;
            composante2[qGreen(image.pixel(i,j))]++;
            composante3[qBlue(image.pixel(i,j))]++;
        }

    }

}

int* Histo::getComposante(int const& num)
{
    switch ( num )
    {
    case 1:
        return composante1;
        break;
    case 2:
        return composante2;
        break;
    case 3:
        return composante3;
        break;
    default:
        return 0;
        break;
    }

}

void Histo::remplirTab()
{


    for(int i=0;i<256;i++)
    {
        composante1[i]=0;
        composante2[i]=0;
        composante3[i]=0;
    }

}

void Histo::afficher()
{
    for(int i=0;i<256;i++){
        cout << "valeur de "<<i<<" : "<<composante1[i] << endl;
    }
}

















