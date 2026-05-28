#include "TetrisGame.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <QTimer>
using namespace std;

TetrisGame::TetrisGame()
{
    rows = 22;
    cols = 10;
    currentRow = 0;
    currentCol = cols / 2;
    score = 0;
    isGameOver = false;
    board.resize(rows, vector<string>(cols, "Empty"));
    boardColors.resize(rows, vector<QColor>(cols, QColor(255, 255, 255)));
    srand(time(0));

    shapes = {
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1},
         {1, 1}},
        {{0, 1, 0},
         {1, 1, 1},
         {0, 0, 0}},
        {{0, 1, 1},
         {1, 1, 0},
         {0, 0, 0}},
        {{1, 1, 0},
         {0, 1, 1},
         {0, 0, 0}},
        {{1, 0, 0},
         {1, 1, 1},
         {0, 0, 0}},
        {{0, 0, 1},
         {1, 1, 1},
         {0, 0, 0}}
    };

    shapeColors = {
        QColor(0, 255, 255), // I shape - Cyan
        QColor(255, 255, 0), // O shape - Yellow
        QColor(128, 0, 128), // T shape - Purple
        QColor(0, 255, 0),   // S shape - Green
        QColor(255, 0, 0),   // Z shape - Red
        QColor(0, 0, 255),   // J shape - Blue
        QColor(255, 165, 0)  // L shape - Orange
    };

    initializeBoard();
    generateNextShapes();
    spawnNewShape();
}

TetrisGame::~TetrisGame()
{
}

void TetrisGame::initializeBoard()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            board[i][j] = "Empty";
            if (i < 2)
                boardColors[i][j] = QColor(192, 192, 192);
            else
                boardColors[i][j] = QColor(255, 255, 255);
        }
    }
}

int TetrisGame::getRandomShape()
{
    return rand() % shapes.size();
}

void TetrisGame::fixBlock()
{
    QColor color = shapeColors[currentShapeIndex];

    for (int i = 0; i < currentShape.size(); ++i)
    {
        for (int j = 0; j < currentShape[i].size(); ++j)
        {
            if (currentShape[i][j] == 1)
            {
                int row = currentRow + i;
                int col = currentCol + j;
                board[row][col] = "Fix";
                boardColors[row][col] = color;
            }
        }
    }

    if (checkGameOver())
    {
        isGameOver = true;
        emit gameOver();
    }
}

void TetrisGame::clearFullLines()
{
    QVector<int> linesToClear;

    for (int i = 2; i < rows; ++i)
    {
        bool fullLine = true;

        for (int j = 0; j < cols; ++j)
        {
            if (board[i][j] == "Empty")
            {
                fullLine = false;
                break;
            }
        }

        if (fullLine)
        {
            linesToClear.append(i);
        }
    }

    if (linesToClear.isEmpty())
    {
        return;
    }

    emit linesCleared();

    QTimer::singleShot(200, [this, linesToClear]() {
        for (int line : linesToClear)
        {
            for (int k = line; k > 2; --k)
            {
                for (int j = 0; j < cols; ++j)
                {
                    board[k][j] = board[k - 1][j];
                    boardColors[k][j] = boardColors[k - 1][j];
                }
            }
            for (int j = 0; j < cols; ++j)
            {
                board[2][j] = "Empty";
                boardColors[2][j] = QColor(255, 255, 255);
            }
        }

        emit linesCleared();
    });

    score += linesToClear.size();
}

bool TetrisGame::checkGameOver()
{
    for (int j = 0; j < cols; ++j)
    {
        if (board[1][j] != "Empty")
        {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<int>> TetrisGame::getCurrentShape() const
{
    return currentShape;
}

void TetrisGame::rotateCurrentShapeClockwise()
{
    auto rotated = rotateShape(currentShape, true);
    if (canRotate(rotated))
    {
        currentShape = rotated;
    }
}

void TetrisGame::rotateCurrentShapeCounterClockwise()
{
    auto rotated = rotateShape(currentShape, false);
    if (canRotate(rotated))
    {
        currentShape = rotated;
    }
}

std::vector<std::vector<int>> TetrisGame::rotateShape(const std::vector<std::vector<int>>& shape, bool clockwise)
{
    int n = shape.size();
    std::vector<std::vector<int>> rotated(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (clockwise)
            {
                rotated[j][n - i - 1] = shape[i][j];
            }
            else
            {
                rotated[n - j - 1][i] = shape[i][j];
            }
        }
    }
    return rotated;
}

bool TetrisGame::canRotate(const std::vector<std::vector<int>>& rotatedShape) const
{
    int n = rotatedShape.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (rotatedShape[i][j] == 1)
            {
                int newRow = currentRow + i;
                int newCol = currentCol + j;
                if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || board[newRow][newCol] != "Empty")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool TetrisGame::canMoveDown() const
{
    int nextRow = currentRow + 1;
    auto shape = getCurrentShape();
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                int row = nextRow + i;
                int col = currentCol + j;
                if (row >= rows || board[row][col] != "Empty")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void TetrisGame::dropBlock()
{
    while (canMoveDown())
    {
        currentRow++;
    }
    fixBlock();
    clearFullLines();
    spawnNewShape();
}

void TetrisGame::generateNextShapes()
{
    while (nextQueue.size() < 5)
    {
        nextQueue.push(getRandomShape());
    }
}

void TetrisGame::spawnNewShape()
{
    currentRow = 0;
    currentCol = cols / 2;
    currentShapeIndex = nextQueue.front();
    nextQueue.pop();
    currentShape = shapes[currentShapeIndex];
    generateNextShapes();
}
