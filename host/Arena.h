/* 
 * File:   Arena.h
 * Author: rushafi
 *
 * Created on November 14, 2011, 8:52 AM
 */

#ifndef ARENA_H
#define	ARENA_H

#include "config.h"

using namespace std;

class Arena {
public:
    Arena();
    Arena(const char *arenaFile);
    Arena(const Arena& orig);
    virtual ~Arena();

    void drawArena();
    void printArenaDescription(FILE *fp);
    char getArenaDescriptor(int x, int y);
    char getArenaDescriptor(_pii pos);
    void updateArenaDescriptor(int x, int y, char ch);
    void updateArenaDescriptor(_pii pos, char ch);

    _pii getDimension();
    int getMaxTurn();
    _pii getCollectiblesCount();
    int getVisRange();
    _pii getPlayer1StartPos();
    _pii getPlayer2StartPos();
    int getPlayer1Length();
    int getPlayer2Length();
    int getPlayer1StartDirection();
    int getPlayer2StartDirection();

    vector<string> getDescription(pair<_pii,_pii> bound, int srl,
    _pii selfHead, _pii oppHead, vector<_pii> body);

private:
    int width, height;
    int maxTurn;
    int posCollectibles, negCollectibles;
    int visRange;
    _pii player1StartPosition, player2StartPosition;
    int player1StartDirection, player2StartDirection;
    int player1Length, player2Length;
    vector<string> gameMap;

    void generateCollectibles();
};

#endif	/* ARENA_H */