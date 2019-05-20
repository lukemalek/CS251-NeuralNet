#include "Gen_net.h"

GenNetwork::GenNetwork(string name) : Network(name)
{
    distribution = normal_distribution<float>(1, 1);
}

GenNetwork::GenNetwork(vector<int> layerSizes, bool randomWeights) : Network(layerSizes, randomWeights)
{
    distribution = normal_distribution<float>(1, 1);
}

void GenNetwork::setInputLayer()
{
    for (unsigned int i = 0; i < myNet[0]->getSize(); i++)
    {
        (*myNet[0])[i].setActivation(distribution(generator));
    }
}

string GenNetwork::as_string()
{
    //index 33*i + 0-25 are letters, 26 is space, 27 is comma,
    //28 is period, 29 is question mark, 30 is exclamation point
    //31 is single quote, 32 is double quote.

    string result;
    int dataSize = myNet[layers - 1]->getSize();

    int great;
    float greatval;
    for (int i = 0; i < dataSize / 33; i++)
    {
        //determine which index is greatest
        great = 0;
        greatval = getOutput(33 * i);
        for (int j = 1; j < 33; j++)
        {
            float val = getOutput(33 * i + j);
            if (val > greatval)
            {
                greatval = val;
                great = j;
            }
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
        else
        {
            result.push_back('"');
        }
    }
    return result;
}