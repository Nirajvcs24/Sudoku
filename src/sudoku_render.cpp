#include "raylib.h"
#include "sudoku.h"

//Function for drawing all the grid lines for the board;
void DrawLines(Vector2 offset, float cellSize){
    float boardSize = cellSize * 9;

    for(int i = 0 ; i <= 9 ; i++){
        float lineThickness = (i % 3 == 0) ? 3.0f : 1.0f;
        Color lineColour = (i % 3 == 0) ? BLACK : DARKGRAY;

        //void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);
        DrawLineEx((Vector2){offset.x + i * cellSize, offset.y},(Vector2){offset.x + i * cellSize , offset.y + boardSize} , lineThickness , lineColour );
        DrawLineEx((Vector2){offset.x , offset.y + i * cellSize}, (Vector2){offset.x + boardSize , offset.y + i * cellSize} , lineThickness , lineColour);
    }
}

void DrawBoard(SudokuGame *game, Vector2 gridOffset , float cellSize , Font font){
    DrawLines(gridOffset,cellSize);
}

