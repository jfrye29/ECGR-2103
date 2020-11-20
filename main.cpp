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

enum Game {
    PigDice,
    TwoDice,
    BigPig,
    Hog
};

// Set this to set the maximum (winning) score
#define WIN_SCORE 20

// Forward declaration of the game functions
void displayMenu();
void displayPlayerMenu(Game game);
void gameLoop(bool computerPlayer, Game game);

int playerTurn_1dice();
int computerPlayerTurn_1dice();

int playerTurn_2dice();
int computerPlayerTurn_2dice();

int playerTurn_big_dice();
int computerPlayerTurn_big_dice();

int main() {
    srand(time(0));
    
    displayMenu();
    
    return 0;
}

void displayMenu() {
    int menuOption;
    char backToMenu;
    bool computerPlayer = false;
    
    //Game Menu
    cout << "\033[2J;\033[H";
    cout << "**************************************************************************************" << endl;
    cout << "\033[01;44;41m" << "                       Welcome to Pig Dice!                       " << "\x1B[0m" << endl;
    cout << endl;
    cout << "                       Game Menu" <<endl;
    cout << "1 - Instructions" << endl;
    cout << "2 - Pig Dice Game" << endl;
    cout << "3 - Two-Dice Pig" << endl;
    cout << "4 - Big Pig" << endl;
    cout << "5 - Hog" << endl;
    cout << "6 - Exit" << endl;
    
    cout <<  "Choose Menu Option: ";
    cin >> menuOption;
    cout << endl; 
    switch(menuOption) {
        case 1: {
            cout<<" Instructions:"<<endl;
            cout << endl;
            cout << endl;
            cout << " Pig Dice Game" << endl;
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
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "Would you like to return to the main menu? (y/n) ";
            cin >> backToMenu;
            if(backToMenu == 'y' ){
                displayMenu();   
            } else{
                cout << "BYE!!!" << endl;
                exit(0);
            }
            break;
        }
            
        // pig dice
        case 2:
            displayPlayerMenu(Game::PigDice);
            break;
        
        // 2-dice
        case 3:
            displayPlayerMenu(Game::TwoDice);
            break;
            
        //big pig
        case 4:
            displayPlayerMenu(Game::BigPig);
            break;
        
        // hog
        case 5:
            displayPlayerMenu(Game::Hog);
            break;
            
        case 6:
            exit(0);
    }
}

void displayPlayerMenu(Game game) {
    int choice = 0;
    cout << "1 - 1-Player" << endl;
    cout << "2 - 2-Player" << endl;
    cout << "3 - View Instructions" << endl;
    cout <<  "Choose Menu Option: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            gameLoop(true, game);
            break;
            
        case 2:
            gameLoop(false, game);
            break;
            
        case 3: {
            /*
            if (game == Game::TwoDice) {
            
            }
            
            switch (game) {
                case Game::TwoDice:
            }
            */
        } break;
    }
    // game loop
}

// The main game loop
// This will keep track of whose turn it is and the scores
//
// The algorithm:
//   Set the current player; call player turn
//   When playerTurn returns, the score is added to the player's current score
//   Check the scores- if one is >= 100 then we output the winner
//   If there is no winner, switch players and start again
void gameLoop(bool computerPlayer, Game game) {
    int currentPlayer = 1;
    int player1Score = 0;
    int player2Score = 0;
    
    while (player1Score < WIN_SCORE && player2Score < WIN_SCORE) {
        cout << "\033[2J\033[H";
        cout << endl << "=================================" << endl;
        cout << "Player " << currentPlayer << "'s turn." << endl;
        
        cout << "Current score: ";
        if (currentPlayer == 1) cout << player1Score;
        else cout << player2Score;
        cout << endl << endl;
        
        if (currentPlayer == 1) {
            switch (game) {
                case Game::PigDice: player1Score += playerTurn_1dice(); break;
                case Game::BigPig: player1Score += playerTurn_big_dice(); break;
                
                case Game::TwoDice: {
                    int score = playerTurn_2dice();
                    if (score == -1)
                        player1Score = 0;
                    else
                        player1Score += score;
                } break;
                
                case Game::Hog: break;
            }
            
            currentPlayer = 2;
        } else {
            if (computerPlayer) {
                switch (game) {
                    case Game::PigDice: player2Score += computerPlayerTurn_1dice(); break;
                    case Game::BigPig: player2Score += computerPlayerTurn_big_dice(); break;
                    
                    case Game::TwoDice: {
                        int score = computerPlayerTurn_2dice();
                        if (score == -1)
                            player2Score = 0;
                        else
                            player2Score += score;
                    } break;
                    
                    case Game::Hog: break;
                }
            } else {
                switch (game) {
                    case Game::PigDice: player2Score += playerTurn_1dice(); break;
                    case Game::BigPig: player2Score += playerTurn_big_dice(); break;
                    
                    case Game::TwoDice: {
                        int score = playerTurn_2dice();
                        if (score == -1)
                            player2Score = 0;
                        else
                            player2Score += score;
                    } break;
                    
                    case Game::Hog: break;
                }
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
int playerTurn_1dice() {
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

int playerTurn_2dice() {
    char choice = 0;
    int dice1 = 0;
    int dice2 = 0;
    int score = 0;
    
    do {
        dice1 = randomDice();
        dice2 = randomDice();
        cout << "Dice 1: " << dice1 << " | Dice 2: " << dice2 << endl;
        
        if (dice1 == 1 && dice2 == 1) {
            score = -1;
            
            cout << "Total score: 0. You lost everything." << endl;
        } else if (dice1 == 1 || dice2 == 1) {
            score = 0;
            
            cout << "Score: 0. Your turn is over." << endl;
        } else {
            score += dice1 + dice2;
            
            cout << "Score: " << score << ". Hold? (y,n)" << endl;
            cin >> choice;
        }
    } while ((dice1 != 1 && dice2 != 1) && !(choice == 'y' || choice == 'y'));
    
    return score;
}

int playerTurn_big_dice() {
    char choice = 0;
    int dice1 = 0;
    int dice2 = 0;
    int score = 0;
    
    do {
        dice1 = randomDice();
        dice2 = randomDice();
        cout << "Dice 1: " << dice1 << " | Dice 2: " << dice2 << endl;
        
        if (dice1 == 1 || dice2 == 1) {
            score = 0;
            
            cout << "Score: 0. Your turn is over." << endl;
        } else {
            if (dice1 == 1 && dice2 == 1) {
                score += 25;
            } else if (dice1 == dice2) {
                score += score * 2;
            } else {
                score += dice1 + dice2;
            }
            
            cout << "Score: " << score << ". Hold? (y,n)" << endl;
            cin >> choice;
        }
    } while ((dice1 != 1 && dice2 != 1) && !(choice == 'y' || choice == 'y'));
    
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

int computerPlayerTurn_1dice() {
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

int computerPlayerTurn_2dice() {
    int dice1 = 0;
    int dice2 = 0;
    int score = 0;
    char choice = 0;
    
    do {
        dice1 = randomDice();
        dice2 = randomDice();
        cout << "Dice 1: " << dice1 << " | Dice 2: " << dice2 << endl;
        
        if (dice1 == 1 && dice2 == 1) {
            lastScores.push_back(score);
            
            cout << "Total score: 0. You lost everything." << endl;
            return -1;
        } else if (dice1 == 1 || dice2 == 1) {
            lastScores.push_back(score);
            
            cout << "Score: 0. Computer's turn is over." << endl;
            return 0;
        } else {
            score += dice1 + dice2;
            
            if (!shouldIHold(score)) {
                choice = 'y';
            }
        }
    } while ((dice1 != 1 && dice2 != 1) && !(choice == 'y' || choice == 'y'));
    
    cout << "Computer holding at: " << score << endl;
    
    lastScores.push_back(score);
    return score;
}

int computerPlayerTurn_big_dice() {
    int dice1 = 0;
    int dice2 = 0;
    int score = 0;
    char choice = 0;
    
    do {
        dice1 = randomDice();
        dice2 = randomDice();
        cout << "Dice 1: " << dice1 << " | Dice 2: " << dice2 << endl;
        
        if (dice1 == 1 || dice2 == 1) {
            lastScores.push_back(score);
            
            cout << "Score: 0. Computer's turn is over." << endl;
            return 0;
        } else {
            if (dice1 == 1 && dice2 == 1) {
                score += 25;
            } else if (dice1 == dice2) {
                score += score * 2;
            } else {
                score += dice1 + dice2;
            }
            
            if (!shouldIHold(score)) {
                choice = 'y';
            }
        }
    } while ((dice1 != 1 && dice2 != 1) && !(choice == 'y' || choice == 'y'));
    
    cout << "Computer holding at: " << score << endl;
    
    lastScores.push_back(score);
    return score;
}

