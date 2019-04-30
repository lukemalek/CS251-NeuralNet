#include "net_fun.h"

double sig(double x, double steepness)
{
    return 1.0/ (1 + pow(M_E, - steepness * x));
}
double sigP(double x, double steepness)
{
    // defined the value of e^(-steepness * x) so the computer
    // wouldnt have to do it three times in the function
    double eToTheNegsx = pow(M_E,- steepness*x);
    return (steepness * eToTheNegsx)/( (1 + eToTheNegsx) * (1 + eToTheNegsx) );
}

float rnum()
{
    //return dis(gen);
    return (float)rand() / RAND_MAX;

}

