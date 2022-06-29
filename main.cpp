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

    // Where width = 10, the first row of cells is indexed by the following sequence
    // {11, 12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,20}
    return y * GRID_WIDTH + x;
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
    // Creates a 'hole' (replaces '#' with ' '),
    // Linking the previous postion to the current one
    grid[XYToIndex(x, y)] = ' ';

    // Create a local array with the four cardinal directions
    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;

    // Shuffles the order directions order
    for (int i = 0; i < 4; i++)
    {
        /* Using bitwise and ('&')
           Given 10  = 1010
           And   3   = 0011
           3 & 10    = 0010
           0000 0010 = 2

           In general, n & m yields m + 1 values
           n & 3 = {0, 1, 2, 3}

           Compare to n mod m, where the solution set has exactly m members
           Ex n % 3 = {0, 1, 2}
           m itself is excluded

           Note: (n % m) + dx still has m members
        */
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }

    // Loop through each direction and attempt to visit each
    for (int i = 0; i < 4; i++)
    {
        // Rebind offset
        int dx = 0, dy = 0;

        // Set offset for a given direction
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

        /* Find the X,Y coordinates of the cell 2 spots
           Away from the given direction

           The left shift here is for concision
           Where 1 = 0001, 1 << 1 = 0010 = 2

           Bits are shifted to the left by 1
           The bit for sign is unaffected
           For example, -1 << 1 = -2
           Thus this avoids branching

           Generally, n << m shifts n's bits to the left m positions
        */
        int x2 = x + (dx << 1);
        int y2 = y + (dy << 1);

        if (IsInBounds(x2, y2))
        {
            // If the cell 2 positions away
            if (grid[XYToIndex(x2, y2)] == '#')
            {
                /* Knock down the wall between my current position
                   And the position 2 cells away

                   Before:       After:
                   #####         #####
                   # ###    =>   #  ##
                   #####         #####
                */
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