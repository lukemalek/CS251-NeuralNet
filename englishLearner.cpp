#include "Neural_net.h"
using namespace std;
int main()
{
    srand(time(NULL));
    const vector<int> dimentions = {30*100,20, 2};
    int firstLayer = dimentions[0];

    ifstream frank("frankenstein.txt");
    ifstream ody("odyssey.txt");

    //this chunk will read both books into separate giant strings.
    vector<string> frankData, odyData;
    string frankstring,odystring,line,s;
    s= " ";
    while(frank)
    {
        getline(frank,line);
        frankstring += s;
        frankstring += line;
        
    }
    while(ody)
    {
        getline(ody,line);
        odystring += s;
        odystring += line;
    }

    //converts the giant string into a vector of string, where each string is a sentence, starts at a capital letter and ends at . or ? or !
    int franksize = frankstring.size(), odysize = odystring.size();
    for(int i = 0; i<franksize;i++)
    {
        string a = {};
        while (frankstring[i] < 65 || frankstring[i] > 90)
        {
            if(i<franksize)i++;
            else break;
        }
        if(i==franksize)break;
        while (frankstring[i] != '.' && frankstring[i] != '!' && frankstring[i] != '?')
        {
            a.push_back(frankstring[i]);
            if(i<franksize)i++;
            else break;
        }
        a.push_back(frankstring[i]);
        if(a.size()>20)
            frankData.push_back(a);
    }

    //converts the giant string into a vector of string, where each string is a sentence, starts at a capital letter and ends at . or ? or !
    for(int i = 0; i<odysize;i++)
    {
        string a = {};
        while (odystring[i] < 65 || odystring[i] > 90)
        {
            if(i<odysize)i++;
            else break;
        }
        if(i==odysize)break;
        while (odystring[i] != '.' && odystring[i] != '!' && odystring[i] != '?')
        {
            a.push_back(odystring[i]);
            if(i<odysize)i++;
            else break;
        }
        a.push_back(odystring[i]);
        if(a.size()>20)
            odyData.push_back(a);
    }

    frank.close();
    ody.close();

    //says the funny line about puppies
    cout << endl<< odyData[1328] << endl;



    //Network learner(dimentions, false);
    Network learner("HomerVShelly2.net");
    int correct=0;

    
    int subsetSize = 1000;
    float rate = 0.2;

    //ten times over
    for(int i = 0; i< 10; i++)
    {
        float boop = 0;

        //makes network to hold gradient of the current batch
        Network temp(learner.getLayerSizes(), false);
        correct = 0;
        
        //trains the net with subsetSize about of data
        for(int j = 0; j<subsetSize; j++)
        {
            vector<float> input, wanted(2);
            if(rnum() > 0.5)
            {
                int spot = (int)(frankData.size() * rnum());
                input = formToInput(frankData[spot],firstLayer, false);
                wanted[0] =1;
                wanted[1] = 0;
            }
            else
            {
                int spot = (int)(odyData.size() * rnum());
                input = formToInput(odyData[spot],firstLayer,false);
                wanted[0] = 0;
                wanted[1] = 1;
            }
            learner.setInputLayer(input);
            learner.evaluate();
            if((learner.getOutput(0)>learner.getOutput(1) && wanted[0] == 1)|| (learner.getOutput(0)<=learner.getOutput(1) && wanted[1] == 1))
                correct++;
            
            //given the output that the net should have given, compute gradient
            temp += learner.gradient(wanted,0.9);
            boop += learner.cost(wanted);
        }
        //scale gradient, then move backwards along it.
        temp /= (subsetSize / rate);
        learner-= temp;

        //says how many correct classifcations were made.
        cout<< boop/subsetSize << " Number correct out of "<<subsetSize<<": "<< correct<< endl;
    }

    //saves the file for next time
    learner.toFile("HomerVShelly2.net");
    
}
