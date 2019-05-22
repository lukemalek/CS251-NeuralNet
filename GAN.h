#ifndef _GAN_
#define _GAN_
#include "Neural_net.h"

//Generative Adversarial Network!!
class GAN: public Network
{
    protected: 
    //layer of the network with the most nodes, represents human readable data.
    int contentLayer;

    //very important boolean!! This guy is set to true when acting as a generator, and false when evaluating from 
    //the content layer.
    bool evaluateFully;
    public:

    //like network constructor, makes a gan from a given .net file
    GAN(string name);

    //identical to corresponding Network
    GAN(vector<int> layerSizes,int contLayer, bool randomWeights = true);

    //sets the root layer to randomly generated noise
    void setInputLayer();

    //sets the CONTENT layer (some layer within the net) to represent the given string
    void setContentLayer(string a);

    //the same as Network's evaluate, however this may start evaluating from either content layer or input layer based on what "evaluate fully" is
    void evaluate();

    //returns index of the content layer
    int getIndexContent(){return contentLayer;}

    //calculates the gradients of either the generator part or the discriminator part. Gradients are only non-zero for the part of the network they should affect.
    Network generatorGradient(vector<float> wantedOutput, float dropout = 0);
    Network discriminatorGradient(vector<float> wantedOutput, float dropout = 0);

    //returns string representation of the content layer
    string getContentLayer();

    //wanted to optimize for variance of string produced based on the noise it is given, never implemented.
    float variance();


};



#endif //_GAN_