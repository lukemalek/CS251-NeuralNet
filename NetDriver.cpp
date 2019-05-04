#include "Neural_net.h"

//TODO: think about network copy constructors.
//      we curently have a sudo-copy constructor in the form of exporting
//      and then calling network("filename"). I don't see much of a need for an
//      actual copy constructor right now but uhh think about it
int main()
{
    vector<float> input(4);
    for(unsigned int i = 0; i<4;i++)
        input[i] = 1.0;


    srand(time(NULL));
    const vector<int> dimentions = {4,2,2};
    
    Network a("before.net");
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