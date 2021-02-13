/*Lottery double linked list final project for Programming languages 2
by Kurtis Shane Wilhoite (Prepare for a lot of comments)*/
#include <iostream> //Cin and cout functionality
#include <vector> //Vector functionality
#include <algorithm> //Usage of sort()
#include "lotlib.h" //Classes
using namespace std;

//Basic template to display at the start to explain the program
void intro(){
    cout << "X============================================X";
    cout << "\nWelcome to the Circular Doubly linked list\n";
    cout << "\nC++ Final project. This is a lottery generator\n";
    cout << "\nplease enter numbers 6 numbers from 1-40 below.\n";
    cout << "\nX============================================X";
}

//Simply prints out the user's input in a line
void userPrint(vector<int> user){
    cout<<"\nYour numbers: ";
    for(int i = 0; i < user.size(); i++){
        cout << user[i]<< " ";
    }
}

//Checks the user's input for various potential mistakes
bool verifyInput(int check, vector<int> user){
    for(int i = 0; i < user.size(); i++){ //Checking for duplicates
        if(check == user[i]){
            cout<<"\nDuplicates are not allowed, please try another: ";
            return false;
        }
    }
    if(cin.fail()){ //Checking for inputs other than numbers
        cout <<"\nOnly input numbers, please try another: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    if(check < 1 || check > 40){ //Checking for anything above 40 or under 1
        cout<<"\nOnly numbers between 1-40 are valid, please try another: ";
        return false;
    } else{ //Otherwise, it's fine and passes the test
        return true;
    }
}

//Nested for loop that checks the two vectors, user's vector and random vector, to see if there are any matches
int winChecks(vector<int> user, lotto lottery){
    int wins = 0;
    for(int i = 0; i < user.size(); i++){
        for(int j = 0; j < lottery.lotteryList.size(); j++){
            if(user[i] == lottery.lotteryList[j]){
                wins = wins+1;
            }
        }
    }
    return wins;
}

//Displays various messages describing the rewards for the matches
void rewardCheck(int wins){ 
    if(wins == 0){
        cout<<"\nBetter luck next time!";
    }else if(wins == 1){
        cout <<"\nYou get your money back!";
    }else if(wins == 2){
        cout <<"\nYou've won 15e!";
    }else if(wins == 3){
        cout <<"\nYou've won 250e!";
    }else if(wins == 4){
        cout <<"\nYou've won 20,000e!";
    }else if(wins == 5){
        cout <<"\nYou just missed by 1 point, you wni 100,000e!";
    } else{
        cout <<"\nCongrats! You've won the 100e million jackpot!";
    }
}


int main(){
    //Initalizing some variables used for later
    vector<int> user;
    int temp;
    lotto lottery;

    intro();

    //Loops and asks for user's selections
    for(int i = 0; i < 6; i++){
        bool loop = true;
        while(loop == true){
            loop = false;
            cout << "\nEnter number "<<(i+1)<<" (between 1-40): ";
            while(!(cin >> temp)){
                cout << "\nPlease input only a number, please try another: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if(verifyInput(temp, user) == false){
                loop = true;
            } else{
                user.push_back(temp); //If it passed the checks, it's pushed into the user vectors
            }
        }
    }
    sort(user.begin(), user.end()); //Cleaning the array just created
    userPrint(user); //Printing t after cleaning

    lottery.createListing(); //Creates the lottery's numbers
    lottery.printLotteryListing();

    cout<< "\nX========================================X";
    cout<< "\nPoints: "<<winChecks(user, lottery)<<endl;
    rewardCheck(winChecks(user, lottery));
    cout<< "\nX========================================X\n";

    system("pause"); //It automatically closes on my end if I don't put a pause at the end to close it.
    return 0;
}