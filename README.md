Supported Platforms

- Linux
- Mac OSX
- Windows

Prerequisite

- GNU GCC compiler (MinGW if Windows)

How to Run

- A script is provided to build, clean, create new empty bot and to run the game with defined map file and player
- In Linux and Mac the script should be accessed from terminal as ./run
- In Windows it should be invoked as run.bat

Flags

- There are some flags to do some other tasks than building and running the game. They are described below. Replace ./run with run.bat if in windows

Clean

./run -c

Create empty bot class

./run -n TestBot	// Two files named TestBot.h and TestBot.cpp will be created

Set Players to default

./run -d	// Default players are SampleBot and SampleMirror. Do not delete them

Build and Run the game

./run	// Will build and Run the game with default players and map

Run Game with specific map and players

./run -map 1	// Start the game in map 1
./run -map 1 TestBot	// Start the game in map 1 between SampleBot (given) and TestBot. TestBot will be player 2
./run -map 1 TestBot AnotherBot	// Start the game in map 1 between TestBot and AnotherBot