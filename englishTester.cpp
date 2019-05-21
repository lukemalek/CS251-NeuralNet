#include "Neural_net.h"
using namespace std;
int main()
{

    
    Network learner("HomerVShelly2.net");
    int correct=0,attempted=0;
    
    bool keepGo = true;
    cout<< "HomerVShelly2 net tester! I work best when inputting sentences with a bit of bulk to them (25+ chars)\n";
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
            cout << "I think that is frankenstein-y! Was I right? (y/n)" << endl;
        else
            cout << "I think that is odyssey-y! Was I right? (y/n)" << endl;
        cout << learner.getOutput(0) << ' ' << learner.getOutput(1) << endl;
        string ans;
        getline(cin, ans);
        if(ans[0] == 'y' || ans[0] == 'Y')
        {
            correct++;
        }
    }
    cout << "I guessed " << correct << " out of " << attempted << " correctly! (" << ((float)correct)/attempted << ")\n";

    
}
