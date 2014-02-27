/* 
 * File:   config.h
 * Author: rushafi
 *
 * Created on November 14, 2011, 8:56 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int,int> _pii;

typedef enum {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
} directions;

typedef enum {
    nofood = 0,
    growfood,
    shrinkfood
} foodtype;

typedef enum {
    STATUS_NOT_STARTED = 0,
    STATUS_ONGOING,
    STATUS_GAME_TIED,
    STATUS_PLAYER1_WON,
    STATUS_PLAYER2_WON
} gameStatus;

typedef enum {
		NO_HIT = 0,
		WALL_HIT,
		SELF_HIT,
		OPP_HIT,
		OPP_HEAD_HIT,
		LENGTH_ZERO
} playerStatus;

#endif	/* CONFIG_H */

