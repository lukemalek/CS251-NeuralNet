#include "Neural_net.h"

//TODO: think about network copy constructors.
//      we curently have a sudo-copy constructor in the form of exporting
//      and then calling network("filename"). I don't see much of a need for an
//      actual copy constructor right now but uhh think about it
int main()
{
    const vector<int> dimentions = {4,8,2};
    int firstLayer = dimentions[0];
    vector<float> input(firstLayer);
    for(int i = 0; i<firstLayer;i++)
        input[i] = 1.0;


    srand(time(NULL));
    
    
    Network a(dimentions);
    a.toFile("before.net");
    a.setInputLayer(input);
    a.evaluate();
    vector<float> v = {1,0};
    cout << "first cost: " << a.cost(v)<<endl;
    for(int i = 0; i<100; i++)
    {
        a-=a.gradient(v);
        a.evaluate();
    }
    cout << "last cost: " << a.cost(v)<<endl;
    
    a.toFile("after.net");
    



}