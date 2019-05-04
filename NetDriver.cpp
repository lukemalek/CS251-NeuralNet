#include "Neural_net.h"

//TODO: 
int main()
{
    const vector<int> dimentions = {1000, 20, 2};
    int firstLayer = dimentions[0];
    vector<float> input(firstLayer);
    for(int i = 0; i<firstLayer;i++)
        input[i] = 0.5;


    srand(time(NULL));
    
    
    Network a(dimentions,false);
    a.toFile("before.net");
    a.setInputLayer(input);
    a.evaluate();
    vector<float> v = {1,1};
    cout << "first cost: " << a.cost(v)<<endl;
    for(int i = 0; i<100; i++)
    {
        a-=a.gradient(v);
        a.evaluate();
    }
    cout << "last cost: " << a.cost(v)<<endl;
    
    a.toFile("after.net");
    



}