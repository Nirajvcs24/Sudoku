#pragma once

#ifndef SUDOKU_H
#define SUDOKU_H

#include "raylib.h"
#include <stdbool.h>

typedef struct{
    int value;
    int solution;
    bool isGiven;
    bool isError;
}Cell;

typedef struct{
    Cell board[9][9];
    int selectedRow;
    int selectedColumn;
    bool isComplete;
    float timer;
}SudokuGame;

//Sudoku_Logic
void InitGame(SudokuGame *game);
bool GetCellFromMouse(Vector2 mousePos , Vector2 gridOffset, float cellSize , int *outRow, int *outCol);
void HandleInput(SudokuGame *game, Vector2 gridOffset, float cellSize);
bool IsValidPlacement(SudokuGame *game, int row , int col , int number);
void UpdateGame(SudokuGame *game, Vector2 gridOffset , float cellSize);

//Drawing the Board
void DrawLines(Vector2 gridOffset, float cellSize);
void DrawBoard(SudokuGame *game, Vector2 gridOffset, float cellSize, Font font);

#endif