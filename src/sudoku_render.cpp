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

void DrawCellHighlights(const SudokuGame *game, Vector2 offset , float cellSize){
    //void DrawRectangle(int posX, int posY, int width, int height, Color color);
    if(game->selectedRow != -1 && game->selectedColumn != -1){
        DrawRectangle(
            (int)(offset.x + (cellSize * game->selectedRow)),
            (int)(offset.y + (cellSize * game->selectedColumn)),
            (int)cellSize,
            (int)cellSize,
            LIGHTGRAY
        );
    }
}

void DrawCellNumbers(const SudokuGame *game, Vector2 offset, float cellSize, Font font){
    int fontSize = (int)(cellSize * 0.6f);
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            Cell cell = game->board[r][c];

            if(cell.value < 1 || cell.value > 9) continue;
            Color textColor = BLUE;
            if(cell.isError)
                textColor = RED;
            else if(cell.isGiven)
                textColor = BLACK;
            
            float cellX = (offset.x + ((r + 0.7) * cellSize));
            float cellY = (offset.y + ((c + 0.5) * cellSize));

            char numStr[2] = { (char)('0' + cell.value), '\0' };

            int textWidth = MeasureText(numStr, fontSize);
            float textX = cellX + (textWidth - cellSize) / 2.0f;
            float textY = cellY + (textWidth - fontSize) / 2.0f;
            //void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
            DrawText(numStr , textX , textY , fontSize , textColor);
        }
    }
}



//Main Function for Drawing all the lines.
void DrawBoard(SudokuGame *game, Vector2 gridOffset , float cellSize , Font font){
    DrawCellHighlights(game,gridOffset,cellSize);
    DrawLines(gridOffset,cellSize);
    DrawCellNumbers(game, gridOffset , cellSize, GetFontDefault());
}

