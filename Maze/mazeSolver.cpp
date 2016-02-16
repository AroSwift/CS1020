//
// Name: Aaron Barlow
// Date: 2/21/2016
// Description: Read in a given file
// in order to attempt to solve a maze.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "mazeSolver.h"
using namespace std;


int main() {
  Stack s;
  ifstream input;
  int rows, cols;

  // Open file
  get_file( input );
  // Get the dimensions of the maze
  get_dimensions( input, rows, cols );


  // Set size of maze as specified by file
  char maze[rows][cols];
  // Load the maze into a 2d demensional array
  load_maze( input, maze, rows, cols );

  // Close the file
  input.close();

  return 0;
}


void get_file( ifstream& input ) {
  bool file_errors;
  // ifstream input;
  char filename[MAX_FILE_LENGTH];

  do { // Find a file that exists
    file_errors = false;

    cout << "Enter input file name: ";
    cin.getline( filename, MAX_FILE_LENGTH ); // Max file length on linux is 255

    input.open( filename );

    // When file could not be found
    if( input.fail() ) {
      cout << "Input file " << filename << " does not exist. \n";
      file_errors = true;

    // When file is empty
    } else if( input.peek() == EOF ) {
      cout << "Input file " << filename << " is empty. \n";
      file_errors = true;
    }

  } while( file_errors );

}

int get_dimensions( ifstream& input, int& rows, int& cols ) {
  bool file_errors;

  input >> rows;
  input >> cols;

  if( !isdigit(rows) || !isdigit(cols) ) {
    cout << "The dimensions for the maze are invalid." << endl;
    exit(1);
  } else {
    return rows * cols;
  }

}

void load_maze( ifstream& input, char *maze, int rows, int cols ) {

  for( int row = 0; row < rows && !input.eof(); row++ ) {
    for( int col = 0; col < cols; col++ ) {

      input >> maze[row][col];

    }
  }

}

void print_maze( char *maze, int rows, int cols ) {

  // for( int row = 0; row < rows && !input.eof(); row++ ) {
  //   for( int col = 0; col < cols; col++ ) {

  //     // Bad code...
  //     cout << maze[row][col];

  //   }
  // }

}

bool is_maze_end( int rows, int cols ) {

}

