//Simple paper rock scissors game created in C++
#include <iostream>
#include <stdio.h> //For NULL usage within srand for randomizing outcome based on system time
#include <stdlib.h> // For srand
#include <time.h> //For recieving system time to randomize numbers
using namespace std;

//global static variable of all potential outcomes in varied cases.
static string outcomes[] = {"paper", "rock", "scissors"};

string outcome(){
    string result;
    int i;

    /*Number randomized based off system time, srand gathers a seed. Time pulls it from the system time.
    being as the system time changes every second, this is nearly random. However, if done quick enough, as in
    within the same second, it will repeat the same result as the previous time. */
    srand(time(NULL));
    i = rand()%3;
    result = outcomes[i];
    return result;
}

void compare(string choice, string outcome){
    //Tie situations
    if(choice == outcome){
        cout << "\nThe result is a tie!";
    }else if(outcome == "rock" && choice == "paper"){ //Winning situations
        cout << "\nYou win!";
    } else if(outcome == "paper" && choice == "scissors"){
        cout << "\nYou win!";
    } else if(outcome == "scissors" && choice =="rock"){
        cout << "\nYou win!";
    } else { //Outside of tieing and winning, the only other option is toooo.....
        cout << "\nYou lose, sorry!";
    }
}

int main(){
    //This sets up the restart loop until something other than "y" is put.
    bool stop = false;

    while(!stop){
        string choice, result;
redo:
        cout <<"\nChoose paper, rock or scissors! ";
        cin >> choice;

        //Casing conversion - This makes it a bit easier to compare them in the future
        if(choice == "Paper"){
            choice = "paper";
        } else if(choice == "Rock"){
            choice = "rock";
        } else if(choice == "Scissors"){
            choice = "scissors";
        }

        //Verification, ensuring the input was one of the 6 options and not something complete random
        bool found = false;
        for(int i = 0; i < 3; i++){
            if(choice == outcomes[i]){
                found = true;
            }
        }
        while(!found){
            cout << "\nInvalid input, please try again";
            goto redo;
        }

        //Opponent's decision function call and printing to console.
        result = outcome();
        compare(choice, result);
        cout << "\nThe opponent choose: "<< result;

        //Restart or Stop the program
        char restart;
        cout <<"\nDo you wish to try? (y/n)";
        cin >> restart;
        if(restart == 'n' || restart == 'N'){
            stop = true;
        }
    }

    return 0;
}