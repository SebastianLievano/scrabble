#include "globals.h"

//Global gameBoard class manages everything
//Game setup is all managed in the constructor of this function
gameBoard g;

//Helper Functions
int getValue(char a);
bool turnParser(stringstream& input, Player &p);
void playerTurn(Player* p);

//Main function manages main gameplay cycle
int main(){
    //gameOver function
    bool gameOver = false;
    //turn counter
    int turn = 0;
    //number of players
    int numPlayers = g.getNumPlayers();
    cin.clear();
    cin.ignore(1);
    //looping player turns
    while(!gameOver){
        playerTurn(g.getPlayer(turn));
        if(turn < numPlayers-1) turn++;
        else if (turn == numPlayers-1) turn = 0;
    }
}

//Player turn
void playerTurn(Player* p){
    //print board and hand
    g.printBoard();
    p->printHand();
    string line, dummy;
    bool doneTurn = false;
    while(!doneTurn){
        //Receiving input move
        cout << "Coordinates are Start(0-14). Direction is H or V. Enter 0 to Pass" << endl <<
        "Input(WORD ROW COL DIR): ";
        getline(cin, line); 
        //If user inputted 0 to pass, they are skipped
        if (line == "0") {
            cout << "Turn skipped!\n" << endl;
        } else {
            //If not, stringstream is created
            stringstream input(line);
            //Turn is parsed
            doneTurn = turnParser(input, *p);
            //If move returns invalid, doneTurn is set to false and loop is replayed
            if(!doneTurn) cout << "Invalid move!" << endl;
            else{
                //Moving on to next turn
                cout << "Press any key to continue" << endl;
                cin >> dummy;
                for(int i = 0; i < 20; i++) cout << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.clear();
            }
        }   
    }  
}

//GetValue: returns scrabble value of a character
int getValue(char a){
    int val;
    switch(a) {
        //Uses cascading cases to limit repetition. Assumed error free input so only scores above 1 are calculated
        case '~': val = 0; break;
        case 'D':
        case 'G': val = 2; break;
        case 'B' : case 'M' :
        case 'P' : val = 3; break;
        case 'F' : case 'H' : case 'V' : case 'W' :
        case 'Y' : val = 4; break;
        case 'K' : val = 5; break;
        case 'J' : case 'X' : val = 8;  break;
        case 'Q' : case 'Z' : val = 10; break;
        default: val = 1; break;
    }
    return val;
}

//turnParser: parses user input and plays move if valid.
bool turnParser(stringstream & input, Player &p) {
    bool success;
    string word;
    int row, col;
    char dir;

    //input into word
    input >> word;
    cout << word << endl;

    if (input.fail()) {
        return false;
    }
    //checking row and col inputs
    input >> row; 
    if (input.fail()) {
        return false;
    } else if (row < 0 || row > 14) return false;

    input >> col;
    if (input.fail()) {
        return false;
    } else if (col < 0 || col > 14) return false;
    
    //ensuring direction is either H or V
    input >> dir;
    if (input.fail()) {
        return false;
    } else if (dir != 'V' && dir != 'H') return false;

    //creating a start coordinate
    coord start(row, col);
    
    //running player playMove method function
    success = p.playMove(word, start, dir);
    if(success) return true;
    else return false;
}
