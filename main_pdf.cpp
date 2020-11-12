/*

Class: ECGR 2103 - 003
Project: Final Project - Pig Dice Game  
Team #4: Justus Frye, Robert Griffin, Patrick Flynn
Date: 12/01/20

*/

#include <iostream>
#include <cstdlib>
#include <ctime>  
#include <cmath>
using namespace std;

// Forward declaration of the game functions
void gameLoop();
int playerTurn();

int main(){
    
    srand(time(0));
    //Initialize Variables
    char instructionsNeeded; 
    
    // Welcome the user
    cout << "\033[01;44;41m" << "Welcome to Pig Dice!" << "\x1B[0m" << endl;
    
    //Ask User If they Need Instructions
    cout << "Would you like to see the instructions for the Pig Dice game? (y/n)";
    cin >>instructionsNeeded;
    
    if (instructionsNeeded == 'y') {
        //Output Instructions
        cout<<" Instructions:"<<endl;
        cout<<" The rules are simple: Two players race to reach 100 points. Each turn,"<<endl;
        cout<<" a player repeatedly rolls a die until either a 1 is rolled or the"<<endl;
        cout<<" player holds and scores the sum of the rolls (i.e. the turn total). At "<<endl;
        cout<<" any time during a player's turn, the player is faced with two decisions:"<<endl;
        cout<<""<<endl;
        cout<<" roll- If the player rolls a "<<endl;
        cout<<"\t1: the player scores nothing and it becomes the opponent's turn."<<endl;
        cout<<"\t2 - 6: the number is added to the player's turn total and the player's turn continues."<<endl;
        cout<<""<<endl;
        cout<<" hold- The turn total is added to the player's score and it "<<endl;
        cout<<" becomes the opponent's turn."<<endl;
    }
    
    gameLoop();
    return 0;
}

// The main game loop
// This will keep track of whose turn it is and the scores
//
// The algorithm:
//   Set the current player; call player turn
//   When playerTurn returns, the score is added to the player's current score
//   Check the scores- if one is >= 100 then we output the winner
//   If there is no winner, switch players and start again
void gameLoop() {
    int currentPlayer = 1;
    int player1Score = 0;
    int player2Score = 0;
    
    while (player1Score < 100 && player2Score < 100) {
        cout << endl << "=================================" << endl;
        cout << "Player " << currentPlayer << "'s turn." << endl;
        
        cout << "Current score: ";
        if (currentPlayer == 1) cout << player1Score;
        else cout << player2Score;
        cout << endl << endl;
    
        int score = playerTurn();
        
        if (currentPlayer == 1) {
            player1Score += score;
            currentPlayer = 2;
        } else {
            player2Score += score;
            currentPlayer = 1;
        }
    }
    
    cout << endl;
    if (player1Score >= 100) {
        cout << "Player 1 won!!!!" << endl;
    } else {
        cout << "Player 2 won!!!!" << endl;
    }
}

// We only need one function- it will generate a new random number
// each time we call it
int randomDice(){
    int dice1 = (rand() % 6) + 1; 
    return dice1;
}


// A player loop. This will return how much new score the user has won
//
// The algorithm (use do-while)
//   Roll dice. If dice is 1, score is set to 0 and we return
//   If not 1, add that to the user's score.
//   Ask if they want to hold or roll again.
//      If hold, return the score
//      If roll again, start the loop over
int playerTurn() {
    char choice = 0;
    int dice = 0;
    int score = 0;
    
    do {
        dice = randomDice();
        cout << "Dice: " << dice << endl;
        
        if (dice == 1) {
            score = 0;
            
            cout << "Score: 0. Your turn is over." << endl;
        } else {
            score += dice;
            
            cout << "Score: " << score << ". Hold? (y,n)" << endl;
            cin >> choice;
        }
    } while (dice != 1 && !(choice == 'y' || choice == 'y'));
    
    return score;
}

