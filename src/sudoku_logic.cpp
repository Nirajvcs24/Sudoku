#include "raylib.h"
#include "sudoku.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

using namespace std;

int answer[9][9];

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
    SolveSudoku(game);
    TempFunc(game);
    //PlaceGivenNumbers(game);
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
    if(IsKeyPressed(KEY_SPACE)){
        if(SolveSudoku(game))
            game->isComplete = true;
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

//Used for finding an Empty cell for the Backtracking Function.
bool FindEmptyCell(SudokuGame *game, int *outRow, int *outCol){
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            if(game->board[r][c].value == 0){
                *outRow = r;
                *outCol = c;
                return true;
            }
        }
    }
    return false;
}


//This is the Backtracking function.
bool SolveSudoku(SudokuGame *game){
    int row , col;
    //Finds if there is an empty cell. If no returns true.
    //BASE CASE
    if(!FindEmptyCell(game, &row, &col))
        return true;
    //Iterates through the number 1 to 9 and checking if the number fits there.
    //If not it backtracks and checks with a different number.
    for(int num = 1 ; num <= 9 ; num++){
        if(IsValidPlacement(game,row,col,num)){
            game->board[row][col].value = num;

        if(SolveSudoku(game))
            return true;
        //This is resetting the value to 0 in case it fails.
        game->board[row][col].value = 0;
        }
    }
    //Triggers backtracking.
    return false;
}

//Temporary Name for this function
/*void PlaceGivenNumbers(SudokuGame *game){
    int numberOfGiven = 17 + (rand() % 15);
    int row,col;
    while(numberOfGiven > 0){
        row = rand() % 9;
        col = rand() % 9;
        if(!game->board[row][col].isGiven){
            game->board[row][col].isGiven = true;
            numberOfGiven--;
        }
    } 
}*/

void TempFunc(SudokuGame *game){
    int MaxNumToRemove = 35 + (rand() % 15);
    int row,col;
    while(MaxNumToRemove > 0){
        row = rand() % 9;
        col = rand() % 9;
        if(game->board[row][col].value != 0){
            game->board[row][col].value = 0;
            answer[row][col] = 0;
        }
        MaxNumToRemove--;
    }

    //Make remaining given;
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            if(game->board[r][c].value != 0)
                game->board[r][c].isGiven = true;
        }
    }
}