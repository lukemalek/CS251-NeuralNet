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

    int len = 30;
    vector<int> dims = {30, len * 33, 30, 2};

    GAN frankGAN(dims, 1, true);
    frankGAN *= 0.2;
    //GAN frankGAN("frankGAN.net");

    int rounds = 5, subset = 10, correct = 0, attempted = 0;
    float discrate = 0.1, genrate = 0.1;

    for (int i = 0; i < rounds; i++)
    {
        GAN discgrad(frankGAN.getLayerSizes(), 2, false);
        GAN gengrad(frankGAN.getLayerSizes(), 2, false);

        //fake data
        for (int i = 0; i < subset; i++)
        {
            attempted++;
            frankGAN.setInputLayer();
            frankGAN.evaluate();

            if (frankGAN.getOutput(0) < frankGAN.getOutput(1))
                correct++;

            discgrad += frankGAN.discriminatorGradient(vector<float>{0,1}, 0.4);

            gengrad += frankGAN.generatorGradient(vector<float>{1,0});


            
        }
        //real data
        for (int i = 0; i < subset; i++)
        {
            attempted++;
            frankGAN.setContentLayer(extractString(frankstring, rand() % CHARS_IN_FRANKENSTEIN, len));
            frankGAN.evaluate();

            discgrad += frankGAN.discriminatorGradient(vector<float>{1, 0}, 0.4);

            if (frankGAN.getOutput(0) > frankGAN.getOutput(1))
                correct++;
        }
        cout << "The Discriminator discriminated " << correct << " out of " << attempted << " correctly.\n";
        discgrad *= discrate;
        gengrad *= genrate;
        frankGAN -= discgrad;
        frankGAN -= gengrad;
    }

    frankGAN.toFile("frankGAN.net");
}