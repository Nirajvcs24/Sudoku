#pragma once

#ifndef SUDOKU_H
#define SUDOKU_H

#include "raylib.h"
#include <stdbool.h>
#include<time.h>
#include<stdlib.h>

//defining all the variables for each cell.
typedef struct{
    int value;
    int solution;
    bool isGiven;
    bool isError;
}Cell;

//defining all the variables required for the board;
typedef struct{
    Cell board[9][9];
    int selectedRow;
    int selectedColumn;
    bool isComplete;
    float timer;
}SudokuGame;

//int answer[9][9];

//Sudoku_Logic
void InitGame(SudokuGame *game);
bool GetCellFromMouse(Vector2 mousePos , Vector2 gridOffset, float cellSize , int *outRow, int *outCol);
void HandleInput(SudokuGame *game, Vector2 gridOffset, float cellSize);
bool IsValidPlacement(SudokuGame *game, int row , int col , int number);
void UpdateGame(SudokuGame *game, Vector2 gridOffset , float cellSize);
void IdkWhatToCallYet(SudokuGame *game);
bool FindEmptyCell(SudokuGame *game, int *outRow, int *outColumn);
bool SolveSudoku(SudokuGame *game);
void PlaceGivenNumbers(SudokuGame *game);
void TempFunc(SudokuGame *game);


//Drawing the Board
void DrawLines(Vector2 gridOffset, float cellSize);
void DrawCellHighlights(const SudokuGame *game, Vector2 offset , float cellSize);
void DrawCellNumbers(const SudokuGame *game, Vector2 offset, float cellSize, Font font);
void DrawBoard(SudokuGame *game, Vector2 gridOffset, float cellSize, Font font);

#endif