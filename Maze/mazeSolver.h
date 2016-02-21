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

// Dashes are areas already attempted and ought to be treated as a wall
const char WALL[] = { '|', '_', '-' };
const char PATH = ' ';

// enum { PATH = ' ', HERE_BEFORE = ',' }

const int START_ROW = 0;
const int START_COL = 1;

struct Maze {
  char** maze;
  int num_rows, num_cols;
  int current_row, current_col;

  Stack current_location, options_location;

  // bool down_possible();
  // bool right_possible();
  // bool left_possible();
  // bool up_possible();

  char get_down();
  char get_right();
  char get_left();
  char get_up();

  bool is_wall();
  bool is_path();
  bool is_exit();
};


void get_file(ifstream& input );
int get_dimensions(ifstream& input, Maze *m);

void load_maze(ifstream& input, Maze *m);
// void validate_maze(Maze *m);
bool solve_maze(Maze *m);
void print_maze(Maze *m);
