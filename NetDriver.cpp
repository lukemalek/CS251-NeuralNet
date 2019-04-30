#include "Neural_net.h"

//TODO: think about network copy constructors.
//      we curently have a sudo-copy constructor in the form of exporting
//      and then calling network("filename"). I don't see much of a need for an
//      actual copy constructor right now but uhh think about it
int main()
{
    

    const vector<int> dimentions = {10,5,5,2};
    
    Network a(dimentions);
    vector<float> v = {1,0};
    a.toFile("before.net");
    a+=a.gradient(v);
    a.toFile("after.net");

    



}