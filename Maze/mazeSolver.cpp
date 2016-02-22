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

  // Account for the null character
  m->num_rows++;
  m->num_cols++;

  // dynamic allocation
  m->maze = new char*[m->num_rows];
  for(int i = 0; i < m->num_rows; ++i) {
    m->maze[i] = new char[m->num_cols];
  }

  // Load the maze into a 2d demensional array
  load_maze( input, m );

  // Attempt to solve maze
  bool solved = solve_maze( m );

  if(solved) {
    print_maze( m );
  } else {
    cout << "The maze can not be solved." << endl;
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
    cin.getline( filename, MAX_FILE_LENGTH );

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

void get_dimensions( ifstream& input, Maze *m ) {

  input >> m->num_rows;
  input >> m->num_cols;
  input.ignore();

  // if( m->num_rows < 0 || m->num_cols < 0 ) {
  //   cout << "The dimensions for the maze are invalid." << endl;
  //   exit(1);
  // }

}

void load_maze( ifstream& input, Maze *m ) {
  // Ignore the newline
  input.ignore(1, '\n');

  for( int row = 0; row < m->num_rows; row++ ) {
    // if( input.eof() ) {
    //   cout << "Given dimensions do not map to the maze." << endl;
    //   exit(1);
    // }

    input.getline( m->maze[row], m->num_cols );
  }

  // Ensure maze is valid
  // validate_maze(m);

}

// void validate_maze(Maze *m) {
//   bool error = false;

//   for( int row = 0; row < m->num_rows; row++ ) {
//     for( int col = 0; col < m->num_cols; col++ ) {

//       for( int i = 0; WALL[i] != '\0'; i++ ) {
//         if(m->maze[row][col] == WALL[i]) error = true;
//       }

//       if(m->maze[row][col] != PATH) error = true;

//     }
//   }

//   if(error) {
//     cout << "The maze is invalid." << endl;
//     exit(1);
//   }
// }

bool solve_maze( Maze *m ) {
  Stack current_location, options_location;
  initStack(&current_location);
  initStack(&options_location);
  bool solved = false;

  // Set the starting row and col of maze
  m->cords.row = START_ROW;
  m->cords.col = START_COL;
  push(&current_location, &m->cords);

  m->maze[m->cords.row][m->cords.col] = '*';

  while(!solved) {
    bool switched_location = false;

    // When down is possible
    if( m->down_possible() ) {
      m->cords.row++;
      switched_location = true;
    }

    // When right is possible
    if( m->right_possible() ) {
      if(!switched_location) {
        m->cords.col++;
        switched_location = true;
      }
    }

    // When left is possible
    if( m->left_possible() ) {
      if(!switched_location) {
        m->cords.col--;
        switched_location = true;
      }
    }

    // When up is possible
    if( m->up_possible() ) {
      if(!switched_location) {
        m->cords.row--;
        switched_location = true;
      }
    }

    if(switched_location) {
      m->maze[m->cords.row][m->cords.col] = '*';
      push(&current_location, &m->cords);
    }

    print_maze( m );
    cout << endl;

    if( m->num_options() > 1 ) {
      // When more than one option, push onto the options stack
      push(&options_location, &m->cords);

    // When no options, pop back if possible
    } else if( m->num_options() == 0 ) {
      if( m->is_exit() ) {
        solved = true;
      } else if( isEmpty(&options_location) ) {
        // Impossible to solve
        solved = false;
        // Exit loop
        break;
      } else {
        cout << "Revering options?" << endl;
        m->revert_options( &current_location, &options_location );
      }
    }

  }

  // State of maze resolution
  return solved;
}

bool Maze::down_possible() {
  if( cords.row < num_rows && is_path(get_down()) ) return true;
  // Otherwise, down is not possible
  return false;
}

bool Maze::right_possible() {
  if( cords.col < num_cols && is_path(get_right()) ) return true;
  // Otherwise, right is not possible
  return false;
}
bool Maze::left_possible() {
  if( cords.col != 0 && is_path(get_left()) ) return true;
  // Otherwise, left is not possible
  return false;
}

bool Maze::up_possible() {
  if( cords.row != 0 && is_path(get_up()) ) return true;
  // Otherwise, down is not possible
  return false;
}

char Maze::get_down() {
 return maze[cords.row+1][cords.col];
}

char Maze::get_right() {
  return maze[cords.row][cords.col+1];
}

char Maze::get_left() {
 return maze[cords.row][cords.col-1];
}

char Maze::get_up() {
 return maze[cords.row-1][cords.col];
}

int Maze::num_options() {
  int options = 0;

  if( down_possible() ) options++;
  if( right_possible() ) options++;
  if( left_possible() ) options++;
  if( up_possible() ) options++;

  return options;
}

void Maze::revert_options( Stack *current, Stack *options ) {
  Cords *options_position = (Cords*)pop( options );
  cords = *options_position;

  while( true ) {
    Cords *back_once = (Cords*)pop(current);

    // cout << "BEFORE:" << endl;
    // cout << back_once->row << "  :  " << options_position->row << endl;
    // cout << back_once->col << "  :  " << options_position->col << endl;

    maze[back_once->row][back_once->col] = '-';

    // cout << "AFTER:" << endl;
    // cout << back_once->row << "  :  " << options_position->row << endl;
    // cout << back_once->col << "  :  " << options_position->col << endl;

    if( back_once->row == options_position->row
      && back_once->col == options_position->col ) {
      break;
    }

  }

}

bool Maze::is_exit() {
  // is_edge

  if( cords.row+1 == num_rows-1 || cords.col+1 == num_cols-1 ) {
    if( maze[cords.row][cords.col] == PATH_TAKEN ) {
      return true;
    }
  }

  // Otherwise, is not the maze exit
  return false;
}

bool is_wall( char c ) {
  for( int i = 0; WALL[i] != '\0'; i++ ) {
    if(c == WALL[i]) {
      return true;
    }
  }

  // Otherwise, char is not wall
  return false;
}

bool is_path( char c ) {
  return c == PATH ? true : false;
}

void print_maze( Maze *m) {
  for( int row = 0; row < m->num_rows; row++ ) {
    cout << m->maze[row] << endl;
  }
}

