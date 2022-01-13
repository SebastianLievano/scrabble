#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include <unordered_set>
using namespace std;

struct coord{
    int row;
    int col;
};

struct square{
    int lm;
    int wm;
    char c;
};

class gameBoard{
    private:
        square board[15][15];
        char bag[100];
        int counter = 0;
    public:
    //Constructor
        gameBoard();
    //Accessor
        char getBoard(coord c);
    //Mutator
        bool checkValidPlacement(string word, coord start, coord end); //Checks if a word can be placed from start to end. 
        void placeWord(string word, coord start, coord end); //Places word in appropriate coordinates. NO ERROR CHECKING
        void printBoard(); //Prints Board
        char drawBag(); //Draws from bag. Updates Bag as well
};


class Player{
    private:
        int score;
        string name;
        char hand[7];
    public:
        //Constructor
        Player(string name);
        //Accessors
        int getScore();
        string getName();

        //Mutators
        void setScore();

        //Utility
        void drawTiles();
        bool checkIfCanPlace(string word);
        void printHand();
};