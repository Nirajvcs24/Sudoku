#include "raylib.h"
#include "sudoku.h"

#define windowHeightSize 800
#define windowWidthSize 800

int main(void)
{
    InitWindow(windowHeightSize, windowWidthSize, "Sudoku");

    SetTargetFPS(60);

    //Not Working
    /*Image icon = LoadImage("Sudoku_Image.jpeg");
    SetWindowIcon(icon);
    UnloadImage(icon);*/


    Vector2 gridOffset = {175.0f , 120.0f};
    float cellSize = 50.0f;
    SudokuGame game;
    InitGame(&game);


    while (!WindowShouldClose())    
    {

        UpdateGame(&game,gridOffset,cellSize);

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawBoard(&game,gridOffset,cellSize,GetFontDefault());

        EndDrawing();
    }

    CloseWindow();

    return 0;
}