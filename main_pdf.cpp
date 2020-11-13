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
#include <vector>
using namespace std;

// Set this to set the maximum (winning) score
#define WIN_SCORE 100

// Forward declaration of the game functions
void gameLoop();
int playerTurn();
int computerPlayerTurn();

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
    bool computerPlayer = false;
    
    cout << "Do you wish to fight the computer? (y,n)" << endl;
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        computerPlayer = true;
    }
    
    while (player1Score < WIN_SCORE && player2Score < WIN_SCORE) {
        cout << endl << "=================================" << endl;
        cout << "Player " << currentPlayer << "'s turn." << endl;
        
        cout << "Current score: ";
        if (currentPlayer == 1) cout << player1Score;
        else cout << player2Score;
        cout << endl << endl;
        
        if (currentPlayer == 1) {
            player1Score += playerTurn();
            currentPlayer = 2;
        } else {
            if (computerPlayer) {
                player2Score += computerPlayerTurn();
            } else {
                player2Score += playerTurn();
            }
            currentPlayer = 1;
        }
    }
    
    cout << endl;
    if (player1Score >= WIN_SCORE) {
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

// Logic for the computer player
// This is the idea behind the computer player:
//
// So we have a vector that holds all the scores either when the computer decided to hold,
// or just before their score was zeroed after rolling 1.
//
// If the computer has no scores, we hold if the score is greater than 15 (because you will very likely roll
// a 1 sooner or later).
//
// Otherwise, we just average all the scores. Then we check the difference between the average score and the
// current score (taking the absolute value so we don't end up with a negative number). This value is our
// margin. If the margin is greater than a certain threshold, then we continue. Otherwise, we hold.

vector<int> lastScores;

bool shouldIHold(int current) {
    if (lastScores.size() == 0) {
        if (current >= 15) {
            return true;
        }
        return false;
    }
    
    int size = lastScores.size();
    int average = 0;
    
    for (int score : lastScores) {
        average += score;   
    }
    
    average = average / size;
    int margin = abs(average-current);
    
    if (margin > 5) {
        return false;
    }
    return true;
}

int computerPlayerTurn() {
    int dice = 0;
    int score = 0;
    char choice = 0;
    
    do {
        dice = randomDice();
        cout << "Dice: " << dice << endl;
        
        if (dice == 1) {
            lastScores.push_back(score);
            
            cout << "Score: 0. Computer's turn is over." << endl;
            return 0;
        } else {
            score += dice;
            
            if (!shouldIHold(score)) {
                choice = 'y';
            }
        }
    } while (dice != 1 && !(choice == 'y' || choice == 'y'));
    
    cout << "Computer holding at: " << score << endl;
    
    lastScores.push_back(score);
    return score;
}

