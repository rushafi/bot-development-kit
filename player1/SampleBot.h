#include "Player.h"
#include "config.h"

using namespace std;

class SampleBot : public Player {

public:
    SampleBot(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos,
    int opponentDirection, int maxTurn, int visRange);

    ~SampleBot();

    void drawgrid();

    int bfs(int d);

    int getNextMove(vector<string> surroundings);

private:
    int width,height,npos,nneg,posx,posy,dir,len,oppx,oppy,oppdir,maxturn,visrange,now;
	char grid[200][200];
	int incx[4],incy[4];
	int oppgrid[200][200],st[200][200],ser[200][200];
	bool vis[200][200];
	double prob[200][200];
	vector<_pii> me;
};
