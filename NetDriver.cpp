#include "Neural_net.h"

//TODO:
int main()
{
    const vector<int> dimentions = {33 * 3, 3, 2};
    int firstLayer = dimentions[0];

    //srand(time(NULL));

    Network a(dimentions, false, true);
    //    Network a("after.net");

    a.setInputLayer(formToInput("ass", firstLayer, false));

    a.evaluate();
    vector<float> v = {1, 0};
    cout << "first cost: " << a.cost(v) << endl;
    for (int i = 0; i < 100; i++)
    {
        a -= a.gradient(v);
        a.evaluate();
    }
    cout << "\nlast cost: " << a.cost(v) << endl;
    a.toFile("after.net");
}