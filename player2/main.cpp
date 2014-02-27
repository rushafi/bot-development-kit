#include <cstdio>
#include <cstdlib>
#include "config.h"
#include "SampleBot.h"

using namespace std;

int main(int argc, char** argv) {

	int width, height;
	int maxTurn;
    int posCollectibles, negCollectibles;
    int visRange;
    _pii player1StartPosition, player2StartPosition;
    int player1StartDirection, player2StartDirection;
    int player1Length, player2Length;

    // printf("Player 2 starts\n");

	FILE *fd3, *fd4;

	fd3 = fdopen(3, "r");
	fd4 = fdopen(4, "w");

	fscanf(fd3, "%d %d", &width, &height);
    fscanf(fd3, "%d %d", &posCollectibles, &negCollectibles);
    fscanf(fd3, "%d %d", &player1StartPosition.first, &player1StartPosition.second);
    fscanf(fd3, "%d", &player1StartDirection);
    fscanf(fd3, "%d", &player1Length);
    fscanf(fd3, "%d %d", &player2StartPosition.first, &player2StartPosition.second);
    fscanf(fd3, "%d", &player2StartDirection);
    fscanf(fd3, "%d", &maxTurn);
    fscanf(fd3, "%d", &visRange);

    SampleBot *bot = new SampleBot(make_pair(width, height),
            make_pair(posCollectibles, negCollectibles), player1StartPosition,
            player1StartDirection, player1Length,
            player2StartPosition, player2StartDirection,
            maxTurn, visRange);

    int nLine;
    char line[80];

    while(fscanf(fd3, "%d", &nLine) == 1) {

        // printf("P2 Surroundings: %d\n", nLine);

        // if(nLine == -1) break;  // terminating condition achieved
        // else {

            // nLine is the number of lines to take input

            vector<string> surroundings;

            for(int ii = 0; ii < nLine; ii++) {

                fscanf(fd3, "%s", line);
                string sLine = line;
                surroundings.push_back(sLine);

                // printf("%s\n", sLine.c_str());
            }

            int nextDirection = bot->getNextMove(surroundings);

            fprintf(fd4, "%d\n", nextDirection);
            fflush(fd4);
        // }   
    }

	fclose(fd3);
	fclose(fd4);

	return 0;
}