#include "globals.h"

//GameBoard Class

gameBoard::gameBoard(){
    //Initializing BAG
    string dummy;
    unsigned seed = /*time(0)*/0;
    cout << "Initializing Game" << endl;
    ifstream file("initializer.txt");
    for(int i = 0; i < 100; i++){
        file >> bag[i];
    }
    //Randomizing Bag
    shuffle(bag, bag + 100, default_random_engine(seed));
    //Initializing BOARD multipliers 
    for(int i = 0; i < 15; i++){
        for(int j= 0; j < 15; j++){
            file >> board[i][j].lm; 
            board[i][j].letter = empty;
        }
    }
    for(int i = 0; i < 15; i++){
        for(int j= 0; j < 15; j++){
            file >> board[i][j].wm; 
        }
    }
    //Initializing DICTIONARY
    while(!file.eof()){ //inputting from file stream into dummy string and then dummy string into dictionary set
        file >> dummy; //Loops until eof reached
       // cout << "loading dictionary w. " << dummy;
        dictionary.insert(dummy);
    }

    //Initializing Player Array
    initializePlayers();
}

void gameBoard::initializePlayers(){
    bool gettingPlayerNum = true;
    int numPlayers;
    string playerName;
    while (gettingPlayerNum) {
        cout << "Enter the number of players (2-4): ";

        cin >> numPlayers;
        
        if (cin.fail()) {
            cout << "Enter a number between 2-4\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            if (numPlayers >= 2 && numPlayers <= 4) {
                cout << numPlayers << " players selected\n";
                gettingPlayerNum = false;
            } else cout << "Enter a number between 2-4\n";
        }
    }
    playerArray = new Player[numPlayers];
    nPlayers = numPlayers;
    for(int i = 0; i < numPlayers; i++){
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> playerName;

        playerArray[i] = Player(playerName, this);
        playerArray[i].newHand();
    }

}

gameBoard::~gameBoard(){
    delete [] playerArray;
}

int gameBoard::getNumPlayers(){
    return nPlayers;
}

Player* gameBoard::getPlayer(int number){
    return &playerArray[number];
}
int gameBoard::getTurnCounter(){
    return turnCounter;
}

char gameBoard::getBoard(coord c){
    return board[c.row][c.col].letter;
}

char gameBoard::gBoard(int row, int col){
    return board[row][col].letter;
}

int gameBoard::calcScore(string word, coord start, char dir){
    int value = 0;
    int multiplier = 1;
    if(dir == 'H'){
        for(int j = 0; j < word.length(); j++){
            value += (getValue(word[j])*board[start.row][j].lm);
            multiplier = multiplier*board[start.row][j].wm;
        }
    }
    else if(dir == 'V'){
        for(int i = 0; i < word.length(); i++){
            value += (getValue(word[i])*board[i][start.col].lm);
            multiplier = multiplier*board[i][start.col].wm;
        }
    }
    return value;
}


bool gameBoard::checkWord(string word){
    if(!dictionary.count(word)){ 
        return false;
    }
    return true;
}

int gameBoard::checkOffshoots(string word, coord start, char dir){
    int row = start.row, col = start.col, score = 0, val;
    for(int i = 0; i < word.length(); ++i){
        if(dir == 'H' && board[row][col+i].letter == empty) val = checkEachOffshoot(word[i], row, col + i, dir);
        else if(dir == 'V' && board[row+i][col].letter == empty) val = checkEachOffshoot(word[i], row+i, col, dir);
        if(val) score += val;
        else if(val == -1) return -1;
    }
    return score;
}


int gameBoard::checkEachOffshoot(char letter, int row, int col, char dir){
    //for convenience:
    int i = 1, j = 1, score = 0;
    coord oStart(row, col);
    string offshoot= "";
    switch(dir){
        case 'H':{
            //Above
            while(board[row - j][col].letter != empty && (row - j) >= 0){
                if(j == 1) offshoot = letter;
                offshoot = board[row - j][col].letter + offshoot;
                ++j;
            }
            --j;
            oStart.row -= j;
            //Below
            while(board[row + i][col].letter != empty && (row + i) < 15){
                if( j == 0 && i == 1) offshoot = letter;
                offshoot = offshoot + board[row + i][col].letter;
                ++i;
            }
        }
        case 'V':{
            while(board[row][col-j].letter != empty && (col - j) >= 0){
                if(j == 1) offshoot = letter;
                offshoot = board[row][col-j].letter + offshoot;
                ++j;
            }
            --j;
            oStart.col -= j;
            while(board[row][col + i].letter != empty && (col + i) < 15){
                if(j == 0 && i == 1) offshoot = letter;                        
                offshoot = offshoot + board[row][col + i].letter;
                ++i;
            }
        }
    }
    if(offshoot == "") return 0;
    if(!checkWord(offshoot)){
        cout << offshoot << " is an invalid word" << endl;
        return -1;
    }
    score = calcScore(offshoot, oStart, dir);
    cout << offshoot << "is valid and worth " << score << "points" << endl;
    return score;
}

int gameBoard::validWord(string word, string hand, coord start, char dir){
    int score;
    if(checkValidPlacement(word, start, dir)){
            if(checkWord(word)){
                if(0 <= checkOffshoots(word, start, dir)){
                    return (calcScore(word, start, dir) + checkOffshoots(word, start, dir));
                }
                else cout << "An offshoot of your word is invalid" << endl;
            }
            else cout << word << " is invalid" << endl;
    }
    else cout << "Invalid Placement" << endl;
    return 0;
}

void gameBoard::playMove(string word, coord start, char dir){
    for(int i = 0; i < word.length(); i++){
        if(dir == 'H') board[start.row][start.col+i].letter = word[i];
        else if(dir == 'V') board[start.row+i][start.col].letter = word[i];
    }
    turnCounter++;
}

void gameBoard::printBoard(){ 
    bool printFirst = true;
    cout << "            SCRABBLE            " << endl << "   ";
    for(int i = 0; i<15; i++){ cout << "___";}
    cout << endl << "   ";
    for(int i = 0; i < 15; i ++){ //Top row
        if(i < 10) cout << " " << i; 
        else cout << " " << i;
    }
    cout << endl;
    for(int i = 0; i < 15; i ++){
        if(i < 10) cout << " "; 
        cout << i << "|";
        printFirst = true;
        for(int j = 0; j < 15; j ++){
            if(board[i][j].letter == empty){
                if(board[i][j].lm != 1){
                    cout << "[" << board[i][j].lm << "]";
                    printFirst = false;
                }
                else if(board[i][j].wm != 1){
                    cout << "(" << board[i][j].wm << ")";
                    printFirst = false;
                }
                else{
                    if(j == 0) cout << "|";                    
                    cout << " ";
                    if(board[i][j+1].lm == board[i][j+1].wm && j < 14)cout << "|";
                    if(j == 14) cout << "|";
                }
            }
            else if(board[i][j].letter != empty){
                if(board[i][j].lm == 2){
                    cout << "!" << board[i][j].letter << "!";
                    printFirst = false;
                }
                else if(board[i][j].lm == 3){
                    cout << "[" << board[i][j].letter << "]";
                    printFirst = false;
                }                
                else if(board[i][j].wm == 2){
                    cout << "(" << board[i][j].letter << ")";
                    printFirst = false;
                }
                else if(board[i][j].wm == 3){
                    cout << "{" << board[i][j].letter << "}";
                    printFirst = false;
                }
                else{
                    if(j == 0) cout << "|";
                    cout << board[i][j].letter;
                    if(board[i][j+1].lm == board[i][j+1].wm && j < 14)cout << "|";
                }
            }
        }
        if(i == 4) cout << "     ScoreBoard: ";
        if(i > 4 && i <= 4+nPlayers){
            cout << "      " << playerArray[i-5].getName() << ": " << playerArray[i-5].getScore() << " pts";
        }
        cout << endl;
    }
    for(int i = 0; i < 15; i ++) cout << "---";
    cout << endl;
}

char gameBoard::drawBag(){
    char output;
    output = bag[tileCounter];
    tileCounter++;
    if(tileCounter > 99){
        return '0';
    }
    return output;
}


bool gameBoard::checkValidPlacement(string word, coord start, char dir){
    int wordLength = word.length(), startPos, endPos;
    char startLetter, endLetter;
    bool startLetterEmpty = false, startLetterMatches = false, endLetterMatches = false, endLetterEmpty = false, connected = false;
    // Edge case: first turn
    cout << endl << "Turn: " << getTurnCounter() << endl;
    if (getTurnCounter() == 1) {
        cout << "special turn case" << endl;
        if (dir == 'H') {
            if (start.row != 7){return false;}
            startPos = start.col;
        } else {
            if (start.col != 7){return false;}
            startPos = start.row;
        }
        
        if (startPos > 7){cout << "4" << endl; return false;}
        endPos = startPos + wordLength - 1;

        if (endPos < 7){cout << "5" << endl; return false;}
        return true;
    } else {
        for(int i = 0; i < word.length(); i++){
            if((dir == 'V' && gBoard(start.row+i, start.col) != empty) || (dir == 'H' && gBoard(start.row, start.col+i) != empty)){
                if((dir == 'V' && gBoard(start.row+i, start.col) == word[i]) || (dir == 'H' && gBoard(start.row, start.col+i) == word[i])) connected = true;
                else return false;
            }
        }
        if(dir == 'V' && (gBoard(start.row - 1, start.col) != empty || gBoard(start.row + word.length(), start.col) != empty)) return false;
        if(dir == 'H' && (gBoard(start.row , start.col - 1) != empty || gBoard(start.row, start.col + word.length()) != empty)) return false;
    }
    if (connected == false) return false;
    return true;
}

