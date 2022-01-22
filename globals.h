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

#define empty '0'

class Player;

struct coord{
    int row;
    int col;
    coord();
    coord(int i, int j){
        row = i;
        col = j;
    }
};

struct square{
    int lm;
    int wm;
    char letter;
};

int getValue(char a);

class gameBoard{
    private:
        square board[15][15];
        char bag[100];
        int tileCounter = 0;
        int turnCounter = 1;
        unordered_set<string> dictionary;
        Player* playerArray;
        int nPlayers;
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
    //Mutator
        int calcScore(string word, coord start, char dir);
        bool checkValidPlacement(string word, coord start, char dir); //Checks if a word can be placed from start to end. 
        string lettersNeeded(string word, coord start, char dir); //Checks if player can play word w given letters
        bool lettersAvail(string hand, string word, coord start, char dir);
        bool checkWord(string word); //Checks if word is in Dictionary
        int checkOffshoots(string word, coord start, char dir); 
        int validWord(string word, string hand, coord start, char dir); 
        void playMove(string word, coord start, char dir);
        void printBoard(); //Prints Board
        char drawBag(); //Draws from bag. Updates Bag as well
        void initializePlayers();
        friend class Player;
};

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
        bool playMove(string word, coord start, char dir);
        void drawTiles();
        bool checkIfCanPlace(string word);
        bool changeHand(string word, coord start, char dir);
        void printHand();
};

//Class Declarations



