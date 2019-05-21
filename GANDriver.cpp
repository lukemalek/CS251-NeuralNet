#include "GAN.h"


int main()
{
    
    GAN one("PRESENTABLEfrankGAN.net");

    for(int i = 0; i< 10; i++)
    {
        one.setInputLayer();
        one.evaluate();
        cout << one.getContentLayer() << endl;
    }
    /*
    bigBoy.setContentLayer("aeyvsdmh.o xe  !rhfl");
    bigBoy.evaluate();
    cout << bigBoy.getContentLayer() <<endl;
    cout << bigBoy.getOutput(0) << " " << bigBoy.getOutput(1) << endl;

    bigBoy.setInputLayer();
    bigBoy.evaluate();
    cout << bigBoy.getContentLayer()<<endl;
    cout << bigBoy.getOutput(0) << " " << bigBoy.getOutput(1) << endl;
*/

}