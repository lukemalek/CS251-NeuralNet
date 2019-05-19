#include "Neural_net.h"
using namespace std;
int main()
{
    srand(time(NULL));
    const vector<int> dimentions = {30*200, 100, 40, 2};
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
        frankData.push_back(a);
    }

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
        odyData.push_back(a);
    }

    frank.close();
    ody.close();

    cout << endl<< odyData[1328] << endl;



    /*
    Network learner(dimentions,false);
    int correct=0,attempted=0;
    bool keepGo = true;
    while (keepGo)
    {
        
        cout << "Enter a phrase : ";
        string answer;
        getline(cin, answer);
        
        if(answer[0] == 0)
        {
            keepGo = false;
            break;
        }
        attempted++;
        learner.setInputLayer(formToInput(answer, learner.getInputSize(), false));
        learner.evaluate();
        if (learner.getOutput(0) > learner.getOutput(1))
            cout << "I think that is english! Was I right? (y/n)" << endl;
        else
            cout << "I think that is gibberish! Was I right? (y/n)" << endl;
        cout << learner.getOutput(0) << ' ' << learner.getOutput(1) << endl;
        string ans;
        getline(cin, ans);
        if(ans[0] == 'y' || ans[0] == 'Y')
        {
            correct++;
        }
    }
    cout << "I guessed " << correct << " out of " << attempted << " correctly! (" << ((float)correct)/attempted << ")\n";

    */

    /*
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
                input = formToInput(engData[spot],firstLayer, false);
                wanted[0] =1;
                wanted[1] = 0;
            }
            else
            {
                int spot = (int)(5334 * rnum());
                input = formToInput(gibData[spot],firstLayer,false);
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
    */
}
