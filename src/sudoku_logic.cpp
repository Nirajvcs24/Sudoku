#include "raylib.h"
#include "sudoku.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

//Initializing the game.
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
    //Test - To be removed later.
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
    //IF condition checks whether mouse has been clicked inside the GRID.
    //If clicked inside it calculates the row and column that it has been clicked in.
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
    //Checks if a Row and Column has been selected.
    if(game->selectedRow != -1 && game->selectedColumn !=-1){
        Cell *selectedCell = &game->board[game->selectedRow][game->selectedColumn];
        if(!selectedCell->isGiven){ //Checking if the number is present or not.
            int key = GetKeyPressed();
            if(key >= KEY_ONE && key <= KEY_NINE){ //Making sure the clicked number is between 1 and 9.
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


//The name is temporary, needs to be changed.
//need to change the arguments from game to the answer array so the answer array can store the solution.
//Then compare the answer array with the entered numbers.
//Still need to implement a way to randomize the .isgiven part.
//One method im thinking is to use a random number generator to generate how many numbers are generated.
//then randomize the the row and column, everytime it picks i reduce the number.
void IdkWhatToCallYet(SudokuGame *game){
    //Implementing DiagonalBoxSeeding method to build a solution.
    //In this method the diagonal 3x3 boxes are filled with numbers randomly from 1-9.
    //A solution is then built on this fundamental and stored in an array which then later is used to compare.

    vector<int> numbers(9);
    iota(numbers.begin(),numbers.end(),1);


    int startRow, startCol;

    //Initializing the random shuffler.
    std::random_device rd;
    std::mt19937 g(rd());

    //For the first Box
    startRow = (0 * 3)/3;
    startCol = (0 * 3)/3;
    
    int i = 0;

    shuffle(numbers.begin(), numbers.end(), g);

    for(int r=startRow ; r < startRow + 3 ; r++){
        for(int c = startCol ; c < startCol + 3 ; c++){
            game->board[r][c].value = numbers[i++];
        }
    }


    //Second Box
    startRow = (3 * 3)/3;
    startCol = (3 * 3)/3;

    i = 0;
    shuffle(numbers.begin(), numbers.end(), g);

    for(int r=startRow ; r < startRow + 3 ; r++){
        for(int c = startCol ; c < startCol + 3 ; c++){
            game->board[r][c].value = numbers[i++];
        }
    }

    //Third Box
    startRow = (6 * 3)/3;
    startCol = (6 * 3)/3;

    i = 0;
    shuffle(numbers.begin(), numbers.end(), g);

    for(int r=startRow ; r < startRow + 3 ; r++){
        for(int c = startCol ; c < startCol + 3 ; c++){
            game->board[r][c].value = numbers[i++];
        }
    }
}