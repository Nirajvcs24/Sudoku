#include "raylib.h"
#include "sudoku.h"

void InitGame(SudokuGame *game){
    game->selectedRow = -1;
    game->selectedColumn = -1;
    game->timer = 0.0f;
    game->isComplete = false;
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            game->board[r][c].value = -1;
            game->board[r][c].isError = false;
            game->board[r][c].isGiven = false;
        }
    }
}

bool GetCellFromMouse(Vector2 mousePos , Vector2 gridOffset , float cellSize , int *outRow , int *outCol){
    int boardSize = cellSize * 9;
    if(mousePos.x >= gridOffset.x && mousePos.x < gridOffset.x + boardSize && mousePos.y >=gridOffset.y && mousePos.y < gridOffset.y + boardSize){
        *outRow = (int)((mousePos.x - gridOffset.x)/cellSize);
        *outCol = (int)((mousePos.y - gridOffset.y)/cellSize);
        return true;
    }
    return false;
}

void HandleInput(SudokuGame *game, Vector2 gridOffset , float cellSize){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        Vector2 mousePos = GetMousePosition();
        if(!GetCellFromMouse(mousePos, gridOffset, cellSize, &game->selectedRow , &game->selectedColumn)){
            game->selectedRow = -1;
            game->selectedColumn = -1;
        }
    }

    if(game->selectedRow != -1 && game->selectedColumn !=-1){
        Cell *selectedCell = &game->board[game->selectedRow][game->selectedColumn];
        if(!selectedCell->isGiven){
            int key = GetKeyPressed();
            if(key >= KEY_ONE && key <= KEY_NINE){
                selectedCell->value = key - KEY_ONE + 1;
            }
            else if(key == KEY_BACKSPACE || key == KEY_DELETE){
                selectedCell->value = 0;
            }
        }
    }
}

void UpdateGame(SudokuGame *game, Vector2 gridOffset , float cellSize){
    if(game->isComplete)    return;
    game->timer += GetFrameTime();
    HandleInput(game,gridOffset,cellSize);
}