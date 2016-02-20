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
#include <cctype>
#include "mazeSolver.h"
using namespace std;


int main() {
  ifstream input;
  int rows, cols;

  // Open file
  get_file( input );
  // Get the dimensions of the maze
  get_dimensions( input, rows, cols );

  // dynamic allocation
  char** maze = new char*[rows];
  for(int i = 0; i < rows; ++i)
      maze[i] = new char[cols];

  // Load the maze into a 2d demensional array
  load_maze( input, maze, rows, cols );

  // Attempt to solve maze
  solve_maze( maze, rows, cols );

  // Print the maze
  print_maze( maze, rows, cols );

  // Close the file
  input.close();

  return 0;
}


void get_file( ifstream& input ) {
  bool file_errors;
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

    // Reset buffer
    input.clear();

  } while( file_errors );

}

int get_dimensions( ifstream& input, int& rows, int& cols ) {
  bool file_errors;

  input >> rows;
  input >> cols;

  // input.ignore();
  // if( !isdigit(rows) || !isdigit(cols) ) {
  //   cout << "The dimensions for the maze are invalid." << endl;
  //   exit(1);
  // }

}

// void doIt( char *maze, int cols, int row, int col );
// OR
// MAZE[ ( row * cols ) + col ]

void load_maze( ifstream& input, char **maze, int rows, int cols ) {
  // Ignore the newline
  input.ignore(1, '\n');

  for( int row = 0; row < rows && !input.eof(); row++ ) {
      input.getline( maze[row], cols );

      cout << row << "  Char: \"" << maze[row] << "\"" << endl;

  }

}

void solve_maze( char **maze, int rows, int cols ) {

}

void print_maze( char **maze, int rows, int cols ) {

  for( int row = 0; row < rows; row++ ) {
      cout << maze[row] << endl;
  }

  // for( int row = 0; row < rows; row++ ) {
  //   for( int col = 0; col < cols; col++ ) {
  //     cout << maze[row][col];
  //   }
  //   cout << endl;
  // }

}

// bool is_wall( *maze, int rows, int cols ) {
// }

// bool is_path( *maze, int rows, int cols ) {
// }

// bool is_exit( *maze, int rows, int cols ) {
// }

