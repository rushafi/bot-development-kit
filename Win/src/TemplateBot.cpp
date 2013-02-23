#include "TemplateBot.h"

TemplateBot::TemplateBot(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos,
    int opponentDirection, int maxTurn, int visRange) {
    
    /* This is the default constructor that will be called.
     *
     * arenaDimension is a pair<int,int> that gives arena dimension as
     * width x height.
     *
     * collectibles is another pair<int,int> where the first element is the
     * number of positive collectibles in that arena and the second element is
     * the number of negative collectibles in that arena.
     *
     * startPos is another pair<int,int> that gives the starting position as
     * (x, y) where (0, 0) is the topleft position, x increases on right and
     * y increases downwards. The tail lies at startPos.
     *
     * initialDirection is the initial direction of the snake which can be
     * a value among UP, DOWN, LEFT, RIGHT. Check all directional values
     * against these values.
     *
     * initialLength is the initial length of the snake and its opponent.
     *
     * opponentPos the start poition of its opponent. The tail lies at this
     * point.
     *
     * opponentDirection is the initial direction of the opponent.
     *
     * maxTurn is the maximum number of turns. The game will terminate after
     * maxTurn turns if the game do not end before otherwise. A turn consists of
     *  player's move and opponent's move.
     *
     * visRange is the visibility range of the player. Each block of the players
     *  body will be able to see at least visRange blocks in any direction if
     * the visible block lies within the arena.
     */
}

TemplateBot::~TemplateBot() {
}

int TemplateBot::getNextMove(vector<string> surroundings) {

    /* override this method to return the next move of the snake.
     *
     * vector<string> surroundings provide a rectangular block around the
     * snake which it can see.
     *
     * the descriptors of surroundings are
     * W - White area / Can not be seen, added to make the block rentangular
     * B - Blocked
     * E - Empty
     * S - Self
     * O - Opponent (if within visibility range)
     * C - Positive collectibles / will grow the snake
     * N - Negative collectibles / will shrink the snake
     * H - Head of the snake
     * h - Head of opponent (if within visibility range)
     */

    return DOWN;
}