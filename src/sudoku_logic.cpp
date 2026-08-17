#include "raylib.h"
#include "sudoku.h"
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>

void InitGame(SudokuGame *game){
    game->selectedRow = -1;
    game->selectedColumn = -1;
    game->timer = 0.0f;
    game->isComplete = false;
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            game->board[r][c].value = 0;
            game->board[r][c].isError = false;
            game->board[r][c].isGiven = false;
        }
    }
    IdkWhatToCallYet(game);
}

bool IsValidPlacement(SudokuGame *game, int row , int col , int number){
    if(number == 0) return true;

    //Checks if the number is present in the column
    for(int c = 0 ; c < 9 ; c++){
        if(c != col && game->board[row][c].value == number)
            return false;
    }

    //Checks if the number is present in the row
    for(int r = 0 ; r < 9 ; r++){
        if(r != row && game->board[r][col].value == number)
            return false;
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    //Checks the 3X3 block.
    for(int r = startRow ; r < startRow + 3 ; r++){
        for(int c = startCol ; c < startCol + 3 ; c++){
            if((r != row || c != col) && game->board[r][c].value == number)
                return false;
        }
    }
    return true;
}

bool GetCellFromMouse(Vector2 mousePos , Vector2 gridOffset , float cellSize , int *outRow , int *outCol){
    int boardSize = cellSize * 9;
    if(mousePos.x >= gridOffset.x && mousePos.x < gridOffset.x + boardSize && 
        mousePos.y >=gridOffset.y && mousePos.y < gridOffset.y + boardSize){
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
                if(!IsValidPlacement(game , game->selectedRow , game->selectedColumn , selectedCell->value)){
                    selectedCell->isError = true;
                }
                else
                    selectedCell->isError = false;
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

void IdkWhatToCallYet(SudokuGame *game){
    //Using multiple loops to make it completely random instead of the same configuration for each diagonal 3x3 box
    //Works mostly, need to find a way to fill all the boxes.
    //Problem is that the same number is generating hence skipping few cells.
    //One fix can be that we can loop through 1 to 9 and randomize the row and cell.
    //Didnt Work.
    int startRow, startCol,element;
    //For the first Box
    startRow = (0 * 3)/3;
    startCol = (0 * 3)/3;

    std::vector<int> numbers;

    for(int r=startRow ; r < startRow + 3 ; r++){
        for(int c = startCol ; c < startCol + 3 ; c++){
            element = (rand() % 10) + 1;
            if(IsValidPlacement(game, r , c , element) && element != 0)
                game->board[r][c].value = element;
        }
    }


    //Second Box
    startRow = (3 * 3)/3;
    startCol = (3 * 3)/3;

    for(int r=startRow ; r < startRow + 3 ; r++){
        for(int c = startCol ; c < startCol + 3 ; c++){
            element = (rand() % 10) + 1;
            if(IsValidPlacement(game, r , c , element))
                game->board[r][c].value = element;
        }
    }

    //Third Box
    startRow = (6 * 3)/3;
    startCol = (6 * 3)/3;

    for(int r=startRow ; r < startRow + 3 ; r++){
        for(int c = startCol ; c < startCol + 3 ; c++){
            element = (rand() % 10) + 1;
            if(IsValidPlacement(game, r , c , element))
                game->board[r][c].value = element;
        }
    }
}


