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
    for(int i = 0; i < word.length(); i++){
        if(((g ->gBoard(start.row, start.col+i) == empty) && dir == 'H') || ((g -> gBoard(start.row + i, start.col) == empty) && dir == 'V')){
            for(int j = 0; j < 7; j++){
                if(hand[j] == word[i]){
                    hand[i] = g->drawBag();
                    found = true;
                    break;
                }
            }
            if(!found){
                for(int k = 0; k < 7; k++){
                    if(hand[k] == '~'){
                        hand[k] = g->drawBag();
                        found = true;
                        break;
                    }
                }
            }
            if(!found){
                cout << word[i] << " not found" << endl;
                return false;
            }
        }        
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