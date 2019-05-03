#include "Neural_net.h"

//TODO: think about network copy constructors.
//      we curently have a sudo-copy constructor in the form of exporting
//      and then calling network("filename"). I don't see much of a need for an
//      actual copy constructor right now but uhh think about it
int main()
{
    

    const vector<int> dimentions = {10,10,2};
    
    Network a("after.net");
    a.evaluate();
    vector<float> v = {1,0};
    for(int i = 0; i<100; i++)
    {
        cout << a.cost(v)<<endl;
        a-=a.gradient(v);
        a.evaluate();
    }
    
    a.toFile("after2.net");
    



}