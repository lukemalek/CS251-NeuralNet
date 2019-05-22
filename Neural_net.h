#ifndef _NEURAL_NET_
#define _NEURAL_NET_
#include "net_fun.h"



class Layer;


class Node
{
    // this points to the Layer object that affects this node's activation.
    Layer * lBefore;

    //bias is a little extra value added to the product to the dot product of the previous layer's activation to this nodes
    //own weights
    float b;

    //a dynamically-allocated array of floats, one for every node in the previous layer
    float * ws;

    //a value from 0 to 1 representing how "bright" of an influence this node is.
    float activation;
    public:

    //random biases, unassigned previous layer, mostly unused
    Node();
    
    //used to create a node given a pointer to a previous layer. options included to fill weights randomly or with all zeros or ones
    Node(Layer * layerBefore, bool randomWeights = true, bool allones = false);
    
    //for initial layer, where there are no weights
    Node(float act);

    //makes a node based on input from a file called [anything].net
    Node(istream &is, int weights, Layer * layerBefore);

    //descructor
    ~Node();

    //setters for every varient value that a node has. There is no reason for a Layer* setter because that stays constant throughout any program.
    void setActivation(float a);
    void setBias(float newBias){b = newBias;}
    void setWeights(float * weights);


    //various getters and calculations, calcActivation is the sigmoid function used on bias + weights .(dot prod with) previous activations
    float getWeight(int n);
    float calcActivation();
    float getActivation(){return activation;}
    float getBias(){return b;}
    void printWeights(ostream &o);
    void printBias(ostream &o){o <<fixed<< b << "\n\n";}

    //assignment operator
    Node& operator=(const Node &a);

    //sets the weights and bias of one node to the sum/difference of its own and another. very useful for moving along gradient during gradient descent
    Node& operator+=(const Node &a);
    Node& operator-=(const Node &a);

    //multiplies all float values by a scalar, again, useful in moving and calc-ing gradient
    Node& operator*=(float a);
    Node& operator/=(float a);

    
};
class Layer
{
    //dynamically allocated array of nodes
    Node * myNodes;

    //nodes in the dynamic array of nodes
    unsigned int size;
    
    public:

    //creates a layer given number of nodes, pointer to previous layer (defaults to no previous layer), and extra switches for filling
    //all nodes' weights or biases with zeros or ones or all random.
    Layer(unsigned int sz, Layer* layerBefore = 0, bool randomWeights = true, bool allones = false);

    //destructor
    ~Layer();

    //getter for nodes in layer
    unsigned int getSize(){return size;}

    //returns a reference to a certain node in the array of "myNodes"
    Node&  operator[](int i){return myNodes[i];}

    //purely visual, shows the activation of the nodes in the layer.
    void printActivations();


    

};
class Network
{
    protected:
    //a mostly unused value that is used in the very basic constructors
    const int DEFAULT_NODES_PER_LAYER = 15;

    // count of layers in basic neural net
    unsigned int layers;
    public:

    // array of layers, the entire network
    // 0th layer is input layer, layers-1 layer is output
    Layer ** myNet; 

    
    //literally the most basic network that can be made, makes layers the size of the DEFAULT_NODES_PER_LAYER
    Network(unsigned int ls);

    //makes network with random first layer
    // sizes of layers go with values in the vector<int>
    Network(vector<int> layerSizes, bool randomWeights = true, bool allones = false);

    //loads in a previously existing network, generally called [anything].net
    Network(string name);

    //destructor
    ~Network();

    //if both networks have identical layer sizes, adds ALL corresponding nodes together.
    //extremely important in storing and moving along the gradient of the cost function during gradient descent
    Network& operator+=(const Network &a);
    Network& operator-=(const Network &a);

    //multiplies every float value related to the network by some scalar. great for scaling the gradient
    Network& operator*=(float a);
    Network& operator/=(float a);

    //goes from root layers to output layers, having every node calculate it's activation before moving onto the next layer.
    void evaluate();

    //prints in cout the activation of all nodes in the network. Very unruly for big nets.
    void printActivations();
    
    //creates a re-loadable text file that saves a network. 
    void toFile(string name);

    //sets the activavtion of the input nodes to match the float values in the vector
    void setInputLayer(vector<float> v);
    
    //returns the activation of the i'th output node
    float getOutput(int i){return (*myNet[layers -1])[i].getActivation();}

    //returns the number of nodes in the base layer
    int getInputSize(){return myNet[0]->getSize();}
    vector<int> getLayerSizes();
    
    //the heart and soul of the actual learning that goes on. Given a vector of what the output layer should have said, 
    // gradient calculates how to change every single weight or bias in order to MAXIMIZE the cost function. We end up subtracting the 
    //gradient from the net that is learning to minimize the cost function.
    //the cost function represents how "right" or "wrong" the network is given a certain desired output. A good network will often evaluate a small cost
    Network gradient(vector<float> wantedOutput, float dropout = 0);
    float cost(vector<float> wantedOutput);

    //pivotal in calculating the gradient, returns how much the cost is affected given a slight change in a certain node's
    //activation. is a recursive function.
    float dCostdActivation(int layer, int node, vector<float> wantedOutput);

    //sudocode for the actual learning process, never actually used
    void learn();
};

//forms a string to a float vector that can be interpreted by a network
vector<float> formToInput(string in, int nodeSpace, bool caseSensitive);

//useful in extracting text from book files.
string extractString(string a, int index, int length);



#endif // _NEURAL_NET_