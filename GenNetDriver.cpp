#include "Gen_net.h"

int main()
{
    const vector<int> dims {20,80,330};
    GenNetwork apples(dims, false);
    GenNetwork oranges(dims, false, true);
    apples.toFile("apple.net");
    oranges.toFile("oranges.net");
    Network a(dims, false);
    a+= apples.breedWith(oranges, 0);
    a.toFile("child.net");


    apples.setInputLayer();
    apples.evaluate();
    //cout<< apples.getOutput(7) << endl;
    cout << apples.as_string() << endl;


}