/* 
 * File:   GameEnv.cpp
 * Author: rushafi
 * 
 * Created on November 14, 2011, 8:52 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include "GameEnv.h"
#include "Player.h"
#include "config.h"
// #include "BotHeader.h"
#include "SnakeBot.h"

using namespace std;

GameEnv::GameEnv() {

    arena = new Arena();

    fd3 = fdopen(3, "w");
    fd4 = fdopen(4, "r");
    fd5 = fdopen(5, "w");
    fd6 = fdopen(6, "r");

    // Player 1 init

    fprintf(fd3, "%d %d\n", arena->getDimension().first, arena->getDimension().second);
    fflush(fd3);

    fprintf(fd3, "%d %d\n", arena->getCollectiblesCount().first, arena->getCollectiblesCount().second);
    fflush(fd3);

    fprintf(fd3, "%d %d\n", arena->getPlayer1StartPos().first, arena->getPlayer1StartPos().second);
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getPlayer1StartDirection());
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getPlayer1Length());
    fflush(fd3);

    fprintf(fd3, "%d %d\n", arena->getPlayer2StartPos().first, arena->getPlayer2StartPos().second);
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getPlayer2StartDirection());
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getMaxTurn());
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getVisRange());
    fflush(fd3);

    // Player 2 init

    fprintf(fd5, "%d %d\n", arena->getDimension().first, arena->getDimension().second);
    fflush(fd5);

    fprintf(fd5, "%d %d\n", arena->getCollectiblesCount().first, arena->getCollectiblesCount().second);
    fflush(fd5);

    fprintf(fd5, "%d %d\n", arena->getPlayer2StartPos().first, arena->getPlayer2StartPos().second);
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getPlayer2StartDirection());
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getPlayer2Length());
    fflush(fd5);

    fprintf(fd5, "%d %d\n", arena->getPlayer1StartPos().first, arena->getPlayer1StartPos().second);
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getPlayer1StartDirection());
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getMaxTurn());
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getVisRange());
    fflush(fd5);

    // Player init done

    // Player *player1 = new P1(arena->getDimension(),
    //         arena->getCollectiblesCount(), arena->getPlayer1StartPos(),
    //         arena->getPlayer1StartDirection(), arena->getPlayer1Length(),
    //         arena->getPlayer2StartPos(), arena->getPlayer2StartDirection(),
    //         arena->getMaxTurn(), arena->getVisRange());

    // Player *player2 = new P2(arena->getDimension(),
    //         arena->getCollectiblesCount(), arena->getPlayer2StartPos(),
    //         arena->getPlayer2StartDirection(), arena->getPlayer2Length(),
    //         arena->getPlayer1StartPos(), arena->getPlayer1StartDirection(),
    //         arena->getMaxTurn(), arena->getVisRange());

    // players.push_back(player1);
    // players.push_back(player2);

    // _pii startPos, int length, int direction
    
    bot1 = new SnakeBot(arena->getPlayer1StartPos(), arena->getPlayer1Length(), 
            arena->getPlayer1StartDirection());;

    bot2 = new SnakeBot(arena->getPlayer2StartPos(), arena->getPlayer2Length(),
            arena->getPlayer2StartDirection());;

    isP1Alive = true;
    isP2Alive = true;

    remPosCollectibles = arena->getCollectiblesCount().first;
    remNegCollectibles = arena->getCollectiblesCount().second;

	p1FinalStatus = NO_HIT;
	p2FinalStatus = NO_HIT;
    gameStatus = STATUS_NOT_STARTED;

    turnsRem = arena->getMaxTurn();
}

GameEnv::GameEnv(const char *arenaDescritor, const char *gameDescriptor) {

    gameDescritorFp = fopen(gameDescriptor, "w");
    arena = new Arena(arenaDescritor);

    fd3 = fdopen(3, "w");
    fd4 = fdopen(4, "r");
    fd5 = fdopen(5, "w");
    fd6 = fdopen(6, "r");

    // Player 1 init

    fprintf(fd3, "%d %d\n", arena->getDimension().first, arena->getDimension().second);
    fflush(fd3);

    fprintf(fd3, "%d %d\n", arena->getCollectiblesCount().first, arena->getCollectiblesCount().second);
    fflush(fd3);

    fprintf(fd3, "%d %d\n", arena->getPlayer1StartPos().first, arena->getPlayer1StartPos().second);
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getPlayer1StartDirection());
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getPlayer1Length());
    fflush(fd3);

    fprintf(fd3, "%d %d\n", arena->getPlayer2StartPos().first, arena->getPlayer2StartPos().second);
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getPlayer2StartDirection());
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getMaxTurn());
    fflush(fd3);

    fprintf(fd3, "%d\n", arena->getVisRange());
    fflush(fd3);

    // Player 2 init

    fprintf(fd5, "%d %d\n", arena->getDimension().first, arena->getDimension().second);
    fflush(fd5);

    fprintf(fd5, "%d %d\n", arena->getCollectiblesCount().first, arena->getCollectiblesCount().second);
    fflush(fd5);

    fprintf(fd5, "%d %d\n", arena->getPlayer2StartPos().first, arena->getPlayer2StartPos().second);
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getPlayer2StartDirection());
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getPlayer2Length());
    fflush(fd5);

    fprintf(fd5, "%d %d\n", arena->getPlayer1StartPos().first, arena->getPlayer1StartPos().second);
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getPlayer1StartDirection());
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getMaxTurn());
    fflush(fd5);

    fprintf(fd5, "%d\n", arena->getVisRange());
    fflush(fd5);

    // Player init done
    
    // Player *player1 = new P1(arena->getDimension(), 
    //         arena->getCollectiblesCount(), arena->getPlayer1StartPos(),
    //         arena->getPlayer1StartDirection(), arena->getPlayer1Length(),
    //         arena->getPlayer2StartPos(), arena->getPlayer2StartDirection(),
    //         arena->getMaxTurn(), arena->getVisRange());

    // Player *player2 = new P2(arena->getDimension(),
    //         arena->getCollectiblesCount(), arena->getPlayer2StartPos(),
    //         arena->getPlayer2StartDirection(), arena->getPlayer2Length(),
    //         arena->getPlayer1StartPos(), arena->getPlayer1StartDirection(),
    //         arena->getMaxTurn(), arena->getVisRange());

    // players.push_back(player1);
    // players.push_back(player2);

    // _pii startPos, int length, int direction

    bot1 = new SnakeBot(arena->getPlayer1StartPos(), arena->getPlayer1Length(),
            arena->getPlayer1StartDirection());;

    bot2 = new SnakeBot(arena->getPlayer2StartPos(), arena->getPlayer2Length(),
            arena->getPlayer2StartDirection());;

    isP1Alive = true;
    isP2Alive = true;

    remPosCollectibles = arena->getCollectiblesCount().first;
    remNegCollectibles = arena->getCollectiblesCount().second;

	p1FinalStatus = NO_HIT;
	p2FinalStatus = NO_HIT;
    gameStatus = STATUS_NOT_STARTED;

    turnsRem = arena->getMaxTurn();

    arena->printArenaDescription(gameDescritorFp);

    fclose(gameDescritorFp);

    gameDescritorFp = fopen(gameDescriptor, "a");
}

GameEnv::GameEnv(const GameEnv& orig) {
}

GameEnv::~GameEnv() {
    delete arena;
    // Player* &player1 = players[0];
    // Player* &player2 = players[1];
    // players.clear();
    // delete player1;
    // delete player2;
    
    delete bot1;
    delete bot2;

    fclose(fd3);
    fclose(fd4);
    fclose(fd5);
    fclose(fd6);

    fclose(gameDescritorFp);
}

void GameEnv::start() {

    gameStatus = STATUS_ONGOING;

    do {

        // arena->drawArena();
        turnsRem--; // another turn finished

        pair<_pii,_pii> bot1Bound = bot1->getBound();
        pair<_pii,_pii> bot2Bound = bot2->getBound();

        vector<string> p1Surroundings = arena->getDescription(bot1Bound, 0,
                bot1->getHeadPos(), bot2->getHeadPos(), bot1->getSnakeBody());
        vector<string> p2Surroundings = arena->getDescription(bot2Bound, 1,
                bot2->getHeadPos(), bot1->getHeadPos(), bot2->getSnakeBody());

				time_t p1Start, p1End, p2Start, p2End, p1Diff, p2Diff;

                // writing number of lines to take as surrourndings input for player 1

                fprintf(fd3, "%d\n", (int)p1Surroundings.size());
                fflush(fd3);

                // writing surroundings

                for(int i1 = 0; i1 < p1Surroundings.size(); i1++) {

                    fprintf(fd3, "%s\n", p1Surroundings[i1].c_str());
                    fflush(fd3);
                }

                // end of writing surroundings for player 1

                p1Start = time(NULL);

                // int p1direction = players[0]->getNextMove(p1Surroundings);

                int p1direction;

                fscanf(fd4, "%d", &p1direction);

                // printf("Received P1 direction: %d\n", p1direction);

                p1End = time(NULL);

                p1Diff = difftime(p1Start, p1End);
                bot1->updateTime(p1Diff);

                // writing number of lines to take as surrourndings input for player 2

                fprintf(fd5, "%d\n", (int)p2Surroundings.size());
                fflush(fd5);

                // writing surroundings

                for(int i1 = 0; i1 < p2Surroundings.size(); i1++) {

                    fprintf(fd5, "%s\n", p2Surroundings[i1].c_str());
                    fflush(fd5);
                }

                // end of writing surroundings for player 2
				
				p2Start = time(NULL);

				// int p2direction = players[1]->getNextMove(p2Surroundings);

                int p2direction;

                fscanf(fd6, "%d", &p2direction);

                // printf("Received P2 direction: %d\n", p2direction);

				p2End = time(NULL);
				
				p2Diff = difftime(p2Start, p2End);
				bot2->updateTime(p2Diff);
				
        /* Prevent player from going exactly opposite of its direction when
         * length is greater than 1. It is because when length is greater than 1
         *  going to the opposite direction will surely crush it.
         * In this case the bot will retain its previous direction
         */

        if((bot1->getLength() > 1) &&
                (bot1->getDirection() == ((p1direction + 2) % 4))) {
            p1direction = bot1->getDirection();
        }

        if((bot2->getLength() > 1) &&
                (bot2->getDirection() == ((p2direction + 2) % 4))) {
            p2direction = bot2->getDirection();
        }

        fprintf(gameDescritorFp, "0 %d %d\n", p1direction, p2direction);

        _pii player1move = bot1->pushHead(p1direction);
        _pii player2move = bot2->pushHead(p2direction);

        if(player1move == player2move) {
            // head on collision, both dead
            bot1->pushTail();
            bot2->pushTail();

            isP1Alive = false;
            isP2Alive = false;

            // head is destroyed for both snake, length reduced by one
            
            p1FinalLength = bot1->getLength() - 1;
            p2FinalLength = bot2->getLength() - 1;

			p1FinalStatus = OPP_HEAD_HIT;
			p2FinalStatus = OPP_HEAD_HIT;
            gameStatus = getWinningStatus(p1FinalLength, p2FinalLength);
        }
        else {

            // Push tail of snake 1

            if(arena->getArenaDescriptor(bot1->getHeadPos()) == 'C') {
                // Positive collectible, snake will grow, no pop
                // reduce postivle collectibles by one
                remPosCollectibles--;
            }
            else if(arena->getArenaDescriptor(bot1->getHeadPos()) == 'N') {
                // Negative collectible, snake will shrink, double pop
                // reduce negative collectibles by one
                remNegCollectibles--;

                arena->updateArenaDescriptor(bot1->getTailPos(), 'E');
                bot1->pushTail();

                arena->updateArenaDescriptor(bot1->getTailPos(), 'E');
                bot1->pushTail();

                // Check whether length falls to zero, if then die
                if(bot1->getLength() == 0) {
					isP1Alive = false;
					p1FinalStatus = LENGTH_ZERO;
				}
            }
            else {
                // Snake will move one step
                arena->updateArenaDescriptor(bot1->getTailPos(), 'E');
                bot1->pushTail();
            }
            
            // Push tail of snake 2

            if(arena->getArenaDescriptor(bot2->getHeadPos()) == 'C') {
                // Positive collectible, snake will grow, no pop
                // reduce postivle collectibles by one
                remPosCollectibles--;
            }
            else if(arena->getArenaDescriptor(bot2->getHeadPos()) == 'N') {
                // Negative collectible, snake will shrink, double pop
                // reduce negative collectibles by one
                remNegCollectibles--;

                arena->updateArenaDescriptor(bot2->getTailPos(), 'E');
                bot2->pushTail();

                arena->updateArenaDescriptor(bot2->getTailPos(), 'E');
                bot2->pushTail();

                // Check whether length falls to zero, if then die
                if(bot2->getLength() == 0) {
					isP2Alive = false;
					p2FinalStatus = LENGTH_ZERO;
				}
            }
            else {
                // Snake will move one step
                arena->updateArenaDescriptor(bot2->getTailPos(), 'E');
                bot2->pushTail();
            }

            // Check whether the snakes have collided with anything
            // If collides game is over

            if(arena->getArenaDescriptor(bot1->getHeadPos()) == 'B') {
                // Did hit a block, snake is dead
                // need to reduce length by one
                p1FinalLength = bot1->getLength() - 1;
                isP1Alive = false;
				p1FinalStatus = WALL_HIT;
            }
            else if(arena->getArenaDescriptor(bot1->getHeadPos()) == 'O') {
                // Did hit opponents body, snake is dead
                // need to reduce length by one
                p1FinalLength = bot1->getLength() - 1;
                isP1Alive = false;
				p1FinalStatus = OPP_HIT;
            }
            else if(arena->getArenaDescriptor(bot1->getHeadPos()) == 'S') {
                // Did hit own body, snake is dead
                // need to reduce length by one
                p1FinalLength = bot1->getLength() - 1;
                isP1Alive = false;
				p1FinalStatus = SELF_HIT;
            }
            else {
                // No collision occured
                // Update headPos with snake signature
                arena->updateArenaDescriptor(bot1->getHeadPos(), 'S');
                p1FinalLength = bot1->getLength();
            }

            if(arena->getArenaDescriptor(bot2->getHeadPos()) == 'B') {
                // Did hit a block, snake is dead
                // need to reduce length by one
                p2FinalLength = bot2->getLength() - 1;
                isP2Alive = false;
				p2FinalStatus = WALL_HIT;
            }
            else if(arena->getArenaDescriptor(bot2->getHeadPos()) == 'O') {
                // Did hit own body, snake is dead
                // need to reduce length by one
                p2FinalLength = bot2->getLength() - 1;
                isP2Alive = false;
				p2FinalStatus = SELF_HIT;
            }
            else if(arena->getArenaDescriptor(bot2->getHeadPos()) == 'S') {
                // Did hit opponent body, snake is dead
                // need to reduce length by two
                p2FinalLength = bot2->getLength() - 1;
                isP2Alive = false;
				p2FinalStatus = OPP_HIT;
            }
            else {
                // No collision occured
                // Update headPos with snake signature
                arena->updateArenaDescriptor(bot2->getHeadPos(), 'O');
                p2FinalLength = bot2->getLength();
            }
        }

        if(!isP1Alive && !isP2Alive) {
            
            // both are dead, winning condition is to achieve by length
            gameStatus = getWinningStatus(bot1->getLength(), bot2->getLength());
        }
        else {
            
            if(!isP1Alive) gameStatus = STATUS_PLAYER2_WON;
            else if(!isP2Alive) gameStatus = STATUS_PLAYER1_WON;
            else {
                // no one is dead, game will continue
            }
        }

        if(gameStatus == STATUS_ONGOING) {
            if(isTerminationConditionAchieved()) {
                gameStatus = getWinningStatus(bot1->getLength(),
                        bot2->getLength());
            }
        }
    }
    while(gameStatus == STATUS_ONGOING);

    // Game is finished
    // gameStatus holds game result
    // p1FinalLength holds final length of Player1
    // p2FinalLength holds final length of Player2

    // arena->drawArena();

    // need to send a signal to shut down the bots

    // fprintf(fd3, "%d\n", -1);
    // fprintf(fd5, "%d\n", -1);

    // printGameResult();

    fprintf(gameDescritorFp, "1 %d %d\n", p1FinalLength, p2FinalLength);
    fprintf(gameDescritorFp, "%d %d %d\n", gameStatus, p1FinalStatus, p2FinalStatus);
}

bool GameEnv::isTerminationConditionAchieved() {

    /* Game will terminate if max available turns end or
     * number of positive collectibles falls to zero
     */

    if(remPosCollectibles == 0) return true;
    else if(turnsRem == 0) return true;
    else return false;
}

int GameEnv::getWinningStatus(int p1Length, int p2Length) {

    if(p1Length > p2Length) return STATUS_PLAYER1_WON;
    else if(p2Length > p1Length) return STATUS_PLAYER2_WON;
    else return STATUS_GAME_TIED;
}

void GameEnv::printPlayerStatus(int n) {
		fprintf(gameDescritorFp, "Final Status: ");
		switch (n) {
				case 0:
						fprintf(gameDescritorFp, "Intact\n");
						break;
				case 1:
						fprintf(gameDescritorFp, "Hit Wall\n");
						break;
				case 2:
						fprintf(gameDescritorFp, "Hit Self\n");
						break;
				case 3:
						fprintf(gameDescritorFp, "Hit Opponent\n");
						break;
				case 4:
						fprintf(gameDescritorFp, "Hit Opponent Head\n");
						break;
				case 5:
						fprintf(gameDescritorFp, "Dived to the VOID\n");
						break;
				default:
						fprintf(gameDescritorFp, "Undefined Case\n");
		}
}

void GameEnv::printGameResult() {
	fprintf(gameDescritorFp, "\nResult: ");

    if(gameStatus == STATUS_GAME_TIED)          fprintf(gameDescritorFp, "Game Tied\n");
    else if(gameStatus == STATUS_PLAYER1_WON)   fprintf(gameDescritorFp, "Player 1 won\n");
    else if(gameStatus == STATUS_PLAYER2_WON)   fprintf(gameDescritorFp, "Player 2 won\n");
    else                                        fprintf(gameDescritorFp, "Game Status Unknown\n");

    fprintf(gameDescritorFp, "Remaining turns: %d\n", turnsRem);
	fprintf(gameDescritorFp, "\n");

	fprintf(gameDescritorFp, "P1 Stat\n");
	fprintf(gameDescritorFp, "Final Length: %d\n", p1FinalLength);
	// fprintf(gameDescritorFp, "Avg time per move: %.6lf\n", bot1->getAverageTime());
	// fprintf(gameDescritorFp, "Max time in any move: %.6lf\n", bot1->getMaxTime());
	// fprintf(gameDescritorFp, "Min time in any move: %.6lf\n", bot1->getMinTime());
	printPlayerStatus(p1FinalStatus);
	fprintf(gameDescritorFp, "\n");
	
	fprintf(gameDescritorFp, "P2 Stat\n");
	fprintf(gameDescritorFp, "Final Length: %d\n", p2FinalLength);
	// fprintf(gameDescritorFp, "Avg time per move: %.6lf\n", bot2->getAverageTime());
	// fprintf(gameDescritorFp, "Max time in any move: %.6lf\n", bot2->getMaxTime());
	// fprintf(gameDescritorFp, "Min time in any move: %.6lf\n", bot2->getMinTime());
	printPlayerStatus(p2FinalStatus);
	fprintf(gameDescritorFp, "\n");
		
    fprintf(gameDescritorFp, "GAME ENDS HERE\n");
}

void GameEnv::printMove(int playerSrl, int move) {
    if(playerSrl == 0)      fprintf(gameDescritorFp, "Player 1: ");
    else if(playerSrl == 1) fprintf(gameDescritorFp, "Player 2: ");

    if(move == LEFT)        fprintf(gameDescritorFp, "Left\n");
    else if(move == RIGHT)  fprintf(gameDescritorFp, "Right\n");
    else if(move == UP)     fprintf(gameDescritorFp, "Up\n");
    else if(move == DOWN)   fprintf(gameDescritorFp, "Down\n");
}