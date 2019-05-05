#include "Neural_net.h"

int main()
{
    srand(time(NULL));
    const vector<int> dimentions = {56*40, 60,20, 2};
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
    for(int i = 0; i<6558; i++)
    {
        string line; 
        getline(gibberish,line);
        gibData.push_back(line);
    }

    Network learner("englishUpper.net");
    /*
    cout << "enter a phrase : ";
    string answer;
    getline(cin, answer);
    learner.setInputLayer(formToInput(answer, firstLayer,false));
    learner.evaluate();
    if(learner.getOutput(0) > learner.getOutput(1))
        cout << "I think that is english!" << endl;
    else
        cout << "I think that is GIBBERISH, you child!" << endl;
    cout <<learner.getOutput(0) << ' '<< learner.getOutput(1) << endl;
    */

    int subsetSize = 10, rate = 10;

    for(int i = 0; i< 500; i++)
    {
        float boop = 0;
        Network temp(dimentions, false);
        for(int j = 0; j<subsetSize; j++)
        {
            vector<float> input, wanted(2);
            if(rnum() > 0.5)
            {
                int spot = (int)(7720 * rnum());
                input = formToInput(engData[spot],firstLayer, true);
                wanted[0] =1;
                wanted[1] = 0;
            }
            else
            {
                int spot = (int)(5334 * rnum());
                input = formToInput(gibData[spot],firstLayer,true);
                wanted[0] = 0;
                wanted[1] = 1;
            }
            learner.setInputLayer(input);
            learner.evaluate();
            
            
            temp += learner.gradient(wanted);
            boop += learner.cost(wanted);
        }
        temp /= (subsetSize / (float)rate);
        learner-= temp;
        cout<< boop/subsetSize << endl;
    }
    learner.toFile("englishUpper.net");
    


    
}