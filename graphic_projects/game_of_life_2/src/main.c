#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define ROWS 100
#define COLS 100

const unsigned int screenWidth = 800;
const unsigned int screenHeight = 800;

const unsigned int row_side = (int) screenHeight/ROWS;
const unsigned int col_side = (int) screenWidth/COLS;

unsigned int state[ROWS][COLS];
unsigned int aux_state[ROWS][COLS];

void first_state_init(int);
void draw_state(void);
void update_state(void);
unsigned int count_cell_alive_neighbours(int, int);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    unsigned long frame = 0;

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(10);             
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // ----------------------------------------------------------------------------------
        if (frame)
            update_state();
        else
            first_state_init(30);
            memcpy(state, aux_state, sizeof(int)*ROWS*COLS);
        ++frame;

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_state();

            DrawFPS(0, 0);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void first_state_init(int prob)
{
    int i, j, r;
    //srand: the pseudo-random number generator is initialized using the argument passed as seed.
    //time: the function returns the current calendar time as a value of type time_t,
    //and if the argument is not a null pointer, it also sets this value to the object pointed by timer.
    srand(time(NULL));

    for (i=0; i<ROWS; ++i)
    {
        for(j=0; j<COLS; ++j)
        {
            r = rand() % 100;
            if (r < prob)
                state[i][j] = 1;
            else
                state[i][j] = 0;
        }
    }
}

void draw_state(void)
{
    int i, j;
    for (i=0; i<ROWS; i++)
    {
        for(j=0; j<COLS; j++)
        {
            if (state[i][j])
                DrawRectangle(i*row_side, j*col_side, row_side, col_side, BLACK);
            else
                DrawRectangle(i*row_side, j*col_side, row_side, col_side, DARKGRAY);
        }
    }
}

unsigned int count_cell_alive_neighbours(int row, int col)
{
    int i, j, neigh_row, neigh_col;
    int pluses[3] = {-1, 0, 1};
    unsigned int counter;

    counter = 0;
    for (i=0; i<3; ++i)
    {
        for (j=0; j<3; ++j)
        {
            neigh_row = row + pluses[i];
            neigh_col = col + pluses[j];
            if (neigh_row>0 && neigh_row<ROWS && neigh_col>0 && neigh_col<COLS)
                counter += state[neigh_row][neigh_col];
        }
    } 

    // the previous alg will consider the cell a neighbour of itself,
    // by checking outside loop I only check once
    if (state[row][col])
        --counter;
    return counter;
}

// updates the state of the board one step
// the update is performed on the aux state array first to avoid intra-update inteference
// and then copied to the state array
void update_state(void) 
{
    int i, j;
    unsigned int alive_neighbours;

    for (i=0; i<ROWS; ++i)
    {
        for(j=0; j<COLS; ++j)
        {
            alive_neighbours = count_cell_alive_neighbours(i, j);
            if (state[i][j]) //cell is alive
            {
                if (alive_neighbours < 2)
                    aux_state[i][j] = 0; //dies by underpopulation
                else if (alive_neighbours <= 3)
                    aux_state[i][j] = 1; //lives on (might be redundant if state is kept consistent)
                else                     // if >3 alive neighbours
                    aux_state[i][j] = 0; //dies by overpopulation
            }
            else            //cell is dead
            {
                if (alive_neighbours == 3)
                    aux_state[i][j] = 1; //brought to life by reproduction
                else
                    aux_state[i][j] = 0; //keeps being dead (might be redundant if state is kept consistent)
            }
        }
    }

    // copy aux state into state
    memcpy(state, aux_state, sizeof(int)*ROWS*COLS);
}
