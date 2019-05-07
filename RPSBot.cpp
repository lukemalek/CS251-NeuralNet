#include "RPSBot.h"

RPSBot::RPSBot(string name) : Network(name)
{
    int num = getLayerSizes()[0];
    for (int i = 0; i < num; i++)
    {
        memory.push_back(0);
    }
}
RPSBot::RPSBot(vector<int> layerSizes, bool randomWeights) : Network(layerSizes, randomWeights)
{
    int num = layerSizes[0];
    for (int i = 0; i < num; i++)
    {
        memory.push_back(0);
    }
}
int RPSBot::myMove()
{
    if (myNet[layers - 1]->getSize() != 3)
        return -1;
    float a, b, c;
    a = getOutput(0);
    b = getOutput(1);
    c = getOutput(2);
    if (b >= a && b >= c)
        return 1;
    if (c >= a && c >= b)
        return 2;
    return 0;
}
void RPSBot::addToMem(int movetype)
{
    if (movetype < 0 || movetype > 2)
    {
        cout << "invalid movetype: could not add to mem" << endl;
        return;
    }
    for (int i = memory.size() - 3; i > 2; i -= 3)
    {
        memory[i] = memory[i - 3];
        memory[i + 1] = memory[i - 2];
        memory[i + 2] = memory[i - 1];
    }
    memory[0] = 0;
    memory[1] = 0;
    memory[2] = 0;
    memory[movetype] = 1;
}
string RPSBot::sayMove()
{
    if (myMove() == 0)
        return "rock";
    if (myMove() == 1)
        return "paper";
    return "scissors";
}

Network RPSBot::gradient(int wantedMove)
{
    vector<float> wanted = {0,0,0};
    wanted[wantedMove] = 1;

    return Network::gradient(wanted);

}
void RPSBot::setInputLayer()
{
    Network::setInputLayer(memory);
    //myNet[layers-1]->printActivations();
}