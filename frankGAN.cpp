#include "Gen_net.h"

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

int highestIndex(vector<float> a)
{
    int index = 0;
    float inVal = a[0];

    for (unsigned int i = 0; i < a.size(); i++)
    {
        if (a[i] > inVal)
        {
            index = i;
            inVal = a[i];
        }
    }
    return index;
}

int nextHighestIndex(vector<float> a)
{
    a[highestIndex(a)] = 0;
    int index = 0;
    float inVal = a[0];

    for (unsigned int i = 0; i < a.size(); i++)
    {
        if (a[i] > inVal)
        {
            index = i;
            inVal = a[i];
        }
    }
    return index;
}

int main()
{
    srand(time(NULL));
    ifstream frank("frankenstein.txt");
    string frankstring, line, s;
    s = " ";
    while (frank)
    {
        getline(frank, line);
        frankstring += s;
        frankstring += line;
    }
    int CHARS_IN_FRANKENSTEIN = 422874;

    //determines dimentions of the bots, len is length of sentence to be interpreted.
    int len = 50;
    vector<int> discSize = {30 * len, 40, 2}, genSize = {20, 30, 33 * len};
    int nodespace = discSize[0];

    //Network discriminator(discSize, true);
    //GenNetwork mommy(genSize, true);
    //GenNetwork daddy(genSize, true);
    Network discriminator("discriminator.net");
    GenNetwork mommy("mommy.net");
    GenNetwork daddy("daddy.net");

    //will make some number of genNets and one discriminator
    int population = 50, tests = 10, correct = 0, attempted = 0;
    float mutationRate = 100;
    float learningRate = 5;
    vector<GenNetwork *> everyone(population);
    vector<float> effectiveness;

    for (int i = 2; i < population; i++)
    {
        everyone[i] = new GenNetwork(mommy.getLayerSizes(), false);
        everyone[i]->operator+=(mommy.breedWith(daddy, mutationRate));
    }
    everyone[0] = &mommy;
    everyone[1] = &daddy;

    //here come the learning
    for (int sessions = 0; sessions < 1; sessions++)
    {
        Network grad(discriminator.getLayerSizes(), false);
        effectiveness = vector<float>(population, 0);

        //first with many fake sentences
        for (int i = 0; i < population; i++)
        {

            for (int j = 0; j < tests; j++)
            {
                attempted++;
                everyone[i]->setInputLayer();
                everyone[i]->evaluate();
                discriminator.setInputLayer(formToInput(everyone[i]->as_string(), nodespace, false));
                discriminator.evaluate();

                if (discriminator.getOutput(0) < discriminator.getOutput(1))
                    correct++;

                //quantify the effectiveness as the certainty that the discriminator had in the input being from
                //the true data set.
                effectiveness[i] += discriminator.getOutput(0);
                grad += discriminator.gradient(vector<float>{0, 1}, 0.5);
            }
            effectiveness[i] /= tests;
        }
        
        //then with many real sentences
        for (int i = 0; i < population * tests; i++)
        {
            attempted++;
            //sets discriminator input layer to a 150 char string from frankenstein.
            discriminator.setInputLayer(formToInput(extractString(frankstring, rand() % CHARS_IN_FRANKENSTEIN, len), nodespace, false));
            discriminator.evaluate();

            if (discriminator.getOutput(0) > discriminator.getOutput(1))
                correct++;

            grad += discriminator.gradient(vector<float>{1, 0}, 0.5);
        }

        //now to make both nets better
        grad /= (2 * population * tests / learningRate);
        discriminator -= grad;
    }

    cout << "The Discriminator discriminated " << correct << " out of " << attempted << " correctly.\n";
    cout << "The trickiest generator was " << highestIndex(effectiveness) << endl;

    //cout some stats here, then saving all the nets
    everyone[highestIndex(effectiveness)]->toFile("mommy.net");
    everyone[nextHighestIndex(effectiveness)]->toFile("daddy.net");
    discriminator.toFile("discriminator.net");
}