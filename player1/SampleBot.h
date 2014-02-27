#include "Player.h"
#include "config.h"

using namespace std;

class SampleBot : public Player {

public:
    SampleBot(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos, 
    int opponentDirection, int maxTurn, int visRange);

    ~SampleBot();

    int getNextMove(vector<string> surroundings);

private:
	
};
