/* 
 * File:   SnakeBot.cpp
 * Author: rushafi
 * 
 * Created on November 14, 2011, 12:38 AM
 */

#include "SnakeBot.h"

using namespace std;

SnakeBot::SnakeBot() {

}

SnakeBot::SnakeBot(const SnakeBot& orig) {
}

SnakeBot::~SnakeBot() {
}

SnakeBot::SnakeBot(_pii startPos, int length, int direction) {

    _pii currentPos = startPos;

    while(length--){
        snakeTrail.push(currentPos);
        switch (direction) {
            case LEFT:
                currentPos.first--;
                break;
            case RIGHT:
                currentPos.first++;
                break;
            case UP:
                currentPos.second--;
                break;
            case DOWN:
                currentPos.second++;
                break;
            default:
                ; // nothing to do
        }
    }

    _direction = direction;
		totalTime = 0;
		maxTime = 0.;
		minTime = 1.;
		turns = 0;
}

_pii SnakeBot::pushHead(int direction) {

    _pii tailPos = snakeTrail.back();
    
    switch (direction) {
        case LEFT:
            snakeTrail.push(make_pair(--tailPos.first, tailPos.second));
            break;
        case RIGHT:
            snakeTrail.push(make_pair(++tailPos.first, tailPos.second));
            break;
        case UP:
            snakeTrail.push(make_pair(tailPos.first, --tailPos.second));
            break;
        case DOWN:
            snakeTrail.push(make_pair(tailPos.first, ++tailPos.second));
            break;
        default:
            ;
    }
    
    _direction = direction;
    return tailPos; // tailPos is actually the position of the head
}

void SnakeBot::pushTail() {
    snakeTrail.pop();
}

int SnakeBot::getLength() {
    return snakeTrail.size();
}

int SnakeBot::getDirection() {
    return _direction;
}

_pii SnakeBot::getHeadPos() {
    return snakeTrail.back();
}

_pii SnakeBot::getTailPos() {
    return snakeTrail.front();
}

pair<_pii,_pii> SnakeBot::getBound() {

    // ((topLeft.x, topLeft.y), (bottomRight.x, bottomRight.y))

    vector<_pii> body = getSnakeBody(); // list of points that makes the snake

    _pii topLeft = make_pair(1<<30, 1<<30);
    _pii bottomRight = make_pair(0, 0);

    for(int i = 0; i < body.size(); i++) {
        if(body[i].first < topLeft.first) topLeft.first = body[i].first;
        if(body[i].second < topLeft.second) topLeft.second = body[i].second;

        if(body[i].first > bottomRight.first) bottomRight.first = body[i].first;
        if(body[i].second > bottomRight.second)
            bottomRight.second = body[i].second;
    }

    _pii boundedArea = make_pair(bottomRight.first - topLeft.first + 1,
            bottomRight.second - topLeft.second + 1);
    
    return make_pair(topLeft, bottomRight);
}

vector<_pii> SnakeBot::getSnakeBody() {
    vector<_pii> bodyBlocks;
    for(int i = 0; i < snakeTrail.size(); i++) {
        bodyBlocks.push_back(snakeTrail.front());
        snakeTrail.push(snakeTrail.front());
        snakeTrail.pop();
    }
    return bodyBlocks;
}

void SnakeBot::updateTime(time_t diff) {
		if(diff > maxTime) maxTime = diff;
		if(diff < minTime) minTime = diff;
		totalTime += diff;
		turns++;
}

double SnakeBot::getAverageTime() {
		return (double)totalTime/turns;
}

double SnakeBot::getMaxTime() {
		return (double)maxTime;
}

double SnakeBot::getMinTime() {
	return (double)minTime;
}