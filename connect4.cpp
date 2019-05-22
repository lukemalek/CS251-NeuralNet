#include"connect4.h"

void GameBoard::initializeGameBoard(){

 numDiagonalWins=0;
  numVerticalWins=0;
  numHorizontalWins=0;
  numRedWins = 0; 
  numBlackWins=0;
  numChoices = 0;

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

    void GameBoard::displayCurrentGameBoard(){
        //for now, eventually will display in yaml
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
    }

    void GameBoard::updateNetworks(){
        //cout<<learnerP<<endl;
        const vector <int> dimensions = {7*6*3,75,40, 7};
    if(blackWon){
    numBlackWins++;
  } else if (blackWon == false){
    numRedWins++;
  }
    //cout<<"blackWon: "<<blackWon;
    vector <float> wanted(7);
    //cout<<dimensions<<endl;
    //for(auto elem : dimensions)
        //cout << elem << "\n";
    //cout<<"made it here"<<endl;
    //cout<<"made it here"<<endl;
    Network temp(dimensions, false, false);
    Network temp2(dimensions, false, false);
    double totalCost = 0;

    for(int index = 0; index < moveNumber; index++){
      int selectionsForThisMove = 0;
for(int i = 0; i<7;i++){
  if(availableStorage[moveNumber][i]){
  selectionsForThisMove++;
  }
}
        if(index%2 == 0){
            //stuff for the learner 1 network which handles black moves
            if(blackWon){
                //cout<<"Im black and I won, adding move number "<<index<<" to temp"<<endl;
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=1;
                    //cout<<"a";
                    }
                    else{ 
                    wanted[i]=0;
                    //cout<<"b";
                    }
                }
            }else{
                                //cout<<"Im black and I lost, adding move number "<<index<<" to temp"<<endl;
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=0;
                    //cout<<"c";
                    }else if(availableStorage[index][i] == false){
                    wanted[i]=0;
                    //cout<<"d";
                    }
                    else{
                      wanted[i] = 1;
                      //cout<<"e";
                      //wanted[i] = (1/(selectionsForThisMove-1));
                    }
                    
                }
            }
            learnerP->setInputLayer(inputStorage[index]);
            learnerP->evaluate();
            temp += (learnerP->gradient(wanted, 0.1));
            totalCost+= learnerP->cost(wanted);

        }
        else{
            //stuff for the learner 2 network which handles red moves, also counts filling up the board as a dub for red which i kinda like
            if(!blackWon){
                                //cout<<"Im red and I won, adding move number "<<index<<" to temp2"<<endl;
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=1;
                    //cout<<"f";
                    }
                    else{
                    wanted[i]=0;
                    //cout<<"g";
                    }
                }
            }else{
                                //cout<<"Im red and I lost, adding move number "<<index<<" to temp2"<<endl;
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=0;
                    //cout<<"h";
                    }else if(availableStorage[index][i] == false){
                    wanted[i]=0;
                    //cout<<"i";
                    }
                    else{
                      wanted[i]=1;
                      //cout<<"j";
                      //wanted[i] = (1/(selectionsForThisMove-1));
                    }
                }
            }
            learner2P->setInputLayer(inputStorage[index]);
            learner2P->evaluate();
            temp2 += (learner2P->gradient(wanted, 0.1));
            totalCost+= learner2P->cost(wanted);

    }
    }
    /*
    if (blackWon && moveNumber > 19){
      //black won in a long game, should do this more
      //temp *= 10;
      //red lost, but in a long game, was on the right track and shouldnt change too much
      temp2 *=.1;
    }
    if (blackWon && moveNumber < 19){
      //temp *= .1;
      temp2 *=10;
    }
    if (blackWon == false && moveNumber > 19){
      temp *= .1;
      //temp2 *=10;
    }
    if (blackWon == false && moveNumber < 19){
      temp *= 10;
      //temp2 *=.1;
    }
*/
float moveFloat = (float) moveNumber;
//cout<<"MOVE Number: "<<moveNumber<<endl;
    if(blackWon){
      //cout<<moveNumber<<endl;
      temp *= (.1*(1*((2*(moveFloat))/43)));
      temp2 *= (.1*(6*(2*((43- (moveFloat)))/43))); 
      //cout<<"0 or black won this one"<<endl;
    }
    if(blackWon == false){
      temp *= (.1*(6*(2*(43 - (moveFloat))/43)));
      temp2 *= (.1*(1*(2*((moveFloat)/43))));
      //cout<<"X or red won this one"<<endl;
    }
      
    *(learnerP)-= temp;
    *(learner2P)-= temp2;
    learnerP->toFile("connect4black.net");
    learner2P->toFile("connect4red.net");
}

    void GameBoard::makeTurn(){
        vector<float> inputs;
        float outputs [7];

        //these are what the neural networks take in. For any given turn, a neural net will take in 126 boolean values, of which 42 are 1 and 84 are 0
        //these values will alays be in the same order, and will not vary based on which turn it is, so one neural network will learn to play as 
        //black and the other as red, but both will "see" the exact smae thing, in theory each network would learn to see a given value of 1 in isRed and isBlack as exact opposites
        for(int i = 0; i < 7; i++){
            for(int j = 0; j<6; j++){
            inputs.push_back(isRed[i][j]);
            inputs.push_back(isBlack[i][j]);
            inputs.push_back(isEmpty[i][j]);
            }
        }

    //for use later in backpropagating--stores what the neural network sees on a turn for a turn in an array with index of that turn number
    inputStorage [moveNumber] = inputs;

    //either one network or the other evaluates to produce vector of 7 doubles, with each double being from 0 to 1 and with higher numbers reprresetning more preference
    if(blacksMove){
        learnerP->setInputLayer(inputs);
        learnerP->evaluate();
        for(int i=0; i<7; i++){
            outputs [i] = learnerP->getOutput(i);
        }
    } 
    else
    {
        learner2P->setInputLayer(inputs);
        learner2P->evaluate();
        for(int i=0; i<7; i++){
            outputs [i] = learner2P->getOutput(i);
        }
    }
    for(int i = 0; i<7; i++)
    cout<<outputs[i]<<" ";
    cout<<endl;

  for(int i = 0; i<7; i++)
    availableStorage[moveNumber][i] = availableSelections[i];

    //given the output vector from the neural network, find the index value of the choice that has the highest output value, provided that choice is of a column that is not filled up
    //choice is goint to represent a column number, so a value from 0 to 6
    int choice = -1;
    double Maxvalue = -1000;
    //bool needRandom = false;
    int choices [7];
    int pos = 0;
    for (int i = 0; i<7; i++){
        if(availableSelections[i]){
          if (outputs[i]>Maxvalue)
            Maxvalue = outputs[i];
        }
    }

    for(int i = 0; i<7; i++){
        if(availableSelections[i]){
            //if(outputs[i]> Maxvalue){
                 //choices[pos]= i;
                //Maxvalue = outputs[i];
                //cout << "here";
            //}
    // interesting little feature, if two columns have the same "prefrence" as given by outputs, it will randomly choose between the two
    //avoids getting stuck with too much unwarranted preference for any values. In the case that for example, all the outputs are 1
    //this way, at least some times, it wouldn't just choose column 0 over and over in that hypothetical scenario. It would at least sometimes end up doing 
    //something else and having a possibility to learn more
            if(outputs[i] == Maxvalue){
              choices [pos] = i;
              pos++;
              //cout<<"ya";
              //needRandom = true;
	    }
        }

    } 
    int c = (int)(rnum()*(pos));
//cout<<"made choice "<<c<<" from "<<pos<<" choices"<<endl;
     choice = choices[c];   
      numChoices+= pos;

    //stores each of the moves of the game(in terms of column number) in an array with index being the move number
    choiceStorage[moveNumber] = choice;
    makeMove(choice);
    //switches blacksMove from true to false or visa versa
        if(blacksMove == true){
        blacksMove=false;
    }
        else
        {
            blacksMove = true;
        }   
}

  void GameBoard::makeMove(int c){
//see which of the 42 slots should be changed given c (an int from 0 to 6) and the matrix isEmpty 
  int height = 5;
//starts at height 5 of column c, and while isEmpty of column c height-1, decreases height
  while (isEmpty[c][height-1]&& height>= 1){
    height--;
  }
  //sets the corresponding element of avaiable selections to false if for c the piece was placed at height 5
  if(height == 5)
    availableSelections[c] = false;
    //puts either a red or black piece at the correct slot
  if(blacksMove)
    isBlack[c][height] = true;
  else
    isRed[c][height] = true;

    //sets the correct slot to FALSE for isEmpty
  isEmpty[c][height] = false;
  //decreases the number of open spaces
  open--;
  
//creates tmp, a 7 by 6 array that is a copy of either black or red, whichever is currently taking a turn
  bool tmp [7][6];
  for(int i =0; i<7 ;i++){
      for(int j = 0; j<6;j++){
  if(blacksMove)
    tmp[i][j] = isBlack[i][j];
  else
    tmp[i][j] = isRed[i][j];
      }
  }

//checks tmp for any possible 4 in a row win, using the principle that for any win, one of the pieces must be the start of the win. Checks every piece in the board first to make 
//sure that it is occupied by the current color, and then if it is, it checks for three more pieces in a row of the same color originating from that piece in
// the four distinct possible ways that a win must originate from at least 1 piece
  int piecesInARow;
  bool possible;
  //loops through each of the 42 slots in the board
  for(int i = 0; i < 7 ; i++){
    for (int j = 0; j < 6 ; j++){
        //first checks that the slot is occpied by the color that it is checking, and if not, move on to the next values for i and j
      if(tmp[i][j]==true && isGameOver == false){
    
    //First Check: do this no matter what --(up and right diagonal)
	piecesInARow = 1;
	possible = true;
	while(piecesInARow <4 && possible == true){
	if(i+piecesInARow<7 && j+piecesInARow<6){
	  if(tmp[i+piecesInARow][j+piecesInARow]){
	    piecesInARow++;
	  }
	  else
	    possible = false;
	}else
	  possible = false;
	}
    //keep track of summary statistics
	if(piecesInARow>=4){
	  numDiagonalWins++;
	}

    //Second Check: do this only if the first check did not detect a win --(down and right diagonal)
  if(possible == false){
  piecesInARow = 1;
	possible = true;
	while(piecesInARow <4 && possible == true){
	if(i+piecesInARow<7 && j-piecesInARow>=0){
	  if(tmp[i+piecesInARow][j-piecesInARow]){
	    piecesInARow++;
	  }
	  else
	    possible = false;
	}else
	  possible = false;
	}
    //keep track of summary statistics
	if(piecesInARow>=4){
	  numDiagonalWins++;
	}
  }

  //Third Check: do this only if the first two checks did not find a win --(right horizontal)
	if(possible==false){
	  piecesInARow = 1;
	  possible =true;
	  while(piecesInARow <4 && possible == true){
	    if(i+piecesInARow <7){
	      if(tmp[i+piecesInARow][j]){
		piecesInARow++;
	      }else
		possible = false;
	    }else
	      possible =false;
	  }
    //keep track of summary statistics
	  if(piecesInARow>=4){
	    numHorizontalWins++;
}
    }
//Fourth Check: do this only if none of the other checks found a win -- (up vertical)
	
	if(possible ==false){
	  piecesInARow =1;
	  possible = true;
	  while(piecesInARow < 4 && possible ==true){
	    if(j+piecesInARow<6){
	      if(tmp[i][j+piecesInARow]){
		piecesInARow++;
	      }else
		possible = false;
	    }else
	      possible = false;
	  }
    //keep track of summary statistics
	  if(piecesInARow>=4){
	    numVerticalWins++;
	  }
	}

    //checks to see if for the given piece, one of the 4 in a row checks was complete and there are currently 4 pieces in a row, signaling the end of the game
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
  //checks for game over via draw
  if(open == 0 && isGameOver ==false){
    isGameOver = true;
    isDraw = true;
  }  

}
