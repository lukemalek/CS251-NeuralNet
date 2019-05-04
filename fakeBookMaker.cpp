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
    for(int i = 0; i< 75000; i++)
    {
        string word;
        int length = 1 + rnum() * 8;
        charsInLine += length;
        for(int j = 0; j<length; j++)
        {
            word.push_back(97 + (char)(26 * rnum()));
        }
        fakeBook << word;
        if(charsInLine >60)
        {
            fakeBook<< '\n';
            charsInLine = 0;
        }
        else
            fakeBook << ' ';
            
    }
}