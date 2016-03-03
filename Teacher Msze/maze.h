//
// maze.h
// Written by: Dr. Brown
// 03/01/2016
//
#pragma once
#include <fstream>
#include "stack.h"

//
// Direction constants.
//
enum Direction {UP, DOWN, LEFT, RIGHT};
//
// Position 
// Used to hold moves and pushed on move stack.
struct Position {
    int       x, y;
};
//
// Choice
// Used to hold potential moves from a position and
// pushed onto choices stack.
struct Choice {
    Position  pos;
    Direction dir;
};

//
// Maze
// Contains the maze data.
struct Maze {
    char *cells;
    int  rows, cols;
};

//
// DIR_OFFSET
// Used to hold offsets for the 4 possible directions from
// a position in the maze.
const Position DIR_OFFSET[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int NUM_DIRECTIONS = 4;

// Prototypes
void loadMaze(Maze& maze);
void printMaze(Maze maze);
bool solveMaze(Maze& maze);
Position *move(Maze maze, Position current, Choice c, Stack *moveStack);
void pushOptions(Maze maze, Position current, Stack *choices);
void popToChoice(Maze& maze, Stack *moves, Choice c);
void setMaze(Maze& maze, Position p, char c);
bool isExitPoint(Maze maze, Position p);