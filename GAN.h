#ifndef _GAN_
#define _GAN_
#include "Neural_net.h"

class GAN: public Network
{
    protected: 
    //layer of the network with the most nodes, represents human readable data.
    int contentLayer;

    //very important boolean!! This guy is set to true when acting as a generator, and false when evaluating from 
    //the content layer.
    bool evaluateFully;
    public:

    GAN(string name);
    GAN(vector<int> layerSizes,int contLayer, bool randomWeights = true);

    void setInputLayer();
    void setContentLayer(string a);
    void evaluate();

    Network generatorGradient(vector<float> wantedOutput, float dropout = 0);
    Network discriminatorGradient(vector<float> wantedOutput, float dropout = 0);
    string getContentLayer();

};


#endif //_GAN_