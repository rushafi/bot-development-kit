/* 
 * File:   Arena.cpp
 * Author: rushafi
 * 
 * Created on November 14, 2011, 8:52 AM
 */

#include "Arena.h"

using namespace std;

Arena::Arena() {
    width = 10;
    height = 10;
    maxTurn = 50;

    posCollectibles = (int)((double)width * (double)height * 0.05);
    negCollectibles = (int)((double)width * (double)height * 0.05);
    visRange = width / 5;

    player1StartPosition = make_pair(height / 10, width / 10);
    player2StartPosition = make_pair(height - (height / 10) - 1, width - (width / 10) - 1);

    player1StartDirection = RIGHT;
    player2StartDirection = LEFT;

    player1Length = width / 5;
    player2Length = width / 5;
    
    // updating boundary

    for(int i = 0; i < height; i++) {
        string mapLine;
        for(int j = 0; j < width; j++) {
            if(i == 0 || i == height-1) {
                mapLine += "B";
            }
            else {
                if(j == 0 || j == width-1) {
                    mapLine += "B";
                }
                else {
                    mapLine += "E";
                }
            }
        }
        gameMap.push_back(mapLine);
    }

    // updating player starting points

    gameMap[player1StartPosition.first][player1StartPosition.second] = 'S';
    gameMap[player2StartPosition.first][player2StartPosition.second] = 'O';
}

Arena::Arena(const char *arenaFile) {

    gameMap.resize(0);

    FILE *fp = fopen(arenaFile, "r");
    fscanf(fp,"%d %d %d", &width, &height, &maxTurn);
    fscanf(fp,"%d %d %d", &posCollectibles, &negCollectibles, &visRange);
    fscanf(fp,"%d %d %d %d", &player1StartPosition.first, &player1StartPosition.second, &player1Length, &player1StartDirection);
    fscanf(fp,"%d %d %d %d", &player2StartPosition.first, &player2StartPosition.second, &player2Length, &player2StartDirection);

    for(int i = 0; i < height; i++) {
        char tempLine[width+1];
        fscanf(fp,"%s", tempLine);
        string tempStrLine = tempLine;
        gameMap.push_back(tempStrLine);
    }

    _pii cPos = player1StartPosition;

    for (int length = 0; length < player1Length; length++) {
        gameMap[cPos.second][cPos.first] = 'S';

        switch (player1StartDirection) {
            case LEFT:
                cPos.first--;
                break;
            case RIGHT:
                cPos.first++;
                break;
            case UP:
                cPos.second--;
                break;
            case DOWN:
                cPos.second++;
                break;
            default:
                ;
        }
    }

    cPos = player2StartPosition;

    for (int length = 0; length < player2Length; length++) {
        gameMap[cPos.second][cPos.first] = 'O';

        switch (player2StartDirection) {
            case LEFT:
                cPos.first--;
                break;
            case RIGHT:
                cPos.first++;
                break;
            case UP:
                cPos.second--;
                break;
            case DOWN:
                cPos.second++;
                break;
            default:
                ;
        }
    }

    fclose(fp);

    generateCollectibles();
}

Arena::Arena(const Arena& orig) {
}

Arena::~Arena() {
}

void Arena::drawArena() {

//    cout << "Printing Arena" << endl;
//    cout << "Dimension: " << height << " " << width << endl;

    char toBePrinted;

    for(int i = 0; i < height; i++) {
        for(int j  = 0; j < width; j++) {
            if(gameMap[i][j] == 'B') {
                if((i==0 && j==0) || (i==0 && j==width-1) || (i==height-1 && j==0) || (i==height-1 && j==width-1))
                    toBePrinted = '+';
                else if(i==0 || i==height-1) toBePrinted = '-';
                else if(j==0 || j==width-1) toBePrinted = '|';
                else toBePrinted = '+';
            }
            else if(gameMap[i][j] == 'E') {
                toBePrinted = ' ';
            }
            else if(gameMap[i][j] == 'S') {
                toBePrinted = '.';
            }
            else if(gameMap[i][j] == 'O') {
                toBePrinted = '.';
            }
            else if(gameMap[i][j] == 'C') {
                toBePrinted = '*';
            }
            else if(gameMap[i][j] == 'N') {
                toBePrinted = '#';
            }
//            printf("%3c", gameMap[i][j]);
            printf("%3c", toBePrinted);
        }
        printf("\n");
    }
    printf("\n");
}

void Arena::printArenaDescription(FILE *fp) {

    fprintf(fp, "%d %d %d\n", width, height, maxTurn);
    fprintf(fp, "%d %d %d\n", posCollectibles, negCollectibles, visRange);
    fprintf(fp, "%d %d %d %d\n", player1StartPosition.first,
            player1StartPosition.second, player1Length, player1StartDirection);
    fprintf(fp, "%d %d %d %d\n", player2StartPosition.first,
            player2StartPosition.second, player2Length, player2StartDirection);
    
    for(int i = 0; i < gameMap.size(); i++) {
        for(int j = 0; j < gameMap[i].length(); j++) {
            if(gameMap[i][j] == 'S' || gameMap[i][j] == 'O') fprintf(fp, "E");
            else fprintf(fp, "%c",gameMap[i][j]);
        }
        fprintf(fp, "\n");
    }
}

void Arena::generateCollectibles() {

    srand(time(NULL));

    for(int i = 0; i < posCollectibles; i++) {

        _pii cPos = make_pair(rand()%width, rand()%height);

        while(gameMap[cPos.second][cPos.first] == 'B'
            || gameMap[cPos.second][cPos.first] == 'S'
            || gameMap[cPos.second][cPos.first] == 'O'
            || gameMap[cPos.second][cPos.first] == 'C'
            || gameMap[cPos.second][cPos.first] == 'N') {

            cPos = make_pair(rand()%width, rand()%height);
        }

        gameMap[cPos.second][cPos.first] = 'C';
    }

        for(int i = 0; i < negCollectibles; i++) {

        _pii cPos = make_pair(rand()%width, rand()%height);

        while(gameMap[cPos.second][cPos.first] == 'B'
            || gameMap[cPos.second][cPos.first] == 'S'
            || gameMap[cPos.second][cPos.first] == 'O'
            || gameMap[cPos.second][cPos.first] == 'C'
            || gameMap[cPos.second][cPos.first] == 'N') {

            cPos = make_pair(rand()%width, rand()%height);
        }

        gameMap[cPos.second][cPos.first] = 'N';
    }
}

char Arena::getArenaDescriptor(int x, int y) {
    return gameMap[y][x];
}

char Arena::getArenaDescriptor(_pii pos) {
    return gameMap[pos.second][pos.first];
}

void Arena::updateArenaDescriptor(int x, int y, char ch) {
    gameMap[y][x] = ch;
}

void Arena::updateArenaDescriptor(_pii pos, char ch) {
    gameMap[pos.second][pos.first] = ch;
}

_pii Arena::getDimension() {
    return make_pair(width, height);
}

int Arena::getMaxTurn() {
    return maxTurn;
}

_pii Arena::getCollectiblesCount() {
    return make_pair(posCollectibles, negCollectibles);
}

int Arena::getVisRange() {
    return visRange;
}

_pii Arena::getPlayer1StartPos() {
    return player1StartPosition;
}

_pii Arena::getPlayer2StartPos() {
    return player2StartPosition;
}

int Arena::getPlayer1Length() {
    return player1Length;
}

int Arena::getPlayer2Length() {
    return player2Length;
}

int Arena::getPlayer1StartDirection() {
    return player1StartDirection;
}

int Arena::getPlayer2StartDirection() {
    return player2StartDirection;
}

vector<string> Arena::getDescription(pair<_pii,_pii> bound, int srl,
    _pii selfHead, _pii oppHead, vector<_pii> body) {

    _pii adjustedTopLeft, adjustedBottomRight, adjustedArea;

    if(bound.first.first - visRange >= 0)
        adjustedTopLeft.first = bound.first.first - visRange;
    else adjustedTopLeft.first = 0;

    if(bound.first.second - visRange >= 0)
        adjustedTopLeft.second = bound.first.second - visRange;
    else adjustedTopLeft.second = 0;

    if(bound.second.first + visRange < width)
        adjustedBottomRight.first = bound.second.first + visRange;
    else adjustedBottomRight.first = width - 1;

    if(bound.second.second + visRange < height)
        adjustedBottomRight.second = bound.second.second + visRange;
    else adjustedBottomRight.second = height - 1;

    adjustedArea.first = adjustedBottomRight.first - adjustedTopLeft.first + 1;
    adjustedArea.second = adjustedBottomRight.second -
            adjustedTopLeft.second + 1;

    vector<string> ret, updatedRet;

    for(int i = adjustedTopLeft.second; i <= adjustedBottomRight.second; i++) {
        string tempLine = 
                gameMap[i].substr(adjustedTopLeft.first, adjustedArea.first);
        ret.push_back(tempLine);
    }

    for(int i = 0; i < ret.size(); i++) {
        string tempLine;
        for(int j = 0; j < ret[i].length(); j++) {
            tempLine += "W";
        }
        updatedRet.push_back(tempLine);
    }

    for(int i = 0; i < body.size(); i++) {
        _pii coord = body[i], translatedCoord;
        translatedCoord.first = coord.first - adjustedTopLeft.first;
        translatedCoord.second = coord.second - adjustedTopLeft.second;
        for(int j =  -visRange; j <= visRange; j++) {
            for(int k = -visRange; k <= visRange; k++) {
                if((translatedCoord.second+j >=0 &&
                        translatedCoord.second+j < ret.size()) &&
                        (translatedCoord.first+k >= 0 &&
                        translatedCoord.first+k < ret[0].length())) {
                    updatedRet[translatedCoord.second+j]
                            [translatedCoord.first+k] =
                            ret[translatedCoord.second+j]
                            [translatedCoord.first+k];
                }
            }
        }
    }

    for(int i = 0; i < ret.size(); i++) {
        for(int j = 0; j < ret[i].length(); j++) {
            if(srl && ret[i][j] == 'S') updatedRet[i][j] = 'O';
            else if(srl && ret[i][j] == 'O') updatedRet[i][j] = 'S';
        }
    }

    _pii transOppHead;
    transOppHead.first = oppHead.first - adjustedTopLeft.first;
    transOppHead.second = oppHead.second - adjustedTopLeft.second;

    updatedRet[selfHead.second-adjustedTopLeft.second]
            [selfHead.first-adjustedTopLeft.first] = 'H';
    if((transOppHead.first >= 0 &&
            transOppHead.first < updatedRet[0].length())
            && ((transOppHead.second >= 0 &&
            transOppHead.second < updatedRet.size()))) {
        updatedRet[transOppHead.second][transOppHead.first] = 'h';
    }

    return updatedRet;
}