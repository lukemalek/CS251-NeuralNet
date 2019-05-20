#ifndef _GEN_NET_
#define _GEN_NET_
#include "Neural_net.h"


class GenNetwork: public Network
{
    protected:
    std::normal_distribution<float> distribution;
    std::default_random_engine generator;
    public:


    GenNetwork(string name);
    GenNetwork(vector<int> layerSizes, bool randomWeights = true);

    void setInputLayer();
    //specific to nets that generate text
    string as_string();


};

#endif //_GEN_NET_