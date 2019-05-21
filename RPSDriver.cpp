#include "RPSBot.h"




int main()
{   
    
    const vector<int> dimentions = {150, 60,40, 3};

    RPSBot bot1("vsbot1.net");
    bot1.setInputLayer();
    float rate = 3;
    //bool go = true;
    cout<< endl;
    float games = 0,bwins, uwins;
    while(true)
    {
        bot1.evaluate();
        cout << "bot1 has a move ready! Enter r, p, or s to pick your move: ";
        string answer;
        getline(cin, answer);
        if(answer[0] == 0)
        {
            //go = false;
            break;
        }
        
        char move = answer[0];
        if(move != 'r' && move != 'R' && move != 'p' && move != 'P' && move != 's' && move != 'S')
        {
            continue;
        }
        RPSBot temp(bot1.getLayerSizes(), false);
        if(move< 97) move += 32;
        if(move == 'r') move = 0;
        if(move == 'p') move = 1;
        if(move == 's') move = 2;

        cout<< "bot played " << bot1.sayMove()<< ". ";
        if(move == bot1.myMove())
        {
            cout << "It's a draw!\n";
            
        }
        if((move+1)%3 == bot1.myMove())
        {
            cout << "Bot wins!\n";
            bwins++;
            
        }
        if((move+2)%3 == bot1.myMove())
        {
            cout << "You win!\n";
            uwins++;
            
        }
        games++;
        temp += bot1.gradient((int)(move +1)%3);
        temp *= rate;
        bot1 -= temp;
        bot1.addToMem(move);
        bot1.setInputLayer();
    }
    /*cout << "save training session? ";
    char a;
    cin >> a;
    if(a == 'y')*/
    //bot1.toFile("bot1.net");
    cout<< "Expected win rate : 33%%\nActual bot win rate: " <<bwins/games<< endl ;



}