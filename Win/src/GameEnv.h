/* 
 * File:   GameEnv.h
 * Author: rushafi
 *
 * Created on November 14, 2011, 8:52 AM
 */

#ifndef GAMEENV_H
#define	GAMEENV_H

#include "Arena.h"
#include "Player.h"
#include "SnakeBot.h"

class GameEnv {

public:

    GameEnv();
    GameEnv(const char *arenaDescritor, const char *gameDescriptor);
    GameEnv(const GameEnv& orig);
    virtual ~GameEnv();

    void start();

private:

    FILE *gameDescritorFp;

    Arena *arena;
    vector<Player *> players;
    SnakeBot *bot1, *bot2;
    int remPosCollectibles, remNegCollectibles;
    int turnsRem;

    // Game Variables
    bool isP1Alive;
    bool isP2Alive;

    int p1FinalLength;
    int p2FinalLength;

		int p1FinalStatus;
		int p2FinalStatus;
    int gameStatus;

    bool isTerminationConditionAchieved();
    int getWinningStatus(int p1Length, int p2Length);
    void printGameResult();
    void printMove(int playerSrl, int move);
		void printfPlayerStatus(int n);
};

#endif	/* GAMEENV_H */

