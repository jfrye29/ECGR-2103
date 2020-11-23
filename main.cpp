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
#include <unistd.h>
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

int playerTurn_hog();
int computerPlayerTurn_hog();

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
    //cout << "\033[2J\033[H";
    cout << "**************************************************************************************" << endl;
    cout << "         " <<"\033[01;44;41m" << "                       Welcome to Pig Dice!                       " << "\x1B[0m" << endl;
    cout << endl;
    cout << " Game Menu" <<endl;
    cout << "1 - Pig Dice Game" << endl;
    cout << "2 - Two-Dice Pig" << endl;
    cout << "3 - Big Pig" << endl;
    cout << "4 - Hog" << endl;
    cout << "5 - Exit" << endl;
    
    cout <<  "Choose Menu Option: ";
    cin >> menuOption;
    cout << endl;
    switch(menuOption) {
        // pig dice
        case 1:
            displayPlayerMenu(Game::PigDice);
            break;

        // 2-dice
        case 2:
            displayPlayerMenu(Game::TwoDice);
            break;

        //big pig
        case 3:
            displayPlayerMenu(Game::BigPig);
            break;

        // hog
        case 4:
            displayPlayerMenu(Game::Hog);
            break;

        case 5:
            exit(0);
    }
}

void displayPlayerMenu(Game game) {
    int choice = 0;
    char backToMenu;

    cout << "\033[2J\033[H";
    cout << "1 - 1-Player" << endl;
    cout << "2 - 2-Player" << endl;
    cout << "3 - View Instructions" << endl;
    cout <<  "Choose Menu Option: ";
    cin >> choice;
    cout << "\033[2J\033[H";
    
    switch (choice) {
        case 1:
            gameLoop(true, game);
            break;
            
        case 2:
            gameLoop(false, game);
            break;
            
        case 3: {
            if (game == Game::PigDice) {
                cout<<" Basic Game Instructions:"<<endl;
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
                cout << "Would you like to return to the main menu? (y/n) ";
                cin >> backToMenu;
                if(backToMenu == 'y' ){
                    displayMenu();   
                } else{
                    exit(0);
                }
            }
            
            else if (game == Game::TwoDice) {
                cout << "Two-Dice Pig - This variation is the same as Pig, except:"<< endl;
                cout << "\t\u2022 Two standard dice are rolled. If neither shows a 1, their" <<endl;
                cout << "\t  sum is added to the turn total." <<endl;
                cout << "\t\u2022 If a single 1 is rolled, the player scores nothing and the" <<endl;
                cout << "\t  turn ends." <<endl;
                cout << "\t\u2022 If two 1s are rolled, the player’s entire score is lost," <<endl;
                cout << "\t  and the turn ends." <<endl;
                cout << endl;
                cout << "Would you like to return to the main menu? (y/n) ";
                    cin >> backToMenu;
                    if(backToMenu == 'y' ){
                        cout << "\033[2J\033[H";
                        displayMenu();   
                    } else{
                        exit(0);
                    }
                
            }
            
            else if (game == Game::BigPig) {
                cout << "Big Pig - This variation is the same as Two-Dice Pig, except:"<< endl;
                cout << "\t\u2022 If two 1s are rolled, the player adds 25 to the turn total." <<endl;
                cout << "\t\u2022 If other doubles are rolled, the player adds twice the " <<endl;
                cout << "\t  value of the dice to the turn total." <<endl;
                cout << endl;
                cout << "Would you like to return to the main menu? (y/n) ";
                    cin >> backToMenu;
                    if(backToMenu == 'y' ){
                        cout << "\033[2J\033[H";
                        displayMenu();   
                    } else{
                        exit(0);
                    }
                
            }
            
            else if (game == Game::Hog) {
                cout << "Hog - Hog is played as Pig where, at the beginning of a turn, the"<< endl;
                cout << "player decides how many dice to roll and rolls them all at"<< endl;
                cout << "once. If any 1's (""hogs"") are rolled, there is no score for the" <<endl;
                cout << "turn. Otherwise, the sum of the dice are scored. In either " <<endl;
                cout << "case, it becomes the next player's turn." <<endl;
                cout << endl;
                cout << "Would you like to return to the main menu? (y/n) ";
                    cin >> backToMenu;
                    if(backToMenu == 'y' ){
                        cout << "\033[2J\033[H";
                        displayMenu();   
                    } else{
                        exit(0);
                    }
                
            }
            
            
            
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
        //cout << "\033[2J\033[H";
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
                case Game::Hog: player1Score += playerTurn_hog(); break;
                
                case Game::TwoDice: {
                    int score = playerTurn_2dice();
                    if (score == -1)
                        player1Score = 0;
                    else
                        player1Score += score;
                } break;
            }
            
            currentPlayer = 2;
        } else {
            if (computerPlayer) {
                switch (game) {
                    case Game::PigDice: player2Score += computerPlayerTurn_1dice(); break;
                    case Game::BigPig: player2Score += computerPlayerTurn_big_dice(); break;
                    case Game::Hog: player2Score += computerPlayerTurn_hog(); break;
                    
                    case Game::TwoDice: {
                        int score = computerPlayerTurn_2dice();
                        if (score == -1)
                            player2Score = 0;
                        else
                            player2Score += score;
                    } break;
                }
            } else {
                switch (game) {
                    case Game::PigDice: player2Score += playerTurn_1dice(); break;
                    case Game::BigPig: player2Score += playerTurn_big_dice(); break;
                    case Game::Hog: player2Score += playerTurn_hog(); break;
                    
                    case Game::TwoDice: {
                        int score = playerTurn_2dice();
                        if (score == -1)
                            player2Score = 0;
                        else
                            player2Score += score;
                    } break;
                }
            }
            
            currentPlayer = 1;
        }
    }
    
    cout << endl;
    if (player1Score >= WIN_SCORE) {
        cout << "\033[01;44;42m" << "Player 1 Won!!!!" << "\x1B[0m" << endl;
        displayMenu();
    } else {
        cout << "\033[01;44;42m" << "Player 2 Won!!!!" << "\x1B[0m" << endl;
        displayMenu();
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

int playerTurn_hog() {
    int dice_count = 1;
    int score = 0;
    
    cout << "Enter number of dice to roll: ";
    cin >> dice_count;
    
    for (int i = 0; i<dice_count; i++) {
        int dice = randomDice();
        
        if (dice == 1) {
            cout << "You rolled a 1-> No score." << endl;
            return 0;
        }
            
        score += dice_count;
    }
    
    cout << "Score for this turn: " << score << endl;
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

int computerPlayerTurn_hog() {
    int dice_count = 1;
    int score = 0;
    
    dice_count = rand() % 21;
    cout << "Computer wants to roll " << dice_count << " dice." << endl;
    
    for (int i = 0; i<dice_count; i++) {
        int dice = randomDice();
        
        if (dice == 1) {
            cout << "computer rolled a 1-> No score." << endl;
            return 0;
        }
            
        score += dice_count;
    }
    
    cout << "Computer's score for this turn: " << score << endl;
    return score;
}

