#include "GAN.h"

GAN::GAN(string name) : Network(name)
{
    vector<int> v = getLayerSizes();
    int biggestSize = v[0];
    contentLayer = 0;
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if (v[i] > biggestSize)
        {
            contentLayer = i;
            biggestSize = v[i];
        }
    }
    evaluateFully = true;
}

GAN::GAN(vector<int> layerSizes, int contLayer, bool randomWeights) : Network(layerSizes, randomWeights)
{
    contentLayer = contLayer;
    evaluateFully = true;
}

void GAN::setInputLayer()
{
    for (unsigned int i = 0; i < myNet[0]->getSize(); i++)
    {
        (*myNet[0])[i].setActivation(rnum() * 2.0 - 1);
    }
    evaluateFully = true;
}
void GAN::setContentLayer(string input)
{
    vector<float> a = formToInput(input, myNet[contentLayer]->getSize(), false);

    for (unsigned int i = 0; i < a.size(); i++)
    {
        (*myNet[contentLayer])[i].setActivation(a[i]);
    }
    for (int i = 0; i < contentLayer; i++)
    {
        for (unsigned int j = 0; j < myNet[i]->getSize(); j++)
            (*myNet[i])[j].setActivation(0);
    }

    evaluateFully = false;
}

void GAN::evaluate()
{
    if (evaluateFully)
        Network::evaluate();
    else
    {
        for (unsigned int i = contentLayer + 1; i < layers; i++)
        {
            for (unsigned int j = 0; j < myNet[i]->getSize(); j++)
            {
                (*myNet[i])[j].calcActivation();
            }
        }
    }
}
string GAN::getContentLayer()
{
    string result;
    int dataSize = myNet[contentLayer]->getSize();

    int great;
    float greatval;
    for (int i = 0; i < dataSize / 33; i++)
    {
        //determine which index is greatest
        great = 0;
        greatval = myNet[contentLayer]->operator[](33 * i + 0).getActivation();
        for (int j = 1; j < 33; j++)
        {
            float val = myNet[contentLayer]->operator[](33 * i + j).getActivation();
            if (val >= greatval)
            {
                greatval = val;
                great = j;
            }
        }
        if(greatval <0.0001)
        {
            result.push_back('~');
            continue;
        }
        //proceeds to add that character to a string
        if (great <= 25)
        {
            result.push_back(97 + great);
        }
        else if (great == 26)
        {
            result.push_back(' ');
        }
        else if (great == 27)
        {
            result.push_back(',');
        }
        else if (great == 28)
        {
            result.push_back('.');
        }
        else if (great == 29)
        {
            result.push_back('?');
        }
        else if (great == 30)
        {
            result.push_back('!');
        }
        else if (great == 31)
        {
            result.push_back('\'');
        }
        else if (great == 32)
        {
            result.push_back('"');
        }
        
    }
    return result;
}

Network GAN::generatorGradient(vector<float> wo, float dropout)
{
    vector<int> v;
    v = getLayerSizes();

    Network grad(v, false);

    //this loop starts at the outermost layer and works in
    for (int i = contentLayer; i > 0; i--)
    {

        //this loop will run for each node
        for (int j = 0; j < v[i]; j++)
        {
            bool dropped = rnum() < dropout;

            float currentActivation = (*myNet[i])[j].getActivation();
            if(dropped) currentActivation = 0;

            Node gradientNode(myNet[i - 1], false);
            float biasGradient, *weightGradients = new float[v[i - 1]];

            float dCdA = dCostdActivation(i, j, wo);
            biasGradient = dCdA * currentActivation * (1 - currentActivation);

            //for every weight
            for (int k = 0; k < v[i - 1]; k++)
            {
                weightGradients[k] = dCdA * currentActivation * (1 - currentActivation) * (*myNet[i - 1])[k].getActivation();
            }

            //wrapping everything up and setting a node to it's gradient in the returned network
            gradientNode.setWeights(weightGradients);
            gradientNode.setBias(biasGradient);
            (*grad.myNet[i])[j] = gradientNode;
            delete[] weightGradients;
        }
    }

    return grad;
}

Network GAN::discriminatorGradient(vector<float> wo, float dropout)
{
    vector<int> v;
    v = getLayerSizes();

    Network grad(v, false);

    //this loop starts at the outermost layer and works in
    for (int i = v.size() - 1; i > contentLayer; i--)
    {

        //this loop will run for each node
        for (int j = 0; j < v[i]; j++)
        {
            bool dropped = rnum() < dropout;

            float currentActivation = (*myNet[i])[j].getActivation();
            if(dropped) currentActivation = 0;

            Node gradientNode(myNet[i - 1], false);
            float biasGradient, *weightGradients = new float[v[i - 1]];

            float dCdA = dCostdActivation(i, j, wo);
            biasGradient = dCdA * currentActivation * (1 - currentActivation);

            //for every weight
            for (int k = 0; k < v[i - 1]; k++)
            {
                weightGradients[k] = dCdA * currentActivation * (1 - currentActivation) * (*myNet[i - 1])[k].getActivation();
            }

            //wrapping everything up and setting a node to it's gradient in the returned network
            gradientNode.setWeights(weightGradients);
            gradientNode.setBias(biasGradient);
            (*grad.myNet[i])[j] = gradientNode;
            delete[] weightGradients;
        }
    }

    return grad;
}