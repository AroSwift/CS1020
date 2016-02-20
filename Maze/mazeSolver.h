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
const char NOT_WALL = ' ';


void get_file( ifstream& input );
int get_dimensions( ifstream& input, int& rows, int& cols );
void load_maze( ifstream& input, char **maze, int rows, int cols );

void print_maze( char **maze, int rows, int cols );