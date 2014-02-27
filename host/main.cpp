/* 
 * File:   main.cpp
 * Author: rushafi
 *
 * Created on November 13, 2011, 11:09 AM
 */

#include "GameEnv.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	
	string mapName = argv[1];
	string descriptorName = "host/simulation/input.txt";

    GameEnv *gameEnv = new GameEnv(mapName.c_str(), descriptorName.c_str());
    gameEnv->start();
    delete gameEnv;

    return 0;
}