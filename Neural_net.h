#ifndef _NEURAL_NET_
#define _NEURAL_NET_
#include "net_fun.h"

class Layer;
class Node
{
    //node ** represents the entire layer of nodes before this node
    // b is bias, ws is an array of weights
    Layer * lBefore;
    float b;
    float * ws;
    float activation;
    public:

    //random biases, unassigned previous layer
    Node();
    //
    Node(Layer * layerBefore, bool randomWeights = true);
    //for initial layer, where there are no weights
    Node(float act);
    //this is the only constructer that doesn't have a hint of randomness to it, as it takes info from a previously made network
    Node(istream &is, int weights, Layer * layerBefore);
    ~Node();

    void setActivation(float a);
    void setBias(float newBias){b = newBias;}
    void setWeights(float * weights);
    float getWeight(int n);
    float calcActivation();
    float getActivation(){return activation;}
    void printWeights(ostream &o);
    void printBias(ostream &o){o <<fixed<< b << "\n\n";}

    Node& operator=(const Node &a);
    Node& operator+=(const Node &a);
    Node& operator-=(const Node &a);
    Node& operator*=(float a);
    Node& operator/=(float a);

    
};
class Layer
{
    Node * myNodes;
    unsigned int size;
    
    public:
    Layer(unsigned int sz, Layer* layerBefore = 0, bool randomWeights = true);
    ~Layer();

    unsigned int getSize(){return size;}
    Node&  operator[](int i){return myNodes[i];}
    void printActivations();


    

};
class Network
{
    protected:
    const int DEFAULT_NODES_PER_LAYER = 15;
    // count of layers in basic neural net
    unsigned int layers;
    // array of layers, the entire network
    // 0th layer is input layer
    Layer ** myNet;

    public:
    //literally the most basic network I can make.
    Network(unsigned int ls);

    //makes network with random first layer
    // sizes of layers go with values in the vector
    Network(vector<int> layerSizes, bool randomWeights = true);
    Network(string name);

    Network& operator+=(const Network &a);
    Network& operator-=(const Network &a);
    Network& operator*=(float a);
    Network& operator/=(float a);

    float dCostdActivation(int layer, int node, vector<float> wantedOutput);
    void evaluate();
    void printActivations();
    float cost(vector<float> wantedOutput);
    void toFile(string name);
    void setInputLayer(vector<float> v);
    float getOutput(int i){return (*myNet[layers -1])[i].getActivation();}

    
    Network gradient(vector<float> wantedOutput);
    //sudocode for the actual learning process
    void learn();
};

vector<float> formToInput(string in, int nodeSpace, bool caseSensitive);


#endif // _NEURAL_NET_