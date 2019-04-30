#ifndef _NET_FUN_
#define _NET_FUN_
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
using namespace std;

#include <math.h>
#include <stdlib.h>


//dis(gen) gives random number
/*#ifndef _RANDOM_CONFIG_
#define _RANDOM_CONFIG_
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
#endif // _RANDOM_CONFIG */

//define sigmoid functions
extern double sig(double x, double steepness = 1);
extern double sigP(double x, double steepness = 1);
//returns value from 0 to 1
extern float rnum();

#endif // _NET_FUN_