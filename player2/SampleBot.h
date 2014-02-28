#include "Player.h"
#include "config.h"
#include <algorithm>
#include <queue>

using namespace std;


struct RET
{
    _pii pos;
    int len;
    int dir;
};



class SampleBot : public Player {

public:
    _pii idim,coll,sPos,oPos;
    int idir,ilen,odir,maxTurn,nowTurn,vrange;

    _pii curPos;

    vector<string> grid;
    bool isc;
    int gotc;


    SampleBot(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos,
    int opponentDirection, int inmaxTurn, int visRange);

    ~SampleBot();

    int getNextMove(vector<string> surroundings);
    void updateGrid(vector<string> surroundings,_pii hpos);
    RET find(int d);
    bool check(_pii found,int d);
    void printGrid();
    void setMyCurPos();
    _pii getHeadPos(vector<string> s);
    bool valid(char s);
    void goup();
    void godown();
    void goleft();
    void goright();


private:

};
