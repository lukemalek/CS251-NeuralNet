#ifndef _GEN_NET_
#define _GEN_NET_
#include "Neural_net.h"


class GenNetwork: public Network
{
    public:


    GenNetwork(string name): Network(name){}
    GenNetwork(vector<int> layerSizes, bool randomWeights = true, bool allones = false) : Network(layerSizes, randomWeights, allones){}

    void setInputLayer();
    //specific to nets that generate text
    string as_string();

    GenNetwork breedWith(GenNetwork &a, float mutation);

};


#endif //_GEN_NET_