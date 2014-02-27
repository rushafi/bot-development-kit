/* 
 * File:   Player.h
 * Author: rushafi
 *
 * Created on November 15, 2011, 2:43 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "config.h"

using namespace std;

class Player {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();

    virtual int getNextMove(vector<string> surroundings);
private:

};

#endif	/* PLAYER_H */