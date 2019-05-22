#include"connect4.h"
#include"sd_fun.h"

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
      //all columns are avaiable to put into at the start of the game
      for(int i = 0; i< 7; i++)
	availableSelections[i]=true;
  //all slots are empty and nore are black or red at the start of the game
        for(int i=0; i<7;i++){
            for(int j=0; j<6;j++){
                isEmpty[i][j] = true;
                isRed[i][j]=false;
                isBlack[i][j]=false;
            }
        }
}

    void GameBoard::displayCurrentGameBoard(){
        //prints the game board with X representing red pieces and O representing black ones
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
        const vector <int> dimensions = {7*6*3,75,40, 7};
    if(blackWon){
    numBlackWins++;
  } else if (blackWon == false){
    numRedWins++;
  }
//this is the vector that will be filled in with either 1 or 0, willl be used as the argument for gradient
//for each move, if the player won the game, the corresponding value of wanted that matches their selection will be 1 and all the other 6 will be zero
//but if they lost, the value of wanted that matches their move will be 0 and the other 6 will be 1
//essentially meaning if an AI wins a game it will keep doing everything it did and if an AI loses it will stop doing what it did and start trying to do everything else
    vector <float> wanted(7);

//create two blank networks which will each store the gradients from half of the moves in a game, temp for learner and temp 2 for learner2
    Network temp(dimensions, false, false);
    Network temp2(dimensions, false, false);
    //double totalCost = 0;

//loops through all moves that took place during the last game, starting from move number 0
    for(int index = 0; index < moveNumber; index++){


//This first if else statement decides if a move was taken by learner or learner2,
//the if part corresponds to learner 1
        if(index%2 == 0){
          //nested if else statemnt checks which color won
            if(blackWon){
                // for loop fills wanted with 6 0's and a 1 (learner won)
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=1;
                    }
                    else{ 
                    wanted[i]=0;
                    }
                }
            }           
            else{
              //for loop fills wanted with 6 1's and a 0 (learner lost)
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=0;
                    //except in the case of this else if, which will put a zero if the column was filled to the brim on that turn, as we dont want the AI trying to put pieces into columns it cannot
                    }else if(availableStorage[index][i] == false){
                    wanted[i]=0;
                    }
                    else{
                      wanted[i] = 1;
                    }
                    
                }
            }
            //finally, calculates a gradient and adds it to temp
            //uses input storage for that move to recreate the inputs, and since no weight or biases have been changed yet, we get the exact same activations and final outputs from that move 
            learnerP->setInputLayer(inputStorage[index]);
            learnerP->evaluate();
            temp += (learnerP->gradient(wanted, 0.1));
            //totalCost+= learnerP->cost(wanted);

        }
    //this is the else part which corresponds to learner2
        else{

                          //again checks which network won and which lost
            if(!blackWon){
                        // for loop fills wanted with 6 0's and a 1 (learner2 won)
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=1;
                    }
                    else{
                    wanted[i]=0;
                    }
                }
            }else{
              //for loop fills wanted with 6 1's and a 0 (learner2 lost)
                for(int i = 0; i<7; i++){
                    if(i == choiceStorage[index]){
                    wanted[i]=0;

                    }
                    //same principle with elseif for filled columns here
                    else if(availableStorage[index][i] == false){
                    wanted[i]=0;
                    }
                    else{
                      wanted[i]=1;
                    }
                }
            }
            //same evaluation process, using leaerner2 and temp2 though
            learner2P->setInputLayer(inputStorage[index]);
            learner2P->evaluate();
            temp2 += (learner2P->gradient(wanted, 0.1));
            //totalCost+= learner2P->cost(wanted);

    }
    }

//this part adds weight to both temp and temp2 to accmplosh two things, first to make it so that the activations stay in a consistent range and do not all go to 1 or 0,
//and secondly, to implement the principle that you should learn the most by losing a very short game or by winning a long game, and that you should also learn the least by winning a
//short game or losing a long game. If an AI is getting beat in the first 7 or eight m,oves, they are clearly missing something and need large changes to their activations, but if 
// they are winning in the first few moves it is usally due to their opponent making an error and thus they should not get this easy victory too far ingrained into them.
//If they lose a long game it is more likely that they were at least doing something right at the begining, so they should not make too drastic of changes as they just need little tweaks
float moveFloat = (float) moveNumber;

//the first goal is accomplished by the 0.01 and either 1 or 3 and the second goal is accomplished by the part with 43 and 2
    if(blackWon){
      temp *= (.01*(1*((2*(moveFloat))/43)));
      temp2 *= (.01*(3*(2*((43- (moveFloat)))/43))); 
    }
    if(blackWon == false){
      temp *= (.01*(3*(2*(43 - (moveFloat))/43)));
      temp2 *= (.01*(1*(2*((moveFloat)/43))));
    }

    //adds the gradients for this game to their corresponding networks and then saves the networks to their files.
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
    availableStorage[moveNumber][i] = availableSelections[i];

    //given the output vector from the neural network, find the index value of the choice that has the highest output value, provided that choice is of a column that is not filled up
    //choice is goint to represent a column number, so a value from 0 to 6
    int choice = -1;
    double Maxvalue = -1000;
    int choices [7];
    int pos = 0;
    //creates vector choices that contains all outputs that are avaiavlle and have the highest value
    //essentially used for the cause that the network has an equal prefrence for more than one of the possible columns it could chose from
    //makes that choice randomly because that is the fiarest way

//finds what the maximum value of outputs is
    for (int i = 0; i<7; i++){
        if(availableSelections[i]){
          if (outputs[i]>Maxvalue)
            Maxvalue = outputs[i];
        }
    }

//puts all availaible choices with that value into a vector
    for(int i = 0; i<7; i++){
        if(availableSelections[i]){
            if(outputs[i] == Maxvalue){
              choices [pos] = i;
              pos++;
	    }
        }

    } 

    //randomly chooses one of the elements of choices (the vestor with equal values) and sets that equal to choice
    int c = (int)(rnum()*(pos));
     choice = choices[c];   
     //keeps track of summary statistics
      numChoices+= pos;

    //stores each of the moves of the game(in terms of column number) in an array with index being the move number
    choiceStorage[moveNumber] = choice;
    //actually puts the move into the board and updates the board
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
  //decreases the number of open spaces, since a piece was put in the board
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
