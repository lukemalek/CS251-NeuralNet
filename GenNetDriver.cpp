#include "Gen_net.h"

int main()
{
    const vector<int> dims {20,80,330};
    GenNetwork apples(dims, true);

    apples.setInputLayer();
    apples.evaluate();
    //cout<< apples.getOutput(7) << endl;
    cout << apples.as_string() << endl;


}