#include "Player.h"
#include "config.h"

using namespace std;

class SampleMirror : public Player {

public:
    SampleMirror(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos, 
    int opponentDirection, int maxTurn, int visRange);

    ~SampleMirror();

    int getNextMove(vector<string> surroundings);

private:
	
};
