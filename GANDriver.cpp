#include "GAN.h"


int main()
{
    srand(time(NULL));
    const vector<int> dims{1,66,1};
    GAN bigBoy("frankGAN.net");

    bigBoy.setContentLayer("aeyvsdmh.o xe  !rhfl");
    bigBoy.evaluate();
    cout << bigBoy.getContentLayer() <<endl;
    cout << bigBoy.getOutput(0) << " " << bigBoy.getOutput(1) << endl;

    bigBoy.setInputLayer();
    bigBoy.evaluate();
    cout << bigBoy.getContentLayer()<<endl;
    cout << bigBoy.getOutput(0) << " " << bigBoy.getOutput(1) << endl;


}