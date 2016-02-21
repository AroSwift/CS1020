//
// Name: Aaron Barlow
// Date: 2/21/2016
// Description: Read in a given file
// in order to attempt to solve a maze.
//

#pragma once
#include <iostream>
#include "stack.c"
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255
const char WALL[] = { '|', '_' };
const char PATH = ' ';

// enum { PATH = ' ', HERE_BEFORE = ',' }

const int START_ROW = 0;
const int START_COL = 1;

struct Positions {
  int row, col;
};


void get_file( ifstream& input );
int get_dimensions( ifstream& input, int& rows, int& cols );

void load_maze( ifstream& input, char **maze, int rows, int cols );
bool solve_maze( char **maze, int rows, int cols );
void print_maze( char **maze, int rows, int cols );

// void get_options( char **maze, int row, int col );
char get_down( char **maze, int rows, int row, int col );
char get_right( char **maze, int cols, int row, int col );
char get_left( char **maze, int row, int col );
char get_up( char **maze, int row, int col );

bool is_wall( char position );
bool is_path( char position );
bool is_exit( char position );