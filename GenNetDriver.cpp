#include "Gen_net.h"

int main()
{

    srand(time(NULL));
    const vector<int> dims{10, 20, 2};
    GenNetwork mom("mommy.net");

    for (int i = 0; i < 10; i++)
    {
        mom.setInputLayer();
        mom.evaluate();
        cout << mom.as_string() << endl;
    }
}