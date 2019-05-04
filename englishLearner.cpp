#include "Neural_net.h"

vector<float> formToInput(string in,int nodeSpace)
{
    //when formatting for word AIs, nodes 0-25 are for 'a' thru 'z'
    // 26 for space, 27 for punctuation, all empty for other.
    vector<float> result;
    for(int i = 0;i<nodeSpace; i++)
    {
        result.push_back(0);
    }
    
    for(unsigned int i = 0; i< in.size()&& nodeSpace >28; i++)
    {
        //is a lowercase letter
        if(in[i]>= 97 && in[i] <=122)
        {
            result[28 * i + in[i] -97] = 1;
        }
        //uppecase
        else if(in[i]>= 65 && in[i] <=90)
        {
            result[28 * i + in[i] -65] = 1;
        }
        //space
        else if(in[i] == 32)
        {
            result[28 * i + 26] = 1;
        }
        //punctuation
        else if(in[i] == ',' || in[i] == '.' || in[i] == '!' || in[i] == ';' || in[i] == '?')
        {
            result[28* i + 27] =1;
        }
        nodeSpace -= 28;
    }
    return result;

}


int main()
{
    srand(time(NULL));
    const vector<int> dimentions = {28*90, 40, 2};
    int firstLayer = dimentions[0];

    ifstream english("frankenstein.txt");
    ifstream gibberish("gibberish.txt");

    vector<string> engData, gibData;
    for ( int i = 0; i<7720; i++)
    {
        string line; 
        getline(english,line);
        engData.push_back(line);
    }
    for(int i = 0; i<5334; i++)
    {
        string line; 
        getline(gibberish,line);
        gibData.push_back(line);
    }

    Network learner("english.net");
    int subsetSize = 10, rate = 5;

    for(int i = 0; i< 80; i++)
    {
        float boop = 0;
        Network temp(dimentions, false);
        for(int j = 0; j<subsetSize; j++)
        {
            vector<float> input, wanted(2);
            if(rnum() > 0.01)
            {
                int spot = (int)(7720 * rnum());
                input = formToInput(engData[spot],firstLayer);
                wanted[0] =1;
                wanted[1] = 0;
            }
            else
            {
                int spot = (int)(5334 * rnum());
                input = formToInput(gibData[spot],firstLayer);
                wanted[0] = 0;
                wanted[1] = 1;
            }
            learner.setInputLayer(input);
            learner.evaluate();
            
            
            temp += learner.gradient(wanted);
            boop += learner.cost(wanted);
        }
        temp /= subsetSize * rate;
        learner-= temp;
        cout<< boop/subsetSize << endl;
    }
    learner.toFile("english.net");



    
}