#include "GAN.h"


int main()
{
    //initializes an instance of a GAN based on the name I give it.
    GAN one("PRESENTABLEfrankGAN.net");

    //ten times, noise is given and the content layer is shown.
    for(int i = 0; i< 10; i++)
    {
        one.setInputLayer();
        one.evaluate();
        cout << one.getContentLayer() << endl;
    }
    

}