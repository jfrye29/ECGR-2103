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

int randomDice1(){
    int dice1 = (rand() % 6) + 1; 
    return dice1;
}

int randomDice2(){
    int dice2 = (rand() % 6) + 1; 
    return dice2;
}

int main(){
    
    srand(time(0));
    //Initialize Variables
    int diceRoll1 = randomDice1();
    int diceRoll2 = randomDice2();
    char instructionsNeeded; 
    
    cout << "\033[01;44;41m" << "Welcome to Pig Dice!" << "\x1B[0m" << endl;
    //Ask User If they Need Instructions
    cout << "Would you like to see the instructions for the Pig Dice game? (y/n)";
    cin >>instructionsNeeded;
    
    if(instructionsNeeded == 'y'){
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
    
    cout << "Dice Roll:" << "\nDice1: " << diceRoll1 << "\nDice2: " << diceRoll2 << endl;
    return 0;
}
