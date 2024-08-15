#include "raylib.h"
#include <stdio.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic program input");

    int ballRadius = 50;
    Vector2 ballPosition = { (float) screenWidth/2.0f, (float) screenHeight/2.0f};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_LEFT_SHIFT)) ballPosition = GetMousePosition();
        else {
            if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
            if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
            if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
            if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
        }
        ballRadius += GetMouseWheelMove();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
            DrawText("force the ball to follow mouse by keeping left shift pressed", 10, 30, 20, DARKGRAY);
            DrawText("resize the ball by scrolling up and down", 10, 50, 20, DARKGRAY);

            DrawCircleV(ballPosition, ballRadius, MAGENTA);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}