/* 
 * File:   SnakeBot.h
 * Author: rushafi
 *
 * Created on November 14, 2011, 12:38 AM
 */

#ifndef SNAKEBOT_H
#define	SNAKEBOT_H

#include "config.h"

using namespace std;

class SnakeBot {

public:

    SnakeBot();
    SnakeBot(_pii startPos, int length, int direction);
    SnakeBot(const SnakeBot& orig);
    virtual ~SnakeBot();

    _pii pushHead(int direction);
    void pushTail();
    int getLength();
    int getDirection();
    _pii getHeadPos();
    _pii getTailPos();

    pair<_pii,_pii> getBound(); // ((topLeft.x, topLeft.y), (width, height))
    vector<_pii> getSnakeBody();
		void updateTime(time_t diff);
		double getAverageTime();
		double getMaxTime();
		double getMinTime();
		
private:

    queue<_pii> snakeTrail;
    int _direction;
		time_t totalTime;
		time_t maxTime;
		time_t minTime;
		int turns;
};

#endif	/* SNAKEBOT_H */