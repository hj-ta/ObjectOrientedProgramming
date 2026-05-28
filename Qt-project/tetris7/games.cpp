#include "games.h"

Game::Game(int row, int col, int length)
{
    ROW = row;
    COL = col;
    LENGTH = length;

    board = new string*[ROW];
    for (int i = 0; i < ROW; i++)
        board[i] = new string[COL];

    next = new string[length];

    gameover = false;
}

Game::~Game()
{
    delete[] next;

    for (int i = 0; i < ROW; i++)
        delete[] board[i];
    delete[] board;
}

PuyopuyoGame::PuyopuyoGame() : Game(12, 6, 2)
{
    next[0] = "RR"; //Red Red
    next[1] = "YY"; //Yellow Yellow

    for(int i = 0; i < ROW; i++)
        for(int j =0; j < COL; j++)
            board[i][j] = "White";

    board[11][0] = "Red";
    board[11][1] = "Red";
    board[11][2] = "Red";

    board[10][1] = "Yellow";
    board[10][2] = "Yellow";
    board[11][3] = "Yellow";

    board[9][2] = "Green";
    board[10][3] = "Green";
    board[11][4] = "Green";

    board[9][3] = "Blue";
    board[10][4] = "Blue";
    board[11][5] = "Blue";

    board[9][4] = "Purple";
    board[10][5] = "Purple";

    board[2][1] = "Green";
    board[2][2] = "Green";

    axis_row = 2;
    axis_col = 1;

    score = 0;
}

PuyopuyoGame::~PuyopuyoGame()
{
    ;
}

TetrisGame::TetrisGame() : Game(20, 10, 5)
{
    next[0] = "T";
    next[1] = "I";
    next[2] = "S";
    next[3] = "Z";
    next[4] = "O";

    for(int i = 0; i < ROW; i++)
        for(int j =0; j < COL; j++)
            board[i][j] = "White";

    board[19][0] = "Gray";
    board[19][1] = "Gray";
    board[19][2] = "Gray";
    board[19][3] = "Gray";

    board[18][0] = "Gray";
    board[18][1] = "Gray";
    board[18][2] = "Gray";
    board[18][3] = "Gray";

    board[17][2] = "Gray";
    board[17][3] = "Gray";
    board[17][4] = "Gray";
    board[18][4] = "Gray";

    board[16][3] = "Gray";
    board[16][4] = "Gray";
    board[16][5] = "Gray";
    board[17][5] = "Gray";

    board[15][5] = "Gray";
    board[15][6] = "Gray";
    board[16][6] = "Gray";
    board[16][7] = "Gray";

    board[14][6] = "Gray";
    board[14][7] = "Gray";
    board[15][7] = "Gray";
    board[15][8] = "Gray";

    board[13][8] = "Gray";
    board[13][9] = "Gray";
    board[14][8] = "Gray";
    board[14][9] = "Gray";

    board[11][8] = "Gray";
    board[11][9] = "Gray";
    board[12][8] = "Gray";
    board[12][9] = "Gray";

    board[2][1] = "Gray";
    board[2][2] = "Gray";
    board[2][3] = "Gray";
    board[2][4] = "Gray";

    axis_row = 2.5;
    axis_col = 2.5;

    score = 1;
}

TetrisGame::~TetrisGame()
{
    ;
}

PuyopuyoTetrisGame::PuyopuyoTetrisGame() : Game(16, 8, 5)
{
    next[0] = "RY"; //Red Yellow
    next[1] = "GB"; //Green Blue
    next[2] = "PP"; //Purple Purple
    next[3] = "L";
    next[4] = "J";

    for(int i = 0; i < ROW; i++)
        for(int j =0; j < COL; j++)
            board[i][j] = "White";

    board[15][0] = "Gray";
    board[15][1] = "Gray";
    board[15][2] = "Gray";
    board[15][3] = "Gray";

    board[14][0] = "Gray";
    board[14][1] = "Gray";
    board[14][2] = "Gray";
    board[14][3] = "Gray";

    board[13][2] = "Gray";
    board[13][3] = "Gray";
    board[13][4] = "Gray";
    board[14][4] = "Gray";

    board[12][3] = "Gray";
    board[12][4] = "Gray";
    board[12][5] = "Gray";
    board[13][5] = "Gray";

    board[11][5] = "Gray";
    board[11][6] = "Gray";
    board[12][6] = "Gray";
    board[12][7] = "Gray";

    board[13][0] = "Red";
    board[13][1] = "Red";
    board[12][2] = "Red";

    board[12][1] = "Yellow";
    board[11][2] = "Yellow";
    board[11][3] = "Yellow";

    board[10][2] = "Green";
    board[10][3] = "Green";
    board[11][4] = "Green";

    board[9][3] = "Blue";
    board[10][4] = "Blue";
    board[10][5] = "Blue";

    board[9][4] = "Purple";
    board[9][5] = "Purple";
    board[10][6] = "Purple";

    board[2][6] = "Green";
    board[2][5] = "Green";

    axis_row = 2;
    axis_col = 6;

    score = 2;
}

PuyopuyoTetrisGame::~PuyopuyoTetrisGame()
{
    ;
}
