#include"connect4.h"

int main(){
float totalBlackWins = 0;
float totalRedWins = 0;
int totalVertWins = 0;
int totalDiagWins = 0;
int totalHorizWins = 0;
int totalChoices = 0;
int totalMoves = 0;

    srand(time(NULL));
    const vector<int> dimensions = {7*6*3,75,40, 7};
    GameBoard a;
    for (int i = 0; i<30; i++){
    a.playGame();
    totalBlackWins += a.getBlackWins();
    totalRedWins += a.getRedWins();

    totalDiagWins += a.getDiagonalWins();
    totalVertWins += a.getVerticalWins();      
    totalHorizWins += a.getHorizontalWins(); 

    totalChoices += a.getNumChoices();
    totalMoves += a.getMoveNumber();
    }
    cout<<totalBlackWins<<endl;
    cout<<totalRedWins<<endl;
    cout<<totalVertWins<<endl;    
    cout<<totalHorizWins<<endl;
    cout<<totalDiagWins<<endl;
    cout<<totalChoices<<endl;
    cout<<totalMoves<<endl;
    cout<<(float)(totalChoices)/((float)(totalMoves))<<endl;
}
