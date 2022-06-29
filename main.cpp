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
const int GRID_HEIGHT = 23;
const int GRID_WIDTH = 79;

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
//----Global Variables--------------------------------------------------------
char grid[GRID_HEIGHT * GRID_WIDTH];

//----Prototypes--------------------------------------------------------------
void ResetGrid();
int XYToIndex(int x, int y);
bool IsInBounds(int x, int y);
void Visit(int x, int y);
void PrintGrid();
void Format();

//----Functions---------------------------------------------------------------
int main()
{
    Format();
    cout << "Description: A simple recursive maze generator in C++" << endl;
    Format();

    srand(time(0)); // Seed random number generator
    ResetGrid();    // Clears the grid
    Visit(1, 1);
    PrintGrid();

    return 0;
}

// Prints a line to the console for seperation
void Format()
{
    cout << setw(79) << setfill('-') << " " << endl;
}

void ResetGrid()
{
    // Fills grid with '#' characters
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        grid[i] = '#';
    }
}

int XYToIndex(int x, int y)
{
    // Converts two dimensional coordinates to one dimensional index
    // y * ROW WIDTH + x
    return y * GRID_WIDTH + x; // ? Come back to this. Why does it work?
}

bool IsInBounds(int x, int y)
{
    const bool IN_BOUNDS = true;
    const bool NOT_IN_BOUNDS = false;

    if (x < 0 || x >= GRID_WIDTH)
    {
        return NOT_IN_BOUNDS;
    }

    if (y < 0 || y >= GRID_HEIGHT)
    {
        return NOT_IN_BOUNDS;
    }

    return IN_BOUNDS;
}

void Visit(int x, int y)
{
    // Start from a given random index
    grid[XYToIndex(x, y)] = ' '; // ! creates a "hole" in the grid

    // Create a local array with the four cardinal directions
    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;

    // Shuffles the order directions order
    for (int i = 0; i < 4; i++)
    {
        int r = rand() & 3; // ? What is the ampersand doing here
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }

    // Loop through each direction and attempt to visit each
    for (int i = 0; i < 4; i++)
    {
        int dx = 0, dy = 0;

        switch (dirs[i])
        {
        case NORTH:
            dy = -1;
            break;
        case SOUTH:
            dy = 1;
            break;
        case EAST:
            dx = 1;
            break;
        case WEST:
            dx = -1;
            break;
        }

        // Find the X,Y coordinates of the cell 2 spots
        // Away from the given direction
        int x2 = x + (dx << 1); // ? What's the shift here for?
        int y2 = y + (dy << 1);

        if (IsInBounds(x2, y2))
        {
            // If there's a wall in the adjacent cell
            if (grid[XYToIndex(x2, y2)] == '#')
            {
                // Knock down the wall between my current position
                // And that position
                grid[XYToIndex(x2 - dx, y2 - dy)] = ' ';

                // Recursively visit
                Visit(x2, y2);
            }
        }
    }
}

void PrintGrid()
{
    // Displays the final grid
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            cout << grid[XYToIndex(x, y)];
        }
        cout << endl;
    }
}