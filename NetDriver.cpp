#include "Neural_net.h"

//TODO: 
int main()
{
    const vector<int> dimentions = {2, 4, 2};
    int firstLayer = dimentions[0];
    vector<float> input(firstLayer,0.5);


    srand(time(NULL));
    
    
    Network a(dimentions,false);
    a.toFile("before.net");
    a.setInputLayer(input);

    vector<float> v = {1,1};
    cout << "first cost: " << a.cost(v)<<endl;
    for(int i = 0; i<100000; i++)
    {
        a.evaluate();
        cout << a.cost(v)<<endl;
        a-=a.gradient(v);
        
    }
    cout << "\nlast cost: " << a.cost(v)<<endl;
    int b;
    cin >>b;
    a.toFile("after.net");
    



}