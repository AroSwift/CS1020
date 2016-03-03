//
// maze.cpp
// Written by: Dr. Brown
// 03/01/2016
//
// A stack-based maze solver. Solves mazes by pushing all choices
// at a given position, then popping a move. At dead-ends, no
// choices are pushed, so a previous position choice will be
// popped (thus returning to a previous position). If a dead-end
// is reached with no previous choice positions available, then
// the maze is unsolvable.
//
#include <iostream>
#include <cstdlib>
#include "maze.h"
#include "stack.h"
#include "util.h"
using namespace std;

//
// main
// Load the maze from a data file, try to solve the maze,
// print a message telling whether the maze could be
// solved, and then print the maze showing the solution
// (or lack thereof).
//
int main() {
    Maze maze;
    loadMaze(maze);
    if (solveMaze(maze)) 
        cout << "Maze solved!" << endl;
    else 
        cout << "Maze can't be solved." << endl;
    printMaze(maze);
}

//
// loadMaze
// Prompt for maze data file, open the file, load the maze
// from the file and then close the file. Maze data files
// have a first line with the number of rows and columns
// then the maze with walls marked with either '|' or '_'
// and spaces for paths. Entry point is row 0, column 1.
//
void loadMaze(Maze& maze) {
    ifstream mazeFile;
    // Get a valid file name and open the file.
    do {
        cout << "Maze data file: ";
        string fileName;
        cin >> fileName;
        mazeFile.open(fileName.c_str());
        if (!mazeFile.is_open())
            cout << "Can't open " << fileName << "..." << endl;
    } while(!mazeFile.is_open());
    //
    // Read in the maze data.
    //
    mazeFile >> maze.rows >> maze.cols;
    maze.cells = (char *)malloc(sizeof(char) * maze.rows * maze.cols);
    int current = 0;
    // first getline is to advance past newline following dimensions
    string row;
    getline(mazeFile, row, '\n'); 
    // Load the maze data
    for (int i = 0; i < maze.rows; i++) {
        getline(mazeFile, row, '\n'); 
        for(int j = 0; j < maze.cols; j++)
            maze.cells[current++] = row[j];
    }
    mazeFile.close();
}

//
// printMaze
// Output the maze.
//
void printMaze(Maze maze) {
    char *cells = maze.cells;
    for (int i = 0; i < maze.rows; i++) {
        for(int j=0; j < maze.cols; j++)
            cout << *(cells++);
        cout << endl;
    }
}

//
// solveMaze
// Solves a maze if possible and recognizes mazes that
// have no solution. Marks dead-end paths with dashes,
// solution path with asterisks and the exit point with
// '@'.
//
bool solveMaze(Maze& maze) {
    // Create moves and choices stacks.
    Stack *moves = newStack();
    Stack *choices = newStack();
    // Start at row 0, column 1.
    Position *current = new Position;
    current->x = 1;
    current->y = 0;
    push(moves, (void *)current);
    setMaze(maze, *current, '@');
    //
    // Maze solver loop. Push all options from the
    // current location. Pop a move and move there.
    // If a dead-end is reached and no previous
    // choices are available, the maze can't be solved.
    //
    do {
        pushOptions(maze, *current, choices);
        // If not moves are available, the maze can't
        // be solved. This code replaces the last
        // path with dashes.
        if (isEmpty(choices)) {
            Choice c;
            c.pos.x = 1;
            c.pos.y = 0;
            popToChoice(maze, moves, c);
            setMaze(maze, c.pos, '-');
            return(false);
        }
        // There is still a chance of solving the maze...
        Choice *c = (Choice *)pop(choices);
        popToChoice(maze, moves, *c);
        current = move(maze, *current, *c, moves);
    } while(!isExitPoint(maze,*current));
    // An exit point was found!
    return(true);
}

//
// move
// Move from the current position as directed by the choice (c)
// which contains a position and a direction index (telling which
// direction to move).
//
Position *move(Maze maze, Position current, Choice c, Stack *moveStack) {
    cout << "Moved from " << current.x << "," << current.y;
    // Are we just moving from the current position, or are
    // we popping back to a previous position?
    if ((current.x == c.pos.x) && (current.y == c.pos.y))
       setMaze(maze, current, '*'); // regular move
    else
       setMaze(maze, current, '-'); // previous position
    // Calculate new position to move to.
    Position *newCurrent = new Position();
    newCurrent->x = c.pos.x + DIR_OFFSET[c.dir].x;
    newCurrent->y = c.pos.y + DIR_OFFSET[c.dir].y;
    // Mark the current position.
    setMaze(maze, *newCurrent, '@');   
    cout << " to " << newCurrent->x << "," << newCurrent->y << endl;
    // Push move onto move stack.
    push(moveStack, (void *)newCurrent);
    return(newCurrent);
}

//
// pushOptions
// Push all available moves from the current location onto
// the choices stack.
//
void pushOptions(Maze maze, Position current, Stack *choices) {
    bool foundPath = false;
    // Test each of the 4 available directions.
    for(int i=0; i < NUM_DIRECTIONS; i++) {
        int x, y;
        // Find the new position to test.
        x = current.x + DIR_OFFSET[i].x;
        y = current.y + DIR_OFFSET[i].y;
        // See if the new position is valid and a path.
        if ((x >= 0) && (x < maze.cols))
            if ((y >= 0) && (y < maze.rows)) 
                // If new position is a valid path, push it
                // onto the choices stack.
                if (*(maze.cells + (y * maze.cols) + x) == ' ') {
                    foundPath = true;
                    Choice *c = new Choice();
                    c->pos.x = current.x;
                    c->pos.y = current.y;
                    c->dir = (Direction)i;
                    push(choices, (void *)c);
                }
    }
    // Were any choices found from the current position?
    if (!foundPath) 
        cout << "Dead end: " << current.x << "," << current.y << endl;
}

//
// popToChoice
// Pop moves stack back to the location indicated in choice (c).
//
void popToChoice(Maze& maze, Stack *moves, Choice c) {
    Position *p;
    // Main loop. Keep popping from the stack until we
    // find the position indicated in Choice c.
    do {
       if (isEmpty(moves)) {
           cout << "Error: Empty move stack in popToChoice..." << endl;
           return;
       }
       p = (Position *)pop(moves);
       setMaze(maze, *p, '-');
    } while((p->x != c.pos.x) || (p->y != c.pos.y));
    // Push the last move back on. This is where we currently
    // are in the maze.
    push(moves, p);
    setMaze(maze, *p, '*');
}

//
// setMaze
// Set the indicated postion (p) in the maze to the indicated
// character (c).
//
void setMaze(Maze& maze, Position p, char c) {
    *(maze.cells + (p.y * maze.cols) + p.x) = c;
}

//
// isExitPoint
// Returns true if Position p is an exit point and false
// otherwise. The position row = 0, column = 1 is the entry 
// point and therefore not an exit point. 
//
bool isExitPoint(Maze maze, Position p) {
    // Entry point can't be exit point
    if ((p.x == 1) && (p.y == 0))
        return(false);
    
    if ((p.x == 0) || (p.x == (maze.cols - 1)))
        return(true);
        
    if ((p.y == 0) || (p.y == (maze.rows - 1)))
        return(true);
        
    return(false);
}