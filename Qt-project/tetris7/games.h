#ifndef GAMES_H
#define GAMES_H

#include <string>
using namespace std;

class Game
{
public:
    Game(int row, int col, int length);
    ~Game();

public:
    int ROW;
    int COL;
    int LENGTH;

    double axis_row;
    double axis_col;

    int score;

    bool gameover;

    string** board;
    string* next;
};

class PuyopuyoGame : public Game
{
public:
    PuyopuyoGame();
    ~PuyopuyoGame();
};

class TetrisGame : public Game
{
public:
    TetrisGame();
    ~TetrisGame();
};

class PuyopuyoTetrisGame : public Game
{
public:
    PuyopuyoTetrisGame();
    ~PuyopuyoTetrisGame();
};


#endif // GAMES_H
