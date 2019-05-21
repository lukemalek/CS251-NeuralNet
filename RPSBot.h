#ifndef _RPSBot_
#define _RPSBOT_
#include "Neural_net.h"


//my Input layer better be a multiple of 3 on GOD 
//every three nodes is a move, they are "remembered" in the input layer
//from most to last recent.
class RPSBot: public Network
{
    protected:
    vector<float> memory;

    public:

    RPSBot(vector<int> layerSizes, bool randomWeights = true);
    RPSBot(string name);


    //returns the INDEX of the highest output layer, assuming 3 out layers
    int myMove();
    string sayMove();
    //0 is rock, 1 is paper, 2 is scissors. adds to most recent spot.
    void addToMem(int moveType);
    Network gradient(int wantedMove);
    void setInputLayer();
};



#endif // _RPSBot_