/* 
 * File:   Player.cpp
 * Author: rushafi
 * 
 * Created on November 15, 2011, 2:43 AM
 */

#include "Player.h"

using namespace std;

Player::Player() {
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

int Player::getNextMove(vector<string> surroundings) {

    srand(time(NULL));
    int nextMove = rand()%4;
    return nextMove;
}