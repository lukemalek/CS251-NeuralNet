#include "GAN.h"

int main()
{
    srand(time(NULL));
    ifstream frank("frankenstein.txt");
    string frankstring, line, s;
    s = " ";
    while (frank)
    {
        getline(frank, line);
        frankstring += s;
        frankstring += line;
    }
    int CHARS_IN_FRANKENSTEIN = 422874;

    int len = 200;
    vector<int> dims = {50, len * 33, 20, 2};

    //GAN frankGAN(dims, 1, true);
    //frankGAN *= 0.2;
    GAN frankGAN("longFrankGAN.net");

    int rounds = 3, subset = 20, correct = 0, attempted = 0;
    float discrate = 3, genrate = 7, chaosrate= 0.0;

    for (int i = 0; i < rounds; i++)
    {
        GAN discgrad(frankGAN.getLayerSizes(), 1, false);
        GAN gengrad(frankGAN.getLayerSizes(), 1, false);

        //fake data
        for (int i = 0; i < subset; i++)
        {
            attempted++;
            frankGAN.setInputLayer();
            frankGAN.evaluate();

            if (frankGAN.getOutput(0) < frankGAN.getOutput(1))
                correct++;

            discgrad += frankGAN.discriminatorGradient(vector<float>{0,1}, 0.5);

            gengrad += frankGAN.generatorGradient(vector<float>{1,0},0.4);


            
        }
        //real data
        for (int i = 0; i < subset; i++)
        {
            attempted++;
            frankGAN.setContentLayer(extractString(frankstring, rand() % CHARS_IN_FRANKENSTEIN, len));
            frankGAN.evaluate();

            discgrad += frankGAN.discriminatorGradient(vector<float>{1, 0}, 0.5);

            if (frankGAN.getOutput(0) > frankGAN.getOutput(1))
                correct++;
        }
        discgrad *= discrate;
        gengrad *= genrate;
        frankGAN -= discgrad;
        frankGAN -= gengrad;

        Network chaos(frankGAN.getLayerSizes(), true);
        chaos *= chaosrate;

        frankGAN+= chaos;
        frankGAN.setInputLayer();
        frankGAN.evaluate();
        cout << frankGAN.getContentLayer() << "    ("<< (float)correct / attempted << " discriminated)" <<endl;
    }

    frankGAN.toFile("longFrankGAN.net");
}