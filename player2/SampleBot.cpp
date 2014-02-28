#include "SampleBot.h"

SampleBot::SampleBot(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos,
    int opponentDirection, int inmaxTurn, int visRange){

    idim=arenaDimension;
    coll=collectibles;
    sPos=startPos;
    idir=initialDirection;
    ilen=initialLength;
    oPos=opponentPos;
    odir=opponentDirection;
    maxTurn=inmaxTurn;
    vrange=visRange;

    nowTurn=0;
    // cout<<"idim:"<<idim.first<<" "<<idim.second<<endl;
    // cout<<"coll:"<<coll.first<<" "<<coll.second<<endl;
    // cout<<"sPos:"<<sPos.first<<" "<<sPos.second<<endl;
    // cout<<"idir:"<<idir<<endl;
    // cout<<"ilen:"<<ilen<<endl;
    // cout<<"opos:"<<oPos.first<<" "<<oPos.second<<endl;
    // cout<<"odir:"<<odir<<endl;
    // cout<<"t:"<<maxTurn<<endl;
    // cout<<"vrange:"<<vrange<<endl;

    setMyCurPos();

    int i;
    string tempGrid="";
    tempGrid.append(idim.first,'B');
    grid.push_back(tempGrid);
    tempGrid="B";
    tempGrid.append(idim.first-2,'W');
    tempGrid.append("B");
    for (i=0; i<idim.second-2; i++) grid.push_back(tempGrid);
    tempGrid="";
    tempGrid.append(idim.first,'B');
    grid.push_back(tempGrid);

    gotc=0;
    //printGrid();
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

SampleBot::~SampleBot() {
}

bool SampleBot::check(_pii found,int d)
{
    int i;
    int dx[]={0,1, 0,-1};
    int dy[]={1,0,-1, 0};
    bool vis[200][200]={0};
    int level[200][200]={0};

    _pii newPos=curPos;
         if (d==UP) newPos.second--;
    else if (d==DOWN) newPos.second++;
    else if (d==LEFT) newPos.first--;
    else if (d==RIGHT) newPos.first++;

    int nowLen=ilen+gotc;
    queue<_pii> q;
    vis[newPos.second][newPos.first]=1;
    vis[found.second][found.first]=1;
    level[found.second][found.first]=1;
    q.push(found);
    while (!q.empty())
    {
        _pii pop=q.front();q.pop();
        //if head
        if (level[pop.second][pop.first]>=(nowLen/2)) return true;

        for (i=0; i<4; i++)
        {
            char s=grid[pop.second+dx[i]][pop.first+dy[i]];
            int x=pop.first+dx[i];
            int y=pop.second+dy[i];
            if (vis[y][x]) continue;
            if (grid[y][x]=='W') return true;
            if (grid[y][x]!='E' && grid[y][x]!='C') continue;
            vis[y][x]=1;
            q.push(make_pair(x,y));
        }
    }
    return false;
}

RET SampleBot::find(int d)
{
    int i;
    int dx[]={0,1, 0,-1};
    int dy[]={1,0,-1, 0};
    bool vis[200][200]={0};
    int level[200][200]={0};
    int ret=0;
    queue<_pii> q;
    _pii newPos=curPos;
            if (d==UP) newPos.second--;
    else    if (d==DOWN) newPos.second++;
    else    if (d==LEFT) newPos.first--;
    else    if (d==RIGHT) newPos.first++;

    //cout<<curPos.first<<","<<curPos.second<<">"<<newPos.first<<","<<newPos.second<<" "<<grid[newPos.second][newPos.first]<<endl;
    int e=0;
    if (grid[newPos.second][newPos.first]=='E' || grid[newPos.second][newPos.first]=='C')
    {
        level[newPos.second][newPos.first]=1;
        vis[newPos.second][newPos.first]=1;
        q.push(newPos);
        e=1;
    }
    //printGrid();
    //cout<<"PUSHING:("<<curPos.first<<" "<<curPos.second<<") "<<grid[curPos.second][curPos.first]<<endl;
    while (!q.empty())
    {
        //cout<<q.size()<<endl;
        _pii pop=q.front();q.pop();
        if (grid[pop.second][pop.first]=='C')
        {
            _pii found=pop;
            //bool t=;
            //cout<<"check false"<<endl;
            if (check(found,d))
            {
                isc=true;
                RET r;
                r.pos=found;
                r.len=level[pop.second][pop.first];
                r.dir=d;

                return r;
            }
        }
        else if (grid[pop.second][pop.first]=='E') e++;
        //cout<<"POPING:("<<pop.first<<" "<<pop.second<<") "<<grid[pop.second][pop.first]<<endl;
        for (i=0; i<4; i++)
        {
            int x=pop.first+dx[i];
            int y=pop.second+dy[i];
            char s=grid[y][x];
            if (s!='E' && s!='C') continue;
            if (level[y][x]>(maxTurn-nowTurn)) continue;
            if (vis[y][x]) continue;
            vis[y][x]=1;
            level[y][x]=level[pop.second][pop.first]+1;
            //cout<<"PUSHING:("<<x<<" "<<y<<") "<<s<<endl;
            q.push(make_pair(x,y));
            /*for (int j=0; j<idim.second; j++)
            {
                for (int k=0; k<idim.first; k++) cout<<level[j][k];
                cout<<endl;
            }
            cout<<endl;*/



        }
    }
    RET r;
    r.pos=make_pair(-1,-1);
    if (e==0) r.len=10000000;
    else r.len=10000000-e;
    r.dir=d;
    return r;
    //cout<<grid[curPos.second][curPos.first]<<endl;
}

void SampleBot::setMyCurPos()
{
            if (idir==LEFT) curPos=make_pair(sPos.first-(ilen-1),sPos.second);
    else    if (idir==RIGHT) curPos=make_pair(sPos.first+(ilen-1),sPos.second);
    else    if (idir==UP) curPos=make_pair(sPos.first,sPos.second-(ilen-1));
    else    if (idir==DOWN) curPos=make_pair(sPos.first,sPos.second+(ilen-1));
}

bool SampleBot::valid(char s)
{
    return s=='E' || s=='C';
}

void SampleBot::goup()   {curPos.second--;if (grid[curPos.second][curPos.first]=='C') gotc++;idir=UP;}
void SampleBot::godown() {curPos.second++;if (grid[curPos.second][curPos.first]=='C') gotc++;idir=DOWN;}
void SampleBot::goleft() {curPos.first--; if (grid[curPos.second][curPos.first]=='C') gotc++;idir=LEFT;}
void SampleBot::goright(){curPos.first++; if (grid[curPos.second][curPos.first]=='C') gotc++;idir=RIGHT;}

_pii SampleBot::getHeadPos(vector<string> s)
{
    int i,j;
    for (i=0; i<s.size(); i++)
    {
        for (j=0; j<s[i].size(); j++)
        {
            if (s[i][j]=='H') return make_pair(j,i);
        }
    }

    return make_pair(0, 0);
}


void SampleBot::printGrid()
{
    int i;
    for (i=0; i<grid.size(); i++) cout<<grid[i]<<endl;
    for (i=0; i<grid[0].size()+2; i++) cout<<"_";
    cout<<endl;
}

void SampleBot::updateGrid(vector<string> surroundings,_pii hpos)
{
    int x=curPos.first-hpos.first;
    int y=curPos.second-hpos.second;

    int i,j;
    for (i=0; i<surroundings.size(); i++)
    {
        for (j=0; j<surroundings[i].size(); j++)
        {
            if (surroundings[i][j]!='W') grid[y+i][x+j]=surroundings[i][j];
        }
    }
    /*for (i=0; i<surroundings.size(); i++) cout<<surroundings[i]<<endl;
    cout<<hpos.first<<" "<<hpos.second;
    cout<<"______________________________"<<endl;*/
    //printGrid();
}

bool SampleBotf(RET a,RET b)
{
    return a.len<b.len;
}


int SampleBot::getNextMove(vector<string> surroundings) {

//    if (nowTurn==0) setMyCur(surroundings,sPos);

    nowTurn++;
    // cout<<nowTurn<<endl;
    int i,j;
    vector<RET> d;
    _pii vpos=getHeadPos(surroundings);
    updateGrid(surroundings,vpos);

    //goup();
    //return idir;
    isc=false;
    for (i=0; i<4; i++)
    {
        d.push_back(find(i));
    }
    sort(d.begin(),d.end(),SampleBotf);

    // for (i=0; i<d.size(); i++)
    // {
    //     if (d[i].dir==UP) cout<<"UP ";
    //     else if (d[i].dir==DOWN) cout<<"DOWN ";
    //     else if (d[i].dir==LEFT) cout<<"LEFT ";
    //     else if (d[i].dir==RIGHT) cout<<"RIGHT ";
    //     cout<<d[i].len<<endl;
    // }

         /*if (d[0].dir==UP) goup();
        else if (d[0].dir==DOWN) godown();
        else if (d[0].dir==LEFT) goleft();
        else if (d[0].dir==RIGHT) goright();

        return idir;*/
    if (gotc>=coll.first/2+10 || isc)
    {
             if (d[0].dir==UP) goup();
        else if (d[0].dir==DOWN) godown();
        else if (d[0].dir==LEFT) goleft();
        else if (d[0].dir==RIGHT) goright();
    }
    else
    {
        // found all e
        //select mid e
        if (d[1].len!=10000000)
        {
                 if (d[1].dir==UP) goup();
            else if (d[1].dir==DOWN) godown();
            else if (d[1].dir==LEFT) goleft();
            else if (d[1].dir==RIGHT) goright();
        }
        else
        {
                 if (d[0].dir==UP) goup();
            else if (d[0].dir==DOWN) godown();
            else if (d[0].dir==LEFT) goleft();
            else if (d[0].dir==RIGHT) goright();
        }
    }

    return idir;

    i=vpos.first;
    j=vpos.second;
            if (idir!=DOWN && valid(surroundings[i-1][j])) goup();
    else    if (idir!=UP && valid(surroundings[i+1][j])) godown();
    else    if (idir!=LEFT&& valid(surroundings[i][j-1])) goleft();
    else    if (idir!=RIGHT&& valid(surroundings[i][j+1])) goright();

    //idir=d[0].dir;

    //cout<<"idir:"<<idir<<endl;

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

    return idir;
}
