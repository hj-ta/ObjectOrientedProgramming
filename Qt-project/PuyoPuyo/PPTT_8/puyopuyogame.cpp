#include "PuyoPuyoGame.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>

PuyoPuyoGame::PuyoPuyoGame()
{
    rowCount = 20;
    colCount = 10;
    currentRow = 0;
    currentCol = colCount / 2;
    currentScore = 0;
    chainCounter = 0;
    isGameOver = false;
    gameBoard.resize(rowCount, std::vector<std::string>(colCount, "Empty"));
    boardColors.resize(rowCount, std::vector<QColor>(colCount, QColor(255, 255, 255)));
    srand(static_cast<unsigned int>(time(0))); // Seed for random puyo generation

    puyoPairings = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
        {1, 0}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
        {2, 0}, {2, 1}, {2, 3}, {2, 4}, {2, 5},
        {3, 0}, {3, 1}, {3, 2}, {3, 4}, {3, 5},
        {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 5},
        {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}
    };

    puyoColors = {
        QColor(255, 0, 0),    // Red
        QColor(255, 255, 0),  // Yellow
        QColor(0, 255, 0),    // Green
        QColor(0, 0, 255),    // Blue
        QColor(128, 0, 128),  // Purple
        QColor(255, 165, 0)   // Orange
    };

    resetBoard();
    prepareNextPuyos();
    addNewPuyo();
}

PuyoPuyoGame::~PuyoPuyoGame() {}

void PuyoPuyoGame::resetBoard()
{
    for (int i = 0; i < rowCount; ++i)
    {
        for (int j = 0; j < colCount; ++j)
        {
            gameBoard[i][j] = "Empty";
            boardColors[i][j] = (i < 2) ? QColor(192, 192, 192) : QColor(255, 255, 255); // Light gray for first two rows, white for others
        }
    }
}

int PuyoPuyoGame::generateRandomPuyo() const
{
    return rand() % puyoPairings.size();
}

std::vector<QColor> PuyoPuyoGame::retrievePuyoColors() const
{
    return puyoColors;
}

std::queue<int> PuyoPuyoGame::retrieveNextQueue() const
{
    return nextQueue;
}

std::vector<std::vector<int>> PuyoPuyoGame::retrievePuyoPairings() const
{
    return puyoPairings;
}

void PuyoPuyoGame::placePuyo()
{
    int secondRow = currentRow;
    int secondCol = currentCol;

    if (orientation == Orientation::Horizontal)
    {
        secondCol += 1;
    }
    else
    {
        secondRow += 1;
    }

    std::string firstPuyo = "Puyo" + std::to_string(currentPuyo[0]);
    std::string secondPuyo = "Puyo" + std::to_string(currentPuyo[1]);

    gameBoard[currentRow][currentCol] = firstPuyo;
    boardColors[currentRow][currentCol] = puyoColors[currentPuyo[0]]; // Use original color

    gameBoard[secondRow][secondCol] = secondPuyo;
    boardColors[secondRow][secondCol] = puyoColors[currentPuyo[1]]; // Use original color

    removePuyos();

    if (isGameOverCondition())
    {
        isGameOver = true;
        emit gameOver();
    }
    else
    {
        addNewPuyo();
    }
}

void PuyoPuyoGame::removePuyos()
{
    bool puyosRemoved = false;
    for (int i = 0; i < rowCount; ++i)
    {
        for (int j = 0; j < colCount; ++j)
        {
            if (gameBoard[i][j] != "Empty")
            {
                std::string color = gameBoard[i][j];
                if (performBfsClear(i, j, color))
                {
                    puyosRemoved = true;
                }
            }
        }
    }

    if (puyosRemoved)
    {
        applyGravityEffect();
        chainCounter++;
        emit puyosCleared(chainCounter);
    }
    else
    {
        chainCounter = 0;
    }
}

bool PuyoPuyoGame::performBfsClear(int row, int col, const std::string& color)
{
    std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(colCount, false));
    std::queue<std::pair<int, int>> toVisit;
    std::vector<std::pair<int, int>> puyosToClear;

    toVisit.push({row, col});
    visited[row][col] = true;
    puyosToClear.push_back({row, col});

    std::vector<int> dRow = {-1, 1, 0, 0};
    std::vector<int> dCol = {0, 0, -1, 1};

    while (!toVisit.empty())
    {
        auto [r, c] = toVisit.front();
        toVisit.pop();

        for (int i = 0; i < 4; ++i)
        {
            int newRow = r + dRow[i];
            int newCol = c + dCol[i];

            if (newRow >= 0 && newRow < rowCount && newCol >= 0 && newCol < colCount && !visited[newRow][newCol] && gameBoard[newRow][newCol] == color)
            {
                toVisit.push({newRow, newCol});
                visited[newRow][newCol] = true;
                puyosToClear.push_back({newRow, newCol});
            }
        }
    }

    if (puyosToClear.size() >= 4)
    {
        for (const auto& [r, c] : puyosToClear)
        {
            gameBoard[r][c] = "Empty";
            boardColors[r][c] = QColor(255, 255, 255);
        }
        return true;
    }
    return false;
}

void PuyoPuyoGame::applyGravityEffect()
{
    for (int col = 0; col < colCount; ++col)
    {
        int emptyRow = rowCount - 1;
        for (int row = rowCount - 1; row >= 0; --row)
        {
            if (gameBoard[row][col] != "Empty")
            {
                if (row != emptyRow)
                {
                    std::swap(gameBoard[row][col], gameBoard[emptyRow][col]);
                    std::swap(boardColors[row][col], boardColors[emptyRow][col]);
                }
                emptyRow--;
            }
        }
    }
}

const int* PuyoPuyoGame::retrieveCurrentPuyo() const
{
    return currentPuyo;
}

void PuyoPuyoGame::rotatePuyoClockwise()
{
    if (orientation == Orientation::Vertical)
    {
        int newCol = currentCol + 1;
        int newRow = currentRow - 1;
        if (isValidMove(newRow, newCol, currentRow, newCol))
        {
            orientation = Orientation::Horizontal;
        }
    }
    else
    {
        int newCol = currentCol - 1;
        int newRow = currentRow + 1;
        if (isValidMove(newRow, newCol, newRow, currentCol))
        {
            orientation = Orientation::Vertical;
        }
    }
}

void PuyoPuyoGame::rotatePuyoCounterClockwise()
{
    if (orientation == Orientation::Vertical)
    {
        int newCol = currentCol - 1;
        int newRow = currentRow + 1;
        if (isValidMove(newRow, newCol, currentRow, newCol))
        {
            orientation = Orientation::Horizontal;
        }
    }
    else
    {
        int newCol = currentCol + 1;
        int newRow = currentRow - 1;
        if (isValidMove(newRow, newCol, newRow, currentCol))
        {
            orientation = Orientation::Vertical;
        }
    }
}

bool PuyoPuyoGame::isValidMove(int newRow, int newCol, int secondRow, int secondCol) const
{
    return newRow >= 0 && newRow < rowCount && newCol >= 0 && newCol < colCount &&
           secondRow >= 0 && secondRow < rowCount && secondCol >= 0 && secondCol < colCount &&
           gameBoard[newRow][newCol] == "Empty" && gameBoard[secondRow][newCol] == "Empty";
}

bool PuyoPuyoGame::canMoveDown() const
{
    int nextRow = currentRow + 1;
    int secondRow = (orientation == Orientation::Vertical) ? nextRow + 1 : currentRow;
    return nextRow < rowCount && secondRow < rowCount &&
           gameBoard[nextRow][currentCol] == "Empty" &&
           (orientation == Orientation::Horizontal || gameBoard[secondRow][currentCol] == "Empty");
}

bool PuyoPuyoGame::canMoveLeft() const
{
    int nextCol = currentCol - 1;
    int secondCol = (orientation == Orientation::Horizontal) ? nextCol + 1 : currentCol;
    return nextCol >= 0 &&
           gameBoard[currentRow][nextCol] == "Empty" &&
           (orientation == Orientation::Vertical || gameBoard[currentRow][secondCol] == "Empty");
}

bool PuyoPuyoGame::canMoveRight() const
{
    int nextCol = currentCol + 1;
    int secondCol = (orientation == Orientation::Horizontal) ? nextCol + 1 : currentCol;
    return nextCol < colCount &&
           gameBoard[currentRow][nextCol] == "Empty" &&
           (orientation == Orientation::Vertical || gameBoard[currentRow][secondCol] == "Empty");
}

bool PuyoPuyoGame::canRotateClockwise() const
{
    return true; // Placeholder, add actual logic if necessary
}

bool PuyoPuyoGame::canRotateCounterClockwise() const
{
    return true; // Placeholder, add actual logic if necessary
}

bool PuyoPuyoGame::isGameOverCondition() const
{
    return std::any_of(gameBoard[2].begin(), gameBoard[2].end(), [](const std::string& cell) { return cell != "Empty"; });
}

void PuyoPuyoGame::prepareNextPuyos()
{
    // Ensure there are always at least 2 Puyos in the queue.
    while (nextQueue.size() < 2)
    {
        int nextPuyoIndex = generateRandomPuyo();
        nextQueue.push(nextPuyoIndex);
    }
}
void PuyoPuyoGame::addNewPuyo() {

    if (nextQueue.empty()) {
        prepareNextPuyos();  // Make sure there are always next Puyos ready
    }

    currentRow = 0;  // Starting position at the top of the board
    currentCol = colCount / 2;  // Start in the middle column
    orientation = Orientation::Vertical;  // Default starting orientation

    currentPuyoIndex = nextQueue.front();  // Get the index of the next Puyo pair
    nextQueue.pop();  // Remove this pair from the queue

    // Fetch the actual pair of color indices directly into the array
    currentPuyo[0] = puyoPairings[currentPuyoIndex][0];
    currentPuyo[1] = puyoPairings[currentPuyoIndex][1];
    prepareNextPuyos();  // Refill the queue after removing an element
}
