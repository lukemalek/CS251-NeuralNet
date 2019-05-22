#ifndef _CONNECT_4_
#define _CONNECT_4_

#include "sd_fun.h"
#include "Neural_net.h"
using namespace std;

class GameBoard{
    //used for calling any functions of the networks within a game
    Network* learnerP;
    Network* learner2P;

//three two dimentional arrays, representing the state of each slot of the 42 slot board
//first dimention is column, second dimension is row
    bool isEmpty[7][6];
    bool isRed[7][6];
    bool isBlack[7][6];
//keep track of which of the 7 columns are available (true) and which of the 7 are full (false)
    bool availableSelections[7];
//number of open spaces
    int open;
//what move is it within the game
    int moveNumber;
// did black win?
    bool blackWon;
// is the game over?
    bool isGameOver;
// is it blacks turn?
    bool blacksMove;
//was the game a draw?
    bool isDraw;
//used for backpropagation, these have the first dimension of 42 corresponding to as many of the 42 possible moves in a game as necessary,
//stores the input for network, what the network ended up choosing, and what it could have chosen from
    int choiceStorage[42];
    vector<float> inputStorage[42];
    bool availableStorage [42][7];

//used for summary statistics
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

//returning summary statistics from a game
  float getBlackWins(){return numBlackWins;}
  float getRedWins(){return numRedWins;}
  int getVerticalWins(){return numVerticalWins;}
  int getDiagonalWins(){return numDiagonalWins;}
  int getHorizontalWins(){return numHorizontalWins;}
  int getMoveNumber(){return moveNumber;}
  int getNumChoices(){return numChoices;}

//functions to play a game with
  void initializeGameBoard();
  void displayCurrentGameBoard();
  void makeMove(int c);
  void makeTurn();
  void updateNetworks();

//uses above functions to play 1 CPU vs CPU training game
  void playCPUGame(){
        initializeGameBoard();

        //loads the two networks
        Network learner("connect4black.net");
        Network learner2("connect4red.net");
        learnerP = &(learner);
        learner2P = &(learner2);

        while(!isGameOver){
        makeTurn();
        moveNumber++;
        }
	    displayCurrentGameBoard();
        updateNetworks();
    }

void playUserGame(bool compGoesFirst){
    initializeGameBoard();

        //loads the two networks
        Network learner("connect4black.net");
        Network learner2("connect4red.net");
        learnerP = &(learner);
        learner2P = &(learner2);

//has player take a turn at the begining or not depending on if they wanted to go first or not
if(!compGoesFirst){
            int playerselection;
        cout<<"enter column number (1 through 7): ";
        cin>>playerselection;
        makeMove(playerselection-1);
        moveNumber++;
        if(blacksMove == true){
        blacksMove=false;
        }
        else
        {
            blacksMove = true;
        }     
        displayCurrentGameBoard();
}

while(!isGameOver){
    //computer takes a turn
    makeTurn();
    moveNumber++;
    displayCurrentGameBoard();

        //player takes a turn
        int playerselection;
        cout<<"enter column number (1 through 7): ";
        cin>>playerselection;
        makeMove(playerselection-1);
        moveNumber++;
        if(blacksMove == true){
        blacksMove=false;
        }
        else
        {
            blacksMove = true;
        }     
	    displayCurrentGameBoard();
}

}

};

#endif // _CONNECT_4_
