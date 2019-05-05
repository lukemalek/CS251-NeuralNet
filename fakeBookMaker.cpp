#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
using namespace std;

#include <stdlib.h>


float rnum()
{
    return (float)rand() / RAND_MAX;
}
int main()
{
    srand(time(NULL));
    ofstream fakeBook;
    fakeBook.open("gibberish.txt");
    int charsInLine = 0;
    for(int i = 0; i< 400000; i++)
    {
        string symbol;
        int p = (int)(rnum() * 110);
        if(p<80)
        {
            if(p<60)
            {
                symbol.push_back('a' + (int)(rnum() * 26));
            }
            else
            {
                symbol.push_back('A'+ (int)(rnum() * 26));
            }
        }
        else if (p<105)
        {
            symbol.push_back(' ');
        }
        else
        {
            symbol.push_back('.');
            symbol.push_back(' ');
        }
        charsInLine++;
        fakeBook << symbol;
        if(charsInLine >60)
        {
            fakeBook<< '\n';
            charsInLine = 0;
        }
            
    }
}