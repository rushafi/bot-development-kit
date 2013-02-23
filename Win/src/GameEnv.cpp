/* 
 * File:   GameEnv.cpp
 * Author: rushafi
 * 
 * Created on November 14, 2011, 8:52 AM
 */

#include "GameEnv.h"
#include "Player.h"
#include "config.h"
#include "BotHeader.h"
#include "SnakeBot.h"

using namespace std;

GameEnv::GameEnv() {

    arena = new Arena();

    Player *player1 = new P1(arena->getDimension(),
            arena->getCollectiblesCount(), arena->getPlayer1StartPos(),
            arena->getPlayer1StartDirection(), arena->getPlayer1Length(),
            arena->getPlayer2StartPos(), arena->getPlayer2StartDirection(),
            arena->getMaxTurn(), arena->getVisRange());

    Player *player2 = new P2(arena->getDimension(),
            arena->getCollectiblesCount(), arena->getPlayer2StartPos(),
            arena->getPlayer2StartDirection(), arena->getPlayer2Length(),
            arena->getPlayer1StartPos(), arena->getPlayer1StartDirection(),
            arena->getMaxTurn(), arena->getVisRange());

    players.push_back(player1);
    players.push_back(player2);

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
    
    Player *player1 = new P1(arena->getDimension(), 
            arena->getCollectiblesCount(), arena->getPlayer1StartPos(),
            arena->getPlayer1StartDirection(), arena->getPlayer1Length(),
            arena->getPlayer2StartPos(), arena->getPlayer2StartDirection(),
            arena->getMaxTurn(), arena->getVisRange());

    Player *player2 = new P2(arena->getDimension(),
            arena->getCollectiblesCount(), arena->getPlayer2StartPos(),
            arena->getPlayer2StartDirection(), arena->getPlayer2Length(),
            arena->getPlayer1StartPos(), arena->getPlayer1StartDirection(),
            arena->getMaxTurn(), arena->getVisRange());

    players.push_back(player1);
    players.push_back(player2);

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
    Player* &player1 = players[0];
    Player* &player2 = players[1];
    players.clear();
    delete player1;
    delete player2;
    
    delete bot1;
    delete bot2;
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
				
				p1Start = time(NULL);
				int p1direction = players[0]->getNextMove(p1Surroundings);
        p1End = time(NULL);

				p1Diff = difftime(p1Start, p1End);
				bot1->updateTime(p1Diff);
				
				p2Start = time(NULL);
				int p2direction = players[1]->getNextMove(p2Surroundings);
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
    printGameResult();
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

void GameEnv::printfPlayerStatus(int n) {
		printf("Final Status: ");
		switch (n) {
				case 0:
						printf("Intact\n");
						break;
				case 1:
						printf("Hit Wall\n");
						break;
				case 2:
						printf("Hit Self\n");
						break;
				case 3:
						printf("Hit Opponent\n");
						break;
				case 4:
						printf("Hit Opponent Head\n");
						break;
				case 5:
						printf("Dived to the VOID\n");
						break;
				default:
						printf("Undefined Case\n");
		}
}

void GameEnv::printGameResult() {
		printf("\nResult: ");
    if(gameStatus == STATUS_GAME_TIED) printf("Game Tied\n");
    else if(gameStatus == STATUS_PLAYER1_WON) printf("Player 1 won\n");
    else if(gameStatus == STATUS_PLAYER2_WON) printf("Player 2 won\n");
    else printf("Game Status Unknown\n");

    printf("Remaining turns: %d\n", turnsRem);
		printf("\n");

		printf("P1 Stat\n");
		printf("Final Length: %d\n", p1FinalLength);
		printf("Avg time per move: %.6lf\n", bot1->getAverageTime());
		printf("Max time in any move: %.6lf\n", bot1->getMaxTime());
		printf("Min time in any move: %.6lf\n", bot1->getMinTime());
		printfPlayerStatus(p1FinalStatus);
		printf("\n");
		
		printf("P2 Stat\n");
		printf("Final Length: %d\n", p2FinalLength);
		printf("Avg time per move: %.6lf\n", bot2->getAverageTime());
		printf("Max time in any move: %.6lf\n", bot2->getMaxTime());
		printf("Min time in any move: %.6lf\n", bot2->getMinTime());
		printfPlayerStatus(p2FinalStatus);
		printf("\n");
		
    printf("GAME ENDS HERE\n");
}

void GameEnv::printMove(int playerSrl, int move) {
    if(playerSrl == 0) printf("Player 1: ");
    else if(playerSrl == 1) printf("Player 2: ");
    if(move == LEFT) printf("Left\n");
    else if(move == RIGHT) printf("Right\n");
    else if(move == UP) printf("Up\n");
    else if(move == DOWN) printf("Down\n");
}