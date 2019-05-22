#ifndef _CONNECT_4_
#define _CONNECT_4_

#include "Neural_net.h"

class GameBoard{
    Network* learnerP;
    Network* learner2P;

    bool isEmpty[7][6];
    bool isRed[7][6];
    bool isBlack[7][6];
    bool availableSelections[7];
    int open;
    int moveNumber;
    bool blackWon;
    bool isGameOver;
    bool blacksMove;
    bool isDraw;
    int choiceStorage[42];
    vector<float> inputStorage[42];
    //float outputStorage [42][7];
    bool availableStorage [42][7];

    int numDiagonalWins;
  int numVerticalWins;
  int numHorizontalWins;
  float numBlackWins;
  float numRedWins;
  int numChoices;

    public:
        GameBoard(){
            initializeGameBoard();
        }

  float getBlackWins(){return numBlackWins;}
  float getRedWins(){return numRedWins;}
  int getVerticalWins(){return numVerticalWins;}
  int getDiagonalWins(){return numDiagonalWins;}
  int getHorizontalWins(){return numHorizontalWins;}

  int getMoveNumber(){return moveNumber;}
  int getNumChoices(){return numChoices;}

  void initializeGameBoard();
  void displayCurrentGameBoard();
  void makeMove(int c);
  void makeTurn();
  void updateNetworks();

  void playGame(){
        initializeGameBoard();
        //cout<<learnerP<<endl;
        const vector<int> dimensions = {7*6*3,75,40, 7};
        //Network learner(dimensions,false);
        //Network learner2(dimensions,false);
        Network learner("connect4black.net");
        Network learner2("connect4red.net");
        learnerP = &(learner);
        learner2P = &(learner2);
        //cout<<learnerP<<endl;

        while(!isGameOver){
        makeTurn();
        //displayCurrentGameBoard();
        moveNumber++;
        }
	    displayCurrentGameBoard();
        //cout<<learnerP<<endl;
        updateNetworks();
    }

};

#endif // _CONNECT_4_
