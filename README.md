# Project 02-The-Mill-Game

Implementation of The Mill Game. The game can be played locally, on server or versus AI.

## Getting Started

### Prerequisites

- If you want to compile your program with MakeFile you will need Qt5 base development files.
Example of command for downloading these files.
```
    sudo apt-get install qtbase5-dev
```

- Alternatively you can use [QtCreator](https://www.qt.io/download).

### Installing
Example of compiling project with Makefile.

1. Clone the repo.
```
    git clone https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2020-2021/02-the-mill-game
```
2. Make build file.
```
    mkdir build
    cd build
```
3. Compile program.
```
    cmake -G "Unix MakeFiles" ../02-the-mill-game
    make
``` 
4. Start the program.
```
    ./NineMensMorris
```

## Implementation ##

### Local ###

In a local game, two players can play on the same application instance. The game is played by clicking on the fields on the board and depending on the game phase, the pieces are placed, moved, or removed from the selected field. This is done by sending a signal on a mouse click and processing that signal to update the game state. When a move is made a message is displayed in the messages box beneath the board informing the players of what happened on the board. All GUI is made in QtCreator and the board is drawn manually using Qt5 libraries.

### Server ###

In this game mode, each player needs to run his own instance of the application. When the first player starts, a server process is run and the player is automatically connected to that server. When the second player starts, a check is made to see if the server is already running, and if it is,
the player is connected automatically, if it is not, he is actually the first player to run the game. When both players are connected the game can begin. When a player on turn plays a move, that data is sent to the server as a JSON containing all necessary data. The server processes that data and sends it to the other player and updates his game state and his board keeping the two games in synch.

### AI ###

AI is based on minimax algorithm with alfa-beta pruning. Since there are two phases of the game, the minimax and heuristcs used differ in each.
In the first phase of the game AI simulates the game by trying every possible play for each player. In this phase actions are defined by which field is the current player occupying. When the maximum depth of the search is reached, heuristc function is applied. The heuristic function takes into account each players number of pieces and the fields they are occupying, but also how each players pieces are arranged on the board (for example if two pieces of the first player are in the same line with the third field empty, giving him a chance to make a mill in the next turn).
In the second phase actions differ from the first phase, the algorithm now picks every piece from one player and tries to move it to every possible location on the board. Here heuristic function is trivially defined by number of steps until the first mill is reached, whether it was from first or second player. The ultimate heuristic reward in second phase is for winning/losing.
In both phases when the mill occurs it needs to be specially processed, for the player who made the mill algorithm simulates trying to remove each piece and continues the game from there, depending in which state of the game we are in.


## Developers

- [Nikola Andric Mitrovic, 441/2019](https://gitlab.com/andricmitrovic)
- [Marija Eric, 115/2017](https://gitlab.com/MarijaEric)
- [Jovan Milic, 127/2017](https://gitlab.com/jovan998)
- [Mihailo Jovanovic, 72/2017](https://gitlab.com/oliahim98)
