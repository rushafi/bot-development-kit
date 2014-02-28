### Disclamer

The master branch is no more supported. If you want a sneak peak try:

```bash
git checkout distributed
```

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

```bash
./run -c
```

Create empty bot class

```bash
./run -n TestBot	// Two files named TestBot.h and TestBot.cpp will be created
```

Set Players to default (Default players are SampleBot and SampleMirror. Do not delete them)

```bash
./run -d
```

Build and Run the game (Will build and Run the game with default players and map)

```bash
./run
```

Run Game with specific map and players

- Start the game in map 1
```bash
./run -map 1
```
- Start the game in map 1 between SampleBot (given) and TestBot. TestBot will be player 2
```bash
./run -map 1 TestBot
```
- Start the game in map 1 between TestBot and AnotherBot
```bash
./run -map 1 TestBot AnotherBot
```