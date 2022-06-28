//----------------------------------------------------------------------------
// Maze Generator
// Cullen Sharp
//
// A recursive maze generator
//
// History
// Created:         06.28.22
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
using namespace std;

//----Constants---------------------------------------------------------------
const int GRID_HEIGHT = 79;
const int GRID_WIDTH  = 79;

const int NORTH = 0;
const int EAST  = 1;
const int WEST  = 2;
const int SOUTH = 3;
//----------------------------------------------------------------------------

//----Prototypes--------------------------------------------------------------
void format();



//----------------------------------------------------------------------------

//----Function Definitions----------------------------------------------------

// Prints a line to the console for seperation
void format() {
    cout << setw(79) << setfill('-') << " " << endl;
}

//----------------------------------------------------------------------------
int main() {
    format();
    cout << "Description: A simple recursive maze generator in C++" << endl;
    format();

    return 0;
}
