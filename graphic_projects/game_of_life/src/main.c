#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define ROWS 100
#define COLS 100

#define ALIVE_COLOR WHITE
#define INERT_COLOR DARKBLUE

#define DELTA 5

const unsigned int border = 75;

const unsigned int screenWidth = 700 + 2*border;
const unsigned int screenHeight = 700 + 2*border;

const unsigned int row_side = (int) (screenHeight - 2*border)/ROWS;
const unsigned int col_side = (int) (screenWidth - 2*border)/COLS;

// array holding the cells information
unsigned int state[ROWS][COLS];
// auxiliar array used to update the state at each step
unsigned int aux_state[ROWS][COLS];

void first_state_init(int);
void draw_state(void);
void draw_title(void);
void draw_fps_info(int, bool);
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
    unsigned int target_pseudo_fps = 3;
    unsigned int loop_fps = 30;
    double last_frame_time = GetTime();
    double time_btw_frames = (double) 1.0f / target_pseudo_fps;
    bool paused = true;

    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags

    InitWindow(screenWidth, screenHeight, "Game of Life");

    // the actual FPS should not be messed with
    // as it relates directly with the execution of the loop
    // the approach of updating the state only on certain frame numbers make the UI much swifter
    SetTargetFPS(loop_fps);           
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // ----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_P))
            paused = !paused;

        if (IsKeyPressed(KEY_LEFT))
        {
            --target_pseudo_fps;
            if (target_pseudo_fps <= 0)
                target_pseudo_fps = 1;
            time_btw_frames = (double) 1.0f / target_pseudo_fps;
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            ++target_pseudo_fps;
            if (target_pseudo_fps >= 60)
                target_pseudo_fps = 60;
            time_btw_frames = (double) 1.0f / target_pseudo_fps;
        }
        
        if (frame)
        {
            if (!paused)
                if (GetTime()-last_frame_time >= time_btw_frames)
                {
                    update_state();
                    last_frame_time = GetTime();
                }
        }
        else
            first_state_init(50);
            memcpy(aux_state, state, sizeof(int)*ROWS*COLS);
        
        if (paused && IsKeyPressed(KEY_N))
            update_state();

        ++frame;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(INERT_COLOR);

            //draw border around cells
            DrawRectangleLines(border-DELTA, border-DELTA, ROWS*row_side+DELTA*2, COLS*col_side+DELTA*2, ALIVE_COLOR);

            draw_state();

            draw_fps_info(target_pseudo_fps, paused);

            draw_title();


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
                DrawRectangle(i*row_side + border, j*col_side + border, row_side, col_side, ALIVE_COLOR);
            else
                DrawRectangle(i*row_side + border, j*col_side + border, row_side, col_side, INERT_COLOR);
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
                if (alive_neighbours < 2 || alive_neighbours > 3)
                    aux_state[i][j] = 0; //dies by underpopulation or overpopulation
            }
            else            //cell is dead
            {
                if (alive_neighbours == 3)
                    aux_state[i][j] = 1; //brought to life by reproduction
            }
        }
    }

    // copy aux state into state
    memcpy(state, aux_state, sizeof(int)*ROWS*COLS);
}

void draw_title(void)
{
    char* title = "GAME OF LIFE v0.1";
    int fontsize = 40;
    DrawText(title, screenWidth/2 - MeasureText(title, fontsize)/2, 20, fontsize, ALIVE_COLOR);
}

void draw_fps_info(int target_fps, bool paused)
{
    int info_font_size = 20;
    
    int current_fps = GetFPS();

    char str[256];
    snprintf(str, sizeof str, "Current FPS: %d", current_fps);
    DrawText(str, DELTA*2, screenHeight-DELTA*11, info_font_size, ALIVE_COLOR);

    if (paused)
        snprintf(str, sizeof str, "Target FPS: PAUSED \t(press 'P' to resume; press 'N' to perform a single step)");
    else
        snprintf(str, sizeof str, "Target FPS: %d\t(use left/right arrow keys to modify; press 'P' to pause)", target_fps);
    DrawText(str, DELTA*2, screenHeight-DELTA*6, info_font_size, ALIVE_COLOR);
}