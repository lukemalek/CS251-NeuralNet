#include "RPSBot.h"

int main()
{
    int score1 = 0, score2 = 0, games = 0;
    const vector<int> dimentions1 = {150, 60, 40, 3};
    const vector<int> dimentions2 = {50, 20, 3};

    //RPSBot bot1(dimentions1, true);
    //RPSBot bot2(dimentions2, true);
    RPSBot bot1("vsbot1.net");
    RPSBot bot2("vsbot2.net");
    bot1.setInputLayer();
    bot2.setInputLayer();
    float rate = 1;
    //bool go = true;
    cout << endl;
    for (; games < 1000; games++)
    {
        bot1.evaluate();
        bot2.evaluate();

        RPSBot temp1(bot1.getLayerSizes(), false);
        RPSBot temp2(bot2.getLayerSizes(), false);

        cout << "bot1 played " << bot1.sayMove() << ", bot2 played " << bot2.sayMove() << endl;
        int move1 = bot1.myMove(), move2 = bot2.myMove();
        if (move1 == move2)
        {
            cout << "It's a draw!\n";
        }
        if ((move1 + 1) % 3 == move2)
        {
            cout << "Bot1 wins!\n";
            score1++;
        }
        if (move1 == (move2 + 1) % 3)
        {
            cout << "Bot2 wins!\n";
            score2++;
        }

        temp1 += bot1.gradient((move2 + 1) % 3);
        temp2 += bot2.gradient((move1 + 1) % 3);
        temp1 *= rate;
        temp2 *= rate;

        bot1 -= temp1;
        bot1.addToMem(move2);
        bot1.setInputLayer();

        bot2 -= temp2;
        bot2.addToMem(move1);
        bot2.setInputLayer();
    }
    /*cout << "save training session? ";
    char a;
    cin >> a;
    if(a == 'y')*/
    bot1.toFile("vsbot1.net");
    bot2.toFile("vsbot2.net");
    cout << score1 << " "<< score2 << endl;
}