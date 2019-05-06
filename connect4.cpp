#include "Neural_net.h"

    bool isEmpty[7][6];
    bool isRed[7][6];
    bool isBlack[7][6];
  bool availableSelections[7];
  //bool[42][]
    int open;
    bool isGameOver;
    bool blacksMove;
  bool isDraw;
  bool blackWon;
  int moveNumber;
  vector<float> inputStorage[42];
  float outputStorage [42][7];
  int choiceStorage[42];
    void initializeGameBoard(){
      open =42;
      moveNumber = 0;
      isGameOver= false;
      blacksMove = true;
      isDraw = false;
      blackWon = NULL;
      for(int i = 0; i< 7; i++)
	availableSelections[i]=true;
        for(int i=0; i<7;i++){
            for(int j=0; j<6;j++){
                isEmpty[i][j] = true;
                isRed[i][j]=false;
                isBlack[i][j]=false;
            }
        }
    }


void makeMove(int c, bool blacksMove){
  int height = 5;
  while (isEmpty[c][height-1]&& height>= 1){
    height--;
  }
  //cout<<"height: "<<height<<endl;
  if(height == 5)
    availableSelections[c] = false;
  if(blacksMove)
    isBlack[c][height] = true;
  else
    isRed[c][height] = true;
  isEmpty[c][height] = false;
  open--;

  bool tmp [7][6];
  for(int i =0; i<7 ;i++){
      for(int j = 0; j<6;j++){
  if(blacksMove)
    tmp[i][j] = isBlack[i][j];
  else
    tmp[i][j] = isRed[i][j];
      }
  }

  int piecesInARow;
  int checkIncrement;
  bool possible;
  for(int i = 0; i < 7 ; i++){
    for (int j = 0; j < 6 ; j++){
      if(tmp[i][j]==true && isGameOver == false){
//cout<<"base piece column: "<<i<<" and row: "<<j;
        //cout<<" have value: "<<tmp[i][j]<<endl;
	piecesInARow = 1;
	possible = true;
	checkIncrement = 1;
	while(piecesInARow <4 && possible == true){
	if(i+checkIncrement<7 && j+checkIncrement<6){
	  if(tmp[i+checkIncrement][j+checkIncrement]){
	    piecesInARow++;
	    checkIncrement++;
	  }
	  else
	    possible = false;
	}else
	  possible = false;
	}
  if(possible == false){
  piecesInARow = 1;
	possible = true;
	checkIncrement = 1;
	while(piecesInARow <4 && possible == true){
	if(i+checkIncrement<7 && j-checkIncrement>=0){
	  if(tmp[i+checkIncrement][j-checkIncrement]){
	    piecesInARow++;
	    checkIncrement++;
	  }
	  else
	    possible = false;
	}else
	  possible = false;
	}
  }
	if(possible==false){
	  piecesInARow = 1;
	  possible =true;
	  checkIncrement=1;
	  while(piecesInARow <4 && possible == true){
	    if(i+checkIncrement <7){
	      if(tmp[i+checkIncrement][j]){
    //cout<<"looking at piece in column "<<i+checkIncrement<<" and row "<<j<<" and about to increase this number of pieces in a row: "<<piecesInARow<<endl;
		piecesInARow++;
		checkIncrement++;
	      }else
		possible = false;
	    }else
	      possible =false;
	  }
	}
	if(possible ==false){
	  piecesInARow =1;
	  possible = true;
	  checkIncrement =1;
	  while(piecesInARow < 4 && possible ==true){
	    if(j+checkIncrement<6){
	      if(tmp[i][j+checkIncrement]){
		piecesInARow++;
		checkIncrement++;
	      }else
		possible = false;
	    }else
	      possible = false;
	  }
	}
	if(piecesInARow>=4){
	  isGameOver = true;
	  isDraw = false;
	  if(blacksMove)
	    blackWon = true;
	  else
	    blackWon = false;
	}
      }
      
    }    
  }
  if(open == 0 && isGameOver ==false){
    isGameOver = true;
    isDraw = true;
  }  
 //cout<<"NEW_CHECK"<<endl;   

}

void makeTurn(bool& blacksMove, Network& learner, Network& learner2){
        vector<float> inputs;
        float outputs [7];
        for(int i = 0; i < 7; i++){
            for(int j = 0; j<6; j++){
            inputs.push_back(isRed[i][j]);
            inputs.push_back(isBlack[i][j]);
            inputs.push_back(isEmpty[i][j]);
            }
        }

    inputStorage [moveNumber] = inputs;

    if(blacksMove){
        learner.setInputLayer(inputs);
        learner.evaluate();
        for(int i=0; i<7; i++){
            outputs [i] = learner.getOutput(i);
        }
    } 
    else
    {
        learner2.setInputLayer(inputs);
        learner2.evaluate();
        for(int i=0; i<7; i++){
            outputs [i] = learner2.getOutput(i);
        }
    }
    int choice = -1;
    double value = -1000;
    for(int i = 0; i<7; i++){
        if(availableSelections[i]){
            if(outputs[i]>= value){
                choice = i;
                value = outputs[i];
            }
        }

    }

    choiceStorage[moveNumber] = choice;

    makeMove(choice,blacksMove);
    //cout<<"got here";
        if(blacksMove == true){
        blacksMove=false;
    }
        else
        {
            blacksMove = true;
        } 
    //cout<<" and here";   
}

int main()
{
    srand(time(NULL));
    const vector<int> dimensions = {7*6*3,75,20, 7};
    int firstLayer = dimensions[0];

    //bool isRedsTurn = TRUE;
    Network tempt(dimensions, true);
    //tempt.toFile("connect4black.net");

    Network tempt2(dimensions, true);
    //tempt2.toFile("connect4red.net");


for(int numGames=0; numGames< 100; numGames++){
    Network learner("connect4black.net");
    Network learner2("connect4red.net");
    initializeGameBoard();
    while(!isGameOver){
        makeTurn(blacksMove, learner, learner2);
        moveNumber++;
        //cout<<"turn made, open is now "<<open<<" blacks move is "<<blacksMove<<endl;
    }

    //cout<<"blackWon: "<<blackWon;

    vector <float> wanted(7);
    Network temp(dimensions);
    Network temp2(dimensions);
    double totalCost = 0;

    for(int index = 0; index < moveNumber; index++){
        if(index%2 == 0){
            //stuff for the learner 1 network which handles black moves
            if(blackWon){
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index])
                    wanted[i]=.99999;
                    else
                    wanted[i]=.00000001;
                }
            }else{
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index])
                    wanted[i]=.00000001;
                    else
                    wanted[i]=.99999;
                }
            }
            learner.setInputLayer(inputStorage[index]);
            learner.evaluate();
            temp += (learner.gradient(wanted)/= index/moveNumber);
            totalCost+= learner.cost(wanted);

        }else{
            //stuff for the learner 2 network which handles red moves
            if(!blackWon){
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index])
                    wanted[i]=.99999;
                    else
                    wanted[i]=.00000001;
                }
            }else{
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index])
                    wanted[i]=.00000001;
                    else
                    wanted[i]=.99999;
                }
            }
            learner2.setInputLayer(inputStorage[index]);
            learner2.evaluate();
            /*
            for(int i = 0; i < 7; i ++){
            cout<<wanted[i];
            }
            cout<<endl;
                        for(int i = 0; i < 7; i ++){
            cout<<learner2.getOutput(i)<<" ";
            }
            cout<<endl;
            */
            temp2 += (learner2.gradient(wanted)*=index/moveNumber);
            totalCost+= learner2.cost(wanted);

    }
    }
    learner-= temp;
    learner2-= temp2;

    for(int row = 5; row>= 0; row--)
    {
      cout << "|" ;
      for(int column = 0; column < 7; column++)
      {
        if (isRed[column][row]==true){
          cout << " X " ;
        }
        else if (isBlack[column][row]==true){
          cout << " O ";
        }
        else{ 
          cout << "   ";}
      }
      cout << "|" << endl;
    }
    cout<< "|---------------------|\n|                     |"<< endl;

    //cout<<"Cost per move: "<<totalCost/moveNumber<<"and number of turns: "<<moveNumber<<endl;

        learner.toFile("connect4black.net");
    learner2.toFile("connect4red.net");
}





















//for(int index =0; index<(42-moves);i++){

//}
    //cout<<open<<endl;

    /*
    int subsetSize = 10, rate = 10;

    for(int i = 0; i< 500; i++)
    {
        float boop = 0;
        Network temp(dimentions, false);
        for(int j = 0; j<subsetSize; j++)
        {
            vector<float> input, wanted(2);
            if(rnum() > 0.5)
            {
                int spot = (int)(7720 * rnum());
                input = formToInput(engData[spot],firstLayer, true);
                wanted[0] =1;
                wanted[1] = 0;
            }
            else
            {
                int spot = (int)(5334 * rnum());
                input = formToInput(gibData[spot],firstLayer,true);
                wanted[0] = 0;
                wanted[1] = 1;
            }
            learner.setInputLayer(input);
            learner.evaluate();
            
            
            temp += learner.gradient(wanted);
            boop += learner.cost(wanted);
        }
        temp /= (subsetSize / (float)rate);
        learner-= temp;
        cout<< boop/subsetSize << endl;
    }
    learner.toFile("englishUpper.net");
    

*/
    
}