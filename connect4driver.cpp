#include"connect4.h"
#include"sd_fun.h"

int main(){
//variables to keep track of summary statistics between games
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

    //a.createBlankFile("testbullshit.net");

    bool playHuman = false;
    bool compGoesFirst = false;

    string gameType;
    cout<<"do you want the computer to train itself, or do you want to play against it?\n enter either cpu or human:";
    cin>>gameType;
    if(gameType == "cpu"){
        playHuman = false;
    } else if (gameType == "human"){
        playHuman = true;
    } else{
        cout<<"wrong input"<<endl;
        return 0;
    }

    if(playHuman){
        int Turn = 0;
        cout<<"do you want to go first or second?\n enter 1 or 2:";
        cin>>Turn;
        if(Turn == 1){
            compGoesFirst = false;
        } else if (Turn == 2){
            compGoesFirst = true;
        } else{
            cout<<"wrong input"<<endl;
            return 0;
        }
        a.playUserGame(compGoesFirst);
    }

    if(!playHuman){
        int Games = 0;
        cout<<"how many games should it train on?\n enter an integer:";
        cin>>Games;
        for(int i = 0; i<  Games; i++){
            a.playCPUGame();

            //adds summary statistics
            totalBlackWins += a.getBlackWins();
            totalRedWins += a.getRedWins();

            totalDiagWins += a.getDiagonalWins();
            totalVertWins += a.getVerticalWins();      
            totalHorizWins += a.getHorizontalWins(); 

            totalChoices += a.getNumChoices();
            totalMoves += a.getMoveNumber();
        }

        //prints summary statistics
    cout<<"Black (O) Wins: "<<totalBlackWins<<endl;
    cout<<"Red (X) Wins: "<<totalRedWins<<"\n"<<endl;
    cout<<"Vertical Wins: "<<totalVertWins<<endl;    
    cout<<"Horizontal Wins: "<<totalHorizWins<<endl;
    cout<<"Diagonal Wins: "<<totalDiagWins<<"\n"<<endl;
    cout<<"Total Selections: "<<totalChoices<<endl;
    cout<<"Total Moves: "<<totalMoves<<endl; 

    }

}
