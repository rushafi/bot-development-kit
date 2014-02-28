#!/bin/bash
echo "compiling...";
cd host;
rm snake;
g++ *.cpp -o snake;
cd ..;
cd player1;
rm player1;
g++ *.cpp -o player1;
cd ..;
cd player2;
rm player2;
g++ *.cpp -o player2;
cd ..;
chmod 777 tester;
./tester "./host/snake ./host/arena/1" "./player1/player1" "./player2/player2";
echo "Game descriptor generated in host/simulation/input.txt";
echo "Run Snake.swf with any Shockwave Player or Google Chrome";