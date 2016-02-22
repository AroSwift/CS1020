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

//
// get_file
// Continuously prompts user for a file and
// Then attempts to get that file until the file is opened.
//
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

//
// get_dimensions
// Get the dimensions of the maze from a file.
//
void get_dimensions( ifstream& input, Maze *m ) {
  input >> m->num_rows;
  input >> m->num_cols;
  input.ignore();
}

void load_maze( ifstream& input, Maze *m ) {

  for( int row = 0; row < m->num_rows; row++ ) {
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


//
// solve_maze
// Attempts to solve the maze while not solved.
// It goes down, right, left, and up and push cords onto a stack.
// When there are multiple options, push those cords onto a seperate stack.
// When maze is solved or unsolvable, stop attempting to solve maze.
//
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
    if( !switched_location && m->right_possible() ) {
      m->cords.col++;
      switched_location = true;
    }

    // When left is possible
    if( !switched_location && m->left_possible() ) {
      m->cords.col--;
      switched_location = true;
    }

    // When up is possible
    if( !switched_location && m->up_possible() ) {
      m->cords.row--;
      switched_location = true;
    }

    if(switched_location) {
      m->maze[m->cords.row][m->cords.col] = '*';
      Cords current_postion = m->cords;
      cout << "Current Pos:" << m->cords.row << " - " << m->cords.col << endl;
      push(&current_location, &current_postion);
    }

    print_maze( m );
    cout << endl;

    if( m->num_options() > 1 ) {
      // When more than one option, push onto the options stack
      Cords options_position = m->cords;
      cout << "Options" << m->cords.row << " - " << m->cords.col << endl;
      push(&options_location, &options_position);

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
        cout << "Reverting..." << endl;
        m->revert_options( &current_location, &options_location );
      }
    }

  }

  // State of maze resolution
  return solved;
}

//
// down_possible
// Return whether below the maze is possible.
//
bool Maze::down_possible() {
  if( cords.row < num_rows && is_path(get_down()) ) return true;
  // Otherwise, down is not possible
  return false;
}

//
// right_possible
// Return whether right of the maze is possible.
//
bool Maze::right_possible() {
  if( cords.col < num_cols && is_path(get_right()) ) return true;
  // Otherwise, right is not possible
  return false;
}

//
// left_possible
// Return whether left of the maze is possible.
//
bool Maze::left_possible() {
  if( cords.col != 0 && is_path(get_left()) ) return true;
  // Otherwise, left is not possible
  return false;
}

//
// up_possible
// Return whether moving up the maze is possible.
//
bool Maze::up_possible() {
  if( cords.row != 0 && is_path(get_up()) ) return true;
  // Otherwise, down is not possible
  return false;
}

//
// get_down
// Return the character that is below the current maze position.
//
char Maze::get_down() {
 return maze[cords.row+1][cords.col];
}

//
// get_right
// Return the character that is right of the current maze position.
//
char Maze::get_right() {
  return maze[cords.row][cords.col+1];
}

//
// get_left
// Return the character that is left of the current maze position.
//
char Maze::get_left() {
 return maze[cords.row][cords.col-1];
}

//
// get_up
// Return the character that is above the current maze position.
//
char Maze::get_up() {
 return maze[cords.row-1][cords.col];
}

//
// num_options
// Return the number of possible options to be traversed.
//
int Maze::num_options() {
  int options = 0;

  if( down_possible() ) options++;
  if( right_possible() ) options++;
  if( left_possible() ) options++;
  if( up_possible() ) options++;

  return options;
}

//
// revert_options
// Pop back to the last location that options were available.
// While popping back, set asterisks to dashes.
//
void Maze::revert_options( Stack *current, Stack *options ) {
  cout << cords.row << " - " << cords.col << endl;

  // maze[cords.row][cords.col] = '-';

  Cords *options_position = (Cords*)pop( options );
  cords = *options_position;

  while( !isEmpty(current) ) {
    Cords *back_once = (Cords*)pop(current);
    // cords = *back_once;

    cout << "   Back: " << back_once->row << "  " << back_once->col << endl;
    cout << "Options: " << options_position->row << "  " << options_position->col << endl;
    maze[back_once->row][back_once->col] = '-';

    if( back_once->row == options_position->row
      && back_once->col == options_position->col ) {
      cout << "breaking..." << endl;
      break;
    }

  }

}

//
// is_edge
// Return whether the current position is a edge of the maze.
//
bool Maze::is_edge() {
  bool row_edge = (cords.row == 0 || cords.row == num_rows);
  // bool (cords.row >= 0 && cords.row <= num_rows) );

  bool col_edge = (cords.col == 0 || cords.col == num_cols);
  // bool (cords.col >= 0 && cords.col <= num_cols) );

  return row_edge || col_edge;
}

//
// is_exit
// Return whether the current position of the maze is the exit.
//
bool Maze::is_exit() {
  cout << "IS EXIT" << endl;
  cout << maze[cords.row][cords.col] << endl;

  // if( is_edge() && maze[cords.row][cords.col] == PATH_TAKEN ) {
  if( is_edge() && is_path(maze[cords.row][cords.col]) ) {
    return true;
  }

  // Otherwise, is not the maze exit
  return false;
}

//
// is_wall
// Return whether the given character is a wall.
//
bool is_wall( char c ) {
  for( int i = 0; WALL[i] != '\0'; i++ ) {
    if(c == WALL[i]) {
      return true;
    }
  }

  // Otherwise, char is not wall
  return false;
}

//
// is_path
// Return whether the given character is a path.
//
bool is_path( char c ) {
  return c == PATH ? true : false;
}

//
// print_maze
// Print completed maze.
//
void print_maze( Maze *m) {
  for( int row = 0; row < m->num_rows; row++ ) {
    cout << m->maze[row] << endl;
  }
}

