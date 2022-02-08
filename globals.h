/*
globals.h
Contains initialization of classes and functions
*/
#pragma once

#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;

#define empty '0' //setting 0 (character) as empty value
//pre-declaring player class as it is used in gameBoard
class Player;

//coord struct w. two constructors
struct coord{
    int row;
    int col;
    coord();
    coord(int i, int j){
        row = i;
        col = j;
    }
};

//square struct contains letter and word multipliers, as well as the letter it currently contains
struct square{
    int lm;
    int wm;
    char letter;
};

//helper functions
int getValue(char a);


//Class Declaration: gameBoard
//gameBoard contains the board, the bag of tiles, and the dictionary, as well as a pointer
//to an array of players.
class gameBoard{
    private:
        square board[15][15];               //board array of square structs
        char bag[100];                      //bag array of characters
        int tileCounter = 0;                //used to track tiles
        int turnCounter = 1;                //tracks turns
        unordered_set<string> dictionary;   //dictionary set 
                                            //unordered set used for fast lookup and load times
        Player* playerArray;                //Array of players
        int nPlayers;                       //number of players
    public:
    //Constructor
        gameBoard();
        ~gameBoard();
    //Accessor
        char getBoard(coord c);
        char gBoard(int row, int col);
        int getTurnCounter();
        Player* getPlayer(int number);
        int getNumPlayers();
    //Utility
        //Calculates Score Value of a word
        int calcScore(string word, coord start, char dir);

        //Checks if a word can be placed/board spots are available
        bool checkValidPlacement(string word, coord start, char dir); 

        //Checks if word is in dictionary
        bool checkWord(string word);

        //Checks individual offshoots of given letter. Returns score
        int checkEachOffshoot(char letter, int row, int col, char dir);

        //Parent offshoot function, checks all letters
        int checkOffshoots(string word, coord start, char dir); 

        //Parent validity checker, determines if word can be played or not
        int validWord(string word, string hand, coord start, char dir); 

        //Mutates board. Only fed valid plays
        void playMove(string word, coord start, char dir);

        //Prints Board
        void printBoard();

        //Draws character from bag and moves charIndex to next square
        char drawBag();

        //Initializes Player
        void initializePlayers();

        //Friend class for convenience
        friend class Player;
};


//Player class contains player hands, names, and scores, as well as a pointer to their gameboard. 
class Player{
    private:
        int score;
        string name;
        string hand;
        gameBoard* g;
    public:
        //Constructor
        Player();
        Player(string name, gameBoard* gb);
        //Accessors
        int getScore();
        string getName();

        string getHand();

        //Mutators
        void raiseScore(int pts);
        void setBoard(gameBoard* ptr);
        void setName(string n);
        void newHand();

        //Utility

        //Returns false if player can't play move, true if they can
        bool playMove(string word, coord start, char dir);

        //Chec
        bool checkIfCanPlace(string word);
        bool changeHand(string word, coord start, char dir);
        void printHand();
};

//Class Declarations



