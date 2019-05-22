#include "Neural_net.h"

Node::Node()
{
    //assumes that node is in base layer
    lBefore = 0;
    b = 0;
    ws = 0;
    activation = rnum();
}
Node::Node(float act)
{
    //assume thats node is in base layer
    lBefore = 0;
    b = 0;
    ws = 0;
    activation = act;
}
Node::Node(Layer *layerBefore, bool randomWeights, bool allones)
{
    //initialize random or zero net, not in base layer

    if (randomWeights)
        b = 2 * rnum() - 1;
    else
    {
        b = 0;
    }

    lBefore = layerBefore;
    activation = 0;
    //initialize weights as random or 0
    ws = new float[lBefore->getSize()];
    if (randomWeights)
        for (unsigned int i = 0; i < lBefore->getSize(); i++)
            ws[i] = 2 * rnum() - 1;
    else
    {
        if(allones)
            for (unsigned int i = 0; i < lBefore->getSize(); i++)
                ws[i] = 1;
        else
            for (unsigned int i = 0; i < lBefore->getSize(); i++)
                ws[i] = 0;
    }
}
Node::Node(istream &is, int weights, Layer *layerBefore)
{
    ws = new float[weights];
    lBefore = layerBefore;
    for (int i = 0; i < weights; i++)
    {
        is >> ws[i];
    }
    is >> b;
}
Node::~Node()
{
    if (ws)
        delete[] ws;
}
Node &Node::operator=(const Node &a)
{
    if (ws)
        delete[] ws;
    b = a.b;
    activation = a.activation;
    lBefore = a.lBefore;
    ws = new float[lBefore->getSize()];
    for (unsigned int i = 0; i < lBefore->getSize(); i++)
        ws[i] = a.ws[i];

    return *this;
}
Node &Node::operator*=(float a)
{
    b *= a;
    if (ws)
    {
        int numWeights = lBefore->getSize();
        for (int i = 0; i < numWeights; i++)
        {
            ws[i] *= a;
        }
    }
    return *this;
}
Node &Node::operator/=(float a)
{
    b /= a;
    if (ws)
    {
        int numWeights = lBefore->getSize();
        for (int i = 0; i < numWeights; i++)
        {
            ws[i] /= a;
        }
    }
    return *this;
}
Node &Node::operator+=(const Node &a)
{
    unsigned int weights = lBefore->getSize();
    if (weights != a.lBefore->getSize())
    {
        cerr << "un-add-able Nodes" << endl;
        return *this;
    }
    b += a.b;
    if (ws)
    {
        for (unsigned int i = 0; i < weights; i++)
        {
            ws[i] += a.ws[i];
        }
    }
    return *this;
}
Node &Node::operator-=(const Node &a)
{
    unsigned int weights = lBefore->getSize();
    if (weights != a.lBefore->getSize())
    {
        cerr << "un-subtractable-able Nodes" << endl;
        return *this;
    }
    b -= a.b;
    if (ws)
    {
        for (unsigned int i = 0; i < weights; i++)
        {
            ws[i] -= a.ws[i];
        }
    }
    return *this;
}
float Node::getWeight(int n)
{
    if (ws)
    {
        return ws[n];
    }
    return 0;
}
float Node::calcActivation()
{
    //sets AND returns the activation of the node
    if (ws)
    {
        double sum = b;
        for (unsigned int i = 0; i < lBefore->getSize(); i++)
            sum += (*lBefore)[i].getActivation() * ws[i];
        activation = sig(sum);
    }
    return activation;
}
void Node::setActivation(float a)
{
    if (a < 0)
        a = 0;
    else if (a > 1)
        a = 1;
    activation = a;
}
void Node::setWeights(float *weights)
{
    if (ws)
        delete[] ws;

    ws = new float[lBefore->getSize()];
    for (unsigned int i = 0; i < lBefore->getSize(); i++)
    {
        ws[i] = weights[i];
    }
}
void Node::printWeights(ostream &o)
{
    for (unsigned int i = 0; i < lBefore->getSize(); i++)
        o << fixed << ws[i] << '\n';
}

Layer::Layer(unsigned int sz, Layer *layerBefore, bool randomWeights, bool allones)
{
    size = sz;
    //myNodes = new Node(layerBefore)[sz];
    myNodes = new Node[sz];
    if (layerBefore)
    {
        for (unsigned int i = 0; i < sz; i++)
            myNodes[i] = Node(layerBefore, randomWeights,allones);
    }
}
Layer::~Layer()
{
    for (unsigned int i = 0; i < size; i++)
    {
        myNodes[i].~Node();
    }
    
    //if (myNodes)
    //    delete[] myNodes;
    
}
void Layer::printActivations()
{
    for (unsigned int i = 0; i < size; i++)
        cout << "(" << myNodes[i].getActivation() << ")";
    cout << endl;
}

Network::Network(unsigned int ls)
{
    layers = ls;
    myNet = new Layer *[ls];
    myNet[0] = new Layer(DEFAULT_NODES_PER_LAYER);
    for (unsigned int i = 1; i < ls; i++)
    {
        myNet[i] = new Layer(DEFAULT_NODES_PER_LAYER, myNet[i - 1]);
    }
}
Network::Network(vector<int> v, bool randomWeights, bool allones)
{
    layers = v.size();
    myNet = new Layer *[layers];
    myNet[0] = new Layer(v[0]);
    for (unsigned int i = 1; i < layers; i++)
    {
        myNet[i] = new Layer(v[i], myNet[i - 1], randomWeights,allones);
    }
}
Network::Network(string name)
{

    ifstream ifs(name.c_str());

    vector<int> v;
    int a, b;
    ifs >> a;
    for (int i = 0; i < a; i++)
    {
        ifs >> b;
        v.push_back(b);
    }

    layers = v.size();
    myNet = new Layer *[layers];
    myNet[0] = new Layer(v[0]);
    //make a rightful amount of layers
    for (unsigned int i = 1; i < layers; i++)
    {
        myNet[i] = new Layer(v[i], myNet[i - 1]);
        //for each node in the layer
        int prevLayerSize = myNet[i - 1]->getSize();
        for (unsigned int j = 0; j < myNet[i]->getSize(); j++)
        {
            (*myNet[i])[j] = Node(ifs, prevLayerSize, myNet[i - 1]);
        }
    }
}
Network::~Network()
{
    
    for(unsigned int i = 0; i< layers; i++)
    {
        if(myNet[i])myNet[i]->~Layer();
    }
    
    if(myNet) delete myNet;

}
void Network::evaluate()
{
    for (unsigned int i = 1; i < layers; i++)
    {
        for (unsigned int j = 0; j < myNet[i]->getSize(); j++)
        {
            (*myNet[i])[j].calcActivation();
        }
    }
}
void Network::printActivations()
{
    for (unsigned int i = 0; i < layers; i++)
    {
        myNet[i]->printActivations();
    }
}
float Network::cost(vector<float> wantedOutput)
{
    if (wantedOutput.size() != myNet[layers - 1]->getSize())
    {
        cerr << "Wanted Output doesn not match size of actual output, returning -1" << endl;
        return -1;
    }

    float cost = 0;
    for (unsigned int i = 0; i < wantedOutput.size(); i++)
    {
        cost += pow(wantedOutput[i] - (*myNet[layers - 1])[i].getActivation(), 2);
    }
    return cost;
}

void Network::toFile(string name)
{
    ofstream newfile;
    newfile.open(name.c_str());
    //first line, says how many layers
    newfile << layers << endl;
    //second line, says dimentions of the net in the oder that a constructor would take them.
    for (unsigned int i = 0; i < layers; i++)
    {
        newfile << myNet[i]->getSize() << ' ';
    }
    newfile << endl;
    //all that is left to print is weights then biases, but that will not be easy.
    //outside for loop is what to do for each layer, starting at the second because first has no weights.
    for (unsigned int i = 1; i < layers; i++)
    {
        //for each node
        for (unsigned int j = 0; j < myNet[i]->getSize(); j++)
        {
            (*myNet[i])[j].printWeights(newfile);
            (*myNet[i])[j].printBias(newfile);
        }
    }

    newfile.close();
}
Network &Network::operator*=(float a)
{
    for (unsigned int i = 1; i < layers; i++)
    {
        int layerSize = (*myNet[i]).getSize();
        for (int j = 0; j < layerSize; j++)
        {
            (*myNet[i])[j] *= a;
        }
    }
    return *this;
}
Network &Network::operator/=(float a)
{
    for (unsigned int i = 1; i < layers; i++)
    {
        int layerSize = (*myNet[i]).getSize();
        for (int j = 0; j < layerSize; j++)
        {
            (*myNet[i])[j] /= a;
        }
    }
    return *this;
}
Network &Network::operator+=(const Network &a)
{
    for (unsigned int i = 1; i < layers; i++)
    {
        int layerSize = (*myNet[i]).getSize();
        for (int j = 0; j < layerSize; j++)
        {
            (*myNet[i])[j] += (*a.myNet[i])[j];
        }
    }
    return *this;
}
Network &Network::operator-=(const Network &a)
{
    for (unsigned int i = 1; i < layers; i++)
    {
        int layerSize = (*myNet[i]).getSize();
        for (int j = 0; j < layerSize; j++)
        {
            (*myNet[i])[j] -= (*a.myNet[i])[j];
        }
    }
    return *this;
}

Network Network::gradient(vector<float> wo, float dropout)
{
    vector<int> v;
    v = getLayerSizes();

    Network grad(v, false);

    //this loop starts at the outermost layer and works in
    for (int i = v.size() - 1; i > 0; i--)
    {

        //this loop will run for each node
        for (int j = 0; j < v[i]; j++)
        {
            //determines if the given activation will be treated as a zero,
            bool dropped = rnum() < dropout;

            float currentActivation = (*myNet[i])[j].getActivation();
            if(dropped) currentActivation = 0;

            //puts the wanted changes into a new node called "gradientNode"
            Node gradientNode(myNet[i - 1], false);
            float biasGradient, *weightGradients = new float[v[i - 1]];

            float dCdA = dCostdActivation(i, j, wo);
            biasGradient = dCdA * currentActivation * (1 - currentActivation);

            //for every weight
            for (int k = 0; k < v[i - 1]; k++)
            {
                weightGradients[k] = dCdA * currentActivation * (1 - currentActivation) * ((*myNet[i - 1])[k].getActivation());
            }

            //wrapping everything up and setting a node to its gradient in the returned network
            gradientNode.setWeights(weightGradients);
            gradientNode.setBias(biasGradient);
            (*grad.myNet[i])[j] = gradientNode;
            delete[] weightGradients;
        }
    }

    return grad;
}
float Network::dCostdActivation(int l, int n, vector<float> wantO)
{
    int iterations = layers - l;
    float value = 0;
    //Only if iterations is one will the function not be called recursively.
    //at the outermost layer, change in cost with respect to activation is simply the difference of the two
    if (iterations == 1)
    {
        value = (*myNet[l])[n].getActivation() - wantO[n];
        return value;
    }
    else
    {
        //calculating a gross sum of partial derivatives
        int bounds = myNet[l + 1]->getSize();
        for (int i = 0; i < bounds; i++)
        {
            value += dCostdActivation(l + 1, i, wantO) * ((*myNet[l + 1])[i].getActivation()) * (1 - ((*myNet[l + 1])[i].getActivation())) * (*myNet[l + 1])[i].getWeight(n);
        }
        return value;
    }

    return 0;
}
void Network::setInputLayer(vector<float> v)
{
    if (v.size() == myNet[0]->getSize())
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            (*myNet[0])[i].setActivation(v[i]);
        }
    }
    //will not set activation if sizes don't match
    else
        cout << "you goofed" << endl;
}
vector<float> formToInput(string in, int nodeSpace, bool caseSensitive)
{
    vector<float> result;
    for (int i = 0; i < nodeSpace; i++)
    {
        result.push_back(0);
    }
    /*
    for case sensitive nets, 0-25 are a-z, 26-51 are A-Z, 52 is space, 
    53 is punctuation, 54 is number, 55 is other.
    */
    if (caseSensitive)
    {
        for (unsigned int i = 0; i < in.size() && nodeSpace > 56; i++)
        {
            //is a lowercase letter
            if (in[i] >= 97 && in[i] <= 122)
            {
                result[56 * i + in[i] - 97] = 1;
            }
            //uppecase, -39 makes it so A goes to spot 26
            else if (in[i] >= 65 && in[i] <= 90)
            {
                result[56 * i + in[i] - 39] = 1;
            }
            //space
            else if (in[i] == 32)
            {
                result[56 * i + 52] = 1;
            }
            //punctuation
            else if (in[i] == ',' || in[i] == '.' || in[i] == '!' || in[i] == ';' || in[i] == '?')
            {
                result[56 * i + 53] = 1;
            }
            else if (in[i] >= '0' && in[i] <= '9')
            {
                result[56 * i + 54] = 1;
            }
            else
            {
                result[56 * i + 55] = 1;
            }
            
            nodeSpace -= 56;
        }
        return result;
    }
    //when formatting for word AIs that are NOT CASE SENSITIVE, 
    //nodes 0-25 are for 'a' thru 'z'
    // 26 for space, 27 for comma, 28 for period, and 29 for question mark, 30 for exclamation
    //31 for single quote, 32 for double quote
    for (unsigned int i = 0; i < in.size() && nodeSpace >= 33; i++)
    {
        //is a lowercase letter
        if (in[i] >= 97 && in[i] <= 122)
        {
            result[33 * i + in[i] - 97] = 1;
        }
        //uppecase
        else if (in[i] >= 65 && in[i] <= 90)
        {
            result[33 * i + in[i] - 65] = 1;
        }
        //space
        else if (in[i] == 32)
        {
            result[33 * i + 26] = 1;
        }
        //comma
        else if (in[i] == ',' )
        {
            result[33 * i + 27] = 1;
        }
        //period
        else if(in[i] == '.')
        {
            result[33 * i + 28] = 1;
        }
        //question mark
        else if(in[i] == '?')
        {
            result[33 * i + 29] = 1;
        }//exclame
        else if (in[i] == '!' )
        {
            result[33 * i + 30] = 1;
        }
        //single quote
        else if(in[i] == '\'')
        {
            result[33 * i + 31] = 1;
        }
        //doubel quote
        else if(in[i] == '"')
        {
            result[33 * i + 32] = 1;
        }
        
        nodeSpace -= 33;
    }
    return result;
}
vector<int> Network::getLayerSizes()
{
    vector<int> result;
    for(unsigned int i = 0; i<layers; i++)
    {
        result.push_back(myNet[i]->getSize());
    }
    return result;
}
string extractString(string a, int index, int length)
{
    string result;
    if (index + length > (int)a.size())
    {
        length = a.size() - index;
    }
    for (int i = 0; i < length; i++)
    {
        result.push_back(a[index + i]);
    }
    return result;
}

/*
void Network::learn()
{
    vector<float> * trainingData;
    int subsetSize;
    //init temporary gradient network
    vector<int> v;
    for (unsigned int i = 0; i<layers; i++)
    {
        v.push_back(myNet[i]->getSize());
    }
    Network temp(v, false);

    
    for(int i = 0; i< subsetSize; i++)
    {
        evaluate();
        temp += gradient(trainingData[i]);

    }
    //makes an average gradient
    temp /= subsetSize;
     
    *this-= temp;



}*/