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
  Maze *m = new Maze();

  // Open file
  get_file( input );
  // Get the dimensions of the maze
  get_dimensions( input, m );

  // dynamic allocation
  m->maze = new char*[m->num_rows];
  for(int i = 0; i < m->num_rows; ++i) m->maze[i] = new char[m->num_cols];

  // Load the maze into a 2d demensional array
  load_maze( input, m );

  // Attempt to solve maze
  bool solved = solve_maze( m );

  if(solved) {
    print_maze( m );
  } else {
    cout << "The maze can not be solved.";
  }

  // Delete dynamically allocated 2d dimensional array
  for(int row = 0; row < m->num_rows; ++row) delete [] m->maze[row];
  delete [] m->maze;

  // // Close the file
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

int get_dimensions( ifstream& input, Maze *m ) {

  input >> m->num_rows;
  input >> m->num_cols;

  // cout << m->num_rows << "  " << m->num_cols << endl;

  // input.ignore();
  // if( !isdigit(rows) || !isdigit(cols) ) {
  //   cout << "The dimensions for the maze are invalid." << endl;
  //   exit(1);
  // }

}

void load_maze( ifstream& input, Maze *m ) {
  // Ignore the newline
  input.ignore(1, '\n');

  for( int row = 0; row < m->num_rows; row++ ) {

    input.getline( m->maze[row], m->num_cols );

    cout << row << "  Char: \"" << m->maze[row] << "\"" << endl;

    // if( input.eof() ) cout << "Given dimensions do not map to the maze." << endl;

  }

}

bool solve_maze( Maze *m ) {
  Stack current_location, options_location;
  initStack(&current_location);
  initStack(&options_location);
  bool solved = false;

  // for( int row = START_ROW; row < rows; row++ ) {
  //   for( int col = START_COL; col < cols; col++ ) {

  m->current_row = START_ROW;
  m->current_col = START_COL;

  m->maze[m->current_row][m->current_col] = '*';

  while(!solved) {

    // Maze adjacent_tiles[] = { p-> }

    if( m->get_down() ) {

    } else if( m->get_right() ) {

    } else if( m->get_left() ) {

    } else if( m->get_up() ) {

    } else if( m->num_options() > 1 ) {
      // When more than one option, push onto the options stack
      push(&options_location, m);
    } else { // no options, pop back
      if( isEmpty(&options_location) ) {
        solved = false;
        break;
      } else {
        pop( &options_location );
      }
    }


    // isEmpty(options_location);

    print_maze( m );

  }

  // State of maze resolution
  return solved;
}

int Maze::num_options() {
  // int num_options;

  // if( is_path(down) ) num_options++;
  // if( is_path(right) ) num_options++;
  // if( is_path(left) ) num_options++;
  // if( is_path(up) ) num_options++;

  // return num_options;
}

char Maze::get_down() {
  // if(row < num_rows) maze[row+1][col];
}

char Maze::get_right() {
  // if(col < num_cols) maze[row][col+1];
}

char Maze::get_left() {
  // if(col != 0) maze[row][col-1];
}

char Maze::get_up() {
  // if(row != 0) maze[row-1][col];
}

bool Maze::is_wall() {
  for( int i = 0; WALL[i] != '\0'; i++ ) {
    if(maze[current_row][current_col] == WALL[i]) {
      return true;
    }
  }

  // Otherwise, char is not wall
  return false;
}

bool Maze::is_path() {
  return maze[current_row][current_col] == PATH ? true : false;
}

bool Maze::is_exit() {
  // if( is_path(position) ) {
  //   // if( row == max_rows || col == max_rows ) {
  //   //   return true;
  //   // }
  //   return true;
  // }
  // return false;
}

void print_maze( Maze *m) {
  for( int row = 0; row < m->num_rows; row++ ) cout << m->maze[row] << endl;
}


