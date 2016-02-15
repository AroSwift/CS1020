//
// Name: Aaron Barlow
// Date: 2/21/2016
// Description: Read in a given file
// in order to attempt to solve a maze.
//

#pragma once
#include <iostream>
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255


void get_dimensions( int& position_x, int& position_y );
void load_maze( int position_x, int position_y, char maze[][position_y] );
void print_maze();

