#include "globals.h"

gameBoard g;

//Helper Functions
int getValue(char a);
bool turnParser(stringstream& input, Player &p);
void playerTurn(Player* p);

int main(){

    bool gameOver = false;
    int turn = 0;
    int numPlayers = g.getNumPlayers();
    cin.clear();
    cin.ignore(1);
    while(!gameOver){
        playerTurn(g.getPlayer(turn));
        if(turn < numPlayers-1) turn++;
        else if (turn == numPlayers-1) turn = 0;
    }
}

void playerTurn(Player* p){
    g.printBoard();
    p->printHand();
    string line, dummy;
    bool doneTurn = false;
    while(!doneTurn){
        cout << "Coordinates are Start(0-14). Direction is H or V. Enter 0 to Pass" << endl <<
        "Input(WORD ROW COL DIR): ";
        getline(cin, line);

        if (line == "0") {
            cout << "Turn skipped!\n" << endl;
        } else {
            stringstream input(line);
            doneTurn = turnParser(input, *p);
            if(!doneTurn) cout << "Invalid move!" << endl;
            else{
                cout << "Press any key to continue" << endl;
                cin >> dummy;
                for(int i = 0; i < 20; i++) cout << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.clear();
            }
        }   
    }  
}

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

bool turnParser(stringstream & input, Player &p) {
    bool success;
    string word;
    int row, col;
    char dir;

    input >> word;
    cout << word << endl;

    if (input.fail()) {
        return false;
    }

    input >> row; 
    if (input.fail()) {
        return false;
    } else if (row < 1 || row > 15) return false;

    input >> col;
    if (input.fail()) {
        return false;
    } else if (col < 1 || col > 15) return false;

    input >> dir;
    if (input.fail()) {
        return false;
    } else if (dir != 'V' && dir != 'H') return false;

    coord start(row, col);
    
    success = p.playMove(word, start, dir);
    if(success) return true;
    else return false;
}
