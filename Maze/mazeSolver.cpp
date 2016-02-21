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
  bool solved;

  // Open file
  get_file( input );
  // Get the dimensions of the maze
  get_dimensions( input, rows, cols );

  // dynamic allocation
  char** maze = new char*[rows];
  for(int i = 0; i < rows; ++i) maze[i] = new char[cols];

  // Load the maze into a 2d demensional array
  load_maze( input, maze, rows, cols );

  // Attempt to solve maze
  solved = solve_maze( maze, rows, cols );

  if(solved) {
    // Print the maze if maze was solved
    print_maze( maze, rows, cols );
  } else {
    cout << "The maze can not be solved.";
  }

  // Delete dynamically allocated 2d dimensional array
  for(int row = 0; row < rows; ++row) delete [] maze[row];
  delete [] maze;

  // Close the file
  input.close();

  return 0;
}


void get_file( ifstream& input ) {
  bool file_errors;
  char filename[MAX_FILE_LENGTH];

  do { // Find a file that exists
    file_errors = false;

    cout << "Enter file name: ";
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

  for( int row = 0; row < rows; row++ ) {

    input.getline( maze[row], cols );

    // cout << row << "  Char: \"" << maze[row] << "\"" << endl;

    // if( input.eof() ) cout << "Given dimensions do not map to the maze." << endl;

  }

}

bool solve_maze( char **maze, int rows, int cols ) {
  Stack current_location, options_location;
  initStack(&current_location);
  initStack(&options_location);
  bool solved = false;

  // for( int row = START_ROW; row < rows; row++ ) {
  //   for( int col = START_COL; col < cols; col++ ) {

  int current_row = START_ROW;
  int current_col = START_COL;

  while(!solved) {
    char down = get_down( maze, rows, current_row, current_col );
    char right = get_right( maze, cols, current_row, current_col );
    char left = get_left( maze, current_row, current_col );
    char up = get_up( maze, current_row, current_col );

    if( is_path(right) ) {
      if(is_exit(right)) {

      }
    } else if( is_wall(right) ) { // wall

    }

  }

      // push( &current_location, maze[row][col], stack... );
  //   }
  // }

  return solved;
}

// int get_options( char **maze, int row, int col ) {

// }

char get_down( char **maze, int rows, int row, int col ) {
  if(row < rows) maze[row+1][col];
}

char get_right( char **maze, int cols, int row, int col ) {
  if(col < cols) maze[row][col+1];
}

char get_left( char **maze, int row, int col ) {
  if(col != 0) maze[row][col-1];
}

char get_up( char **maze, int row, int col ) {
  if(row != 0) maze[row-1][col];
}

bool is_wall( char position ) {
  for( int i = 0; WALL[i] != '\0'; i++ ) {
    if(position == WALL[i]) {
      return true;
    }
  }

  // Otherwise, char is not wall
  return false;
}

bool is_path( char position ) {
  return position == PATH ? true : false;
}

bool is_exit( char position ) {
  if( is_path(position) ) {
    // if( row == max_rows || col == max_rows ) {
    //   return true;
    // }
    return true;
  }
  return false;
}

void print_maze( char **maze, int rows, int cols ) {
  for( int row = 0; row < rows; row++ ) cout << maze[row] << endl;
}
