#include "globals.h"



Player::Player(){
    score = 0;
}

Player::Player(string n, gameBoard* gb){
    name = n;
    score = 0;
    g = gb;

}

//Accessors
int Player::getScore(){
    return score;
}
        
string Player::getName(){
    return name;
}

string Player::getHand(){
    string h = "";
    for(int i = 0; i < 7; i++){
        h = h + hand[i];
    }
    return h;
}

//Mutators
void Player::newHand(){
    for(int i = 0; i < 7; i++){
        hand[i] = g -> drawBag();
    }
}

void Player::raiseScore(int pts){
    score += pts;
}

void Player::setName(string n){
    name = n;
}

void Player::setBoard(gameBoard* ptr){
    g = ptr;
}


//Utility
bool Player::playMove(string word, coord start, char dir){
    int doableMove;
    bool found = false, cando;




    doableMove = g->validWord(word, hand, start, dir);
    if(doableMove){
        cando = changeHand(word, start, dir);
        if(cando){
            g->playMove(word, start, dir);
            g->printBoard();
            score += doableMove;
            cout << "Word " << word << " was valid. You gained " << doableMove << " pts" << endl;
            cout << "Your new hand is ";
            for(int i = 0; i <7; i++) cout << hand[i];
            cout << endl;
            return true;
        }
        else{
            cout << "can't play that word w. your hand" << endl;
            return false;
        }
    }
    else return false;
}

bool Player::changeHand(string word, coord start, char dir){
    bool found = false;
    int dRow, dCol, row = start.row, col = start.col, wildCardLoc = -1;
    vector<int> changedIndexes;
    char letter;

    char boardTile;
    if (dir == 'V') {
        dRow = 1;
        dCol = 0;
    } else {
        dRow = 0;
        dCol = 1;
    }

    vector<int> checkedIndexes;

    bool letterFound, blankFound;
    // Check if the player has all the letters needed
    for (int i = 0; i < word.length(); i++) {
        cout << "Checking for letter " << word[i] << endl;
        letterFound = false;
        for (int j = 0; j < 7; j++) {
            if(find(checkedIndexes.begin(), checkedIndexes.end(), j) != checkedIndexes.end()) {
                cout << "Hand index " << hand[j] << " has already been registered\n";
            } else {
                if (hand[j] == word[i]) {
                    cout << "Found " << word[i] << " in hand\n";
                    checkedIndexes.push_back(j);
                    letterFound = true;
                    cout << letterFound << endl;
                    break;
                }
            }
        }
        if (!letterFound) {
            cout << "Checking if " << word[i] << " is associated with a blank\n";
            blankFound = false;
            // Check if the player has an unused ~
            for (int k = 0; k < 7; k++) {
                if(find(checkedIndexes.begin(), checkedIndexes.end(), k) != checkedIndexes.end()) {
                    cout << "Hand index " << hand[k] << " has already been registered\n";
                } else {
                    if (hand[k] == '~') {
                        cout << "Found " << word[i] << " in hand as a blank\n";
                        checkedIndexes.push_back(k);
                        blankFound = true;
                        break;
                    }
                }
            }
            if (!blankFound) {
                cout << "No blank was found for " << word[i] << endl;
                return false;
            }
        }
    }

   

    vector<char> existingLetters;
    for(int i = 0; i < word.length(); i++){
        existingLetters.push_back(g->gBoard(row, col));

        row += dRow;
        col += dCol;
    }

    for (int i = 0; i < existingLetters.size(); i++) {
        cout << "BBBB " << existingLetters[i] << endl;
    }

    cout << checkedIndexes.size() << endl;
    for (int i = 0; i < checkedIndexes.size(); i++) {
        cout << "Checking letter " << checkedIndexes[i] << endl;
        int index = checkedIndexes[i];
        letter = hand[checkedIndexes[i]];
        if(find(existingLetters.begin(), existingLetters.end(), letter) != existingLetters.end()) {
            cout << "The letter " << letter << " already is on the board " << endl;
        } else {
            cout << "Replacing letter " << hand[index];
            hand[index] = g->drawBag();
            cout << " with " << hand[index] << endl;
        }
    }
    

    return true;

    for(int i = 0; i < word.length(); i++){
        if(g->gBoard(row, col) != empty){
            cout << "Letter " << word[i] << "already placed" << endl;
            i++;
        }
        for(int j = 0; j < 7; j++){
            found = false;
            if(hand[j] == word[i]){
                changedIndexes.push_back(j);
                found = true;
                break;
            }
            if(hand[j] == '~') wildCardLoc = j;
        }
        if(!found && wildCardLoc != -1){
            changedIndexes.push_back(wildCardLoc);
            wildCardLoc = -1;
            cout << "Using wildcard tile for letter " << word[i] << endl;
        }
        else if(!found){
            return false;
        }
        row += dRow;
        col += dCol;
    }
    for(int i = 0; i < changedIndexes.size(); ++i){
        cout << "Replacing letter " << hand[changedIndexes[i]];
        hand[changedIndexes[i]] = g-> drawBag();
        cout << " with " << hand[changedIndexes[i]] << endl;
    }
    return true;
}


void Player::printHand() {
    sort(hand.begin(), hand.end());

    cout << name << "'s HAND: ";
    for (int i = 0; i < 7; i++) cout << hand[i] << " ";
    cout << endl;
    for(int i = 0; i<10; i++) cout << " ";
    for (int i = 0; i < 7; i++) if (hand[i] != '0') cout << getValue(hand[i]) << " ";
    cout << endl;
}