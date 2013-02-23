#include "Player.h"
#include "config.h"

using namespace std;

class TemplateBot : public Player {

public:
    TemplateBot(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos, 
    int opponentDirection, int maxTurn, int visRange);

    ~TemplateBot();

    int getNextMove(vector<string> surroundings);

private:
	
};