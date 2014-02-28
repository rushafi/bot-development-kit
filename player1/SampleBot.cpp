#include "SampleBot.h"
#include <queue>

void SampleBot::drawgrid()
{
    int i,j,x,y;
    for (i=0;i<width;i++)
    {
        for (j=0;j<height;j++) grid[i][j]='W';
    }
    _pii p;
    for (i=0;i<len-1;i++)
    {
        grid[posx][posy]='S';
        p=make_pair(posx,posy);
        me.insert(me.begin(),p);
        posx+=incx[dir];
        posy+=incy[dir];
    }
    grid[posx][posy]='H';
    p=make_pair(posx,posy);
    me.insert(me.begin(),p);
    for (i=0;i<len-1;i++)
    {
        grid[oppx][oppy]='O';
        p=make_pair(oppx,oppy);
        oppx+=incx[oppdir];
        oppy+=incy[oppdir];
    }
    grid[oppx][oppy]='h';
}

SampleBot::SampleBot(_pii arenaDimension, _pii collectibles, _pii startPos,
    int initialDirection, int initialLength, _pii opponentPos,
    int opponentDirection, int maxTurn, int visRange) {

     width=arenaDimension.first;
     height=arenaDimension.second;
     npos=collectibles.first;
     nneg=collectibles.second;
     posx=startPos.first;
     posy=startPos.second;
     dir=initialDirection;
     len=initialLength;
     oppx=opponentPos.first;
     oppy=opponentPos.second;
     oppdir=opponentDirection;
     maxturn=maxTurn;
     visrange=visRange;
     now=0;
     incx[0]=incx[2]=0;
     incx[1]=1;
     incx[3]=-1;
     incy[1]=incy[3]=0;
     incy[0]=-1;
     incy[2]=1;
     int i,j;
     for (i=0;i<width;i++)
     {
         for (j=0;j<height;j++) oppgrid[i][j]=-1;
     }
    // printf("only here 1\n");
     drawgrid();
}

SampleBot::~SampleBot() {
}

int SampleBot::bfs(int d)
{
    double ret=0.0;
    int i,j,c1=0,c2=width*height,c3=1,c4=0,max1=0;
    for (i=0;i<width;i++)
    {
        for (j=0;j<height;j++) vis[i][j]=0;
    }
    for (i=0;i<me.size();i++)
    {
        ser[me[i].first][me[i].second]=len-i-1;
    }
    queue<_pii> q;
    _pii p,pre;
    p=make_pair(posx+incx[d],posy+incy[d]);
    if (p.first>=0&&p.first<width&&p.second>=0&&p.second<height)
    {
        if (grid[p.first][p.second]!='B'&&grid[p.first][p.second]!='H'&&grid[p.first][p.second]!='S')
        {
            if (grid[p.first][p.second]!='W'&&grid[p.first][p.second]!='h'&&grid[p.first][p.second]!='O')
            {
                vis[p.first][p.second]=1;
                prob[p.first][p.second]=1.0;
                st[p.first][p.second]=1;
                if (grid[p.first][p.second]=='E') c1++;
                else if (grid[p.first][p.second]=='C')
                {
                    c1+=3;
                    if (c2==width*height) c2=st[p.first][p.second];
                    c4=1;
                }
                else
                {
                    c1++;
                    c3=0;
                }
                q.push(p);
                while (!q.empty())
                {
                    pre=q.front();
                    q.pop();
                    max1=st[pre.first][pre.second];
                    //if (st[pre.first][pre.second]==maxturn-now) continue;
                    for (i=0;i<4;i++)
                    {
                        p=make_pair(pre.first+incx[i],pre.second+incy[i]);
                        if (p.first>=0&&p.first<width&&p.second>=0&&p.second<height&&!vis[p.first][p.second])
                        {
                            if (grid[p.first][p.second]!='B'&&grid[p.first][p.second]!='h'&&grid[p.first][p.second]!='O')
                            {
                                if (grid[p.first][p.second]!='W')
                                {
                                    if ((grid[p.first][p.second]=='H'||grid[p.first][p.second]=='S')
                                                &&ser[p.first][p.second]>=st[pre.first][pre.second]+1) continue;
                                    vis[p.first][p.second]=1;
                                    prob[p.first][p.second]=prob[pre.first][pre.second]*1.0/c1;
                                    st[p.first][p.second]=st[pre.first][pre.second]+1;
                                    if (grid[p.first][p.second]=='E')
                                    {
                                        c1++;
                                    }
                                    else if (grid[p.first][p.second]=='C')
                                    {
                                        c1+=3;
                                        if (c2==width*height) c2=st[p.first][p.second];
                                    }
                                    else
                                    {
                                        c1++;
                                    }
                                    q.push(p);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //int x=rand()%19+1;
    return c1*3+(width*height-c2+c3+c4);

}

int SampleBot::getNextMove(vector<string> surroundings) {

     now++;
    // printf("%d %d\n",posx,posy);
     int i,j,givx,givy,l,prevx,prevy;
     int tot[4],max1;
     _pii p;
     for (i=0;i<surroundings[0].length();i++)
     {
         for (j=0;j<surroundings.size();j++)
         {
             if (surroundings[j][i]=='H') break;
         }
         if (j<surroundings.size()) break;
     }
    /*if (now==1)
    {
        for (i=0;i<surroundings.size();i++)
        {
            cout<<surroundings[i]<<endl;
        }
    }*/
     givx=i;
     givy=j;
    // printf("givx givy %d %d\n",givx,givy);
     for (i=0;i<surroundings[0].length();i++)
     {
         for (j=0;j<surroundings.size();j++)
         {
             if (surroundings[j][i]!='W') grid[posx-(givx-i)][posy-(givy-j)]=surroundings[j][i];
             if (surroundings[j][i]=='O'||surroundings[j][i]=='h') oppgrid[posx-(givx-i)][posy-(givy-j)]=now;
         }
     }
     for (i=0;i<width;i++)
     {
         for (j=0;j<height;j++)
         {
             if (oppgrid[i][j]!=-1&&oppgrid[i][j]<now-10) grid[i][j]='E';
         }
     }
     max1=0;
     l=0;
     for (i=0;i<4;i++)
     {
         tot[i]=bfs(i);
         if (tot[i]>max1)
         {
             max1=tot[i];
             l=i;
         }
     }
     prevx=posx;
     prevy=posy;

     posx+=incx[l];
     posy+=incy[l];
     if (posx<0||posx>=width||posy<0||posy>=height) return l;
     if (grid[posx][posy]=='C')
     {
         len++;
         p=make_pair(posx,posy);
         me.insert(me.begin(),p);
         if (len>1)
         {
             grid[prevx][prevy]='S';
         }
         grid[posx][posy]='H';
     }
     else if (grid[posx][posy]=='N')
     {
         len--;
         p=make_pair(posx,posy);
         me.insert(me.begin(),p);
         if (len>1)
         {
             grid[prevx][prevy]='S';
         }
         grid[posx][posy]='H';
         grid[me[me.size()-1].first][me[me.size()-1].second]='E';
         me.pop_back();
         grid[me[me.size()-1].first][me[me.size()-1].second]='E';
         me.pop_back();
     }
     else if (grid[posx][posy]=='E')
     {
         p=make_pair(posx,posy);
         me.insert(me.begin(),p);
         if (len>1)
         {
             grid[prevx][prevy]='S';
         }
         grid[posx][posy]='H';
         grid[me[me.size()-1].first][me[me.size()-1].second]='E';
         me.pop_back();
     }
     //else printf("save me\n");
     //printf("here %d %d\n",len,now);
    return l;
}
