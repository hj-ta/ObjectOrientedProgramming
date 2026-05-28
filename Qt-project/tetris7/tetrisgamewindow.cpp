#include "TetrisGameWindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMessageBox>
#include "GameOverWindow.h"
using namespace std;

TetrisGameWindow::TetrisGameWindow(QWidget *parent)
    : QWidget(parent), game(new TetrisGame())
{
    connect(game, &TetrisGame::linesCleared, this, &TetrisGameWindow::updateBoard);
    connect(game, &TetrisGame::gameOver, this, &TetrisGameWindow::handleGameOver);
    timerId = startTimer(500);
    resize(700, 1100);
    setWindowTitle("Tetris");
}

TetrisGameWindow::~TetrisGameWindow()
{
    delete game;
}

void TetrisGameWindow::paintEvent(QPaintEvent *event)
{
    int rows = game->rows;
    int cols = game->cols;
    auto& board = game->board;
    auto& boardColors = game->boardColors;
    double currentRow = game->currentRow;
    double currentCol = game->currentCol;
    int score = game->score;

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(50, 50, cols * blockSize, rows * blockSize);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));

    painter.drawText(QRect(cols * blockSize + 70, 50, 100, 20), Qt::AlignCenter, "NEXT");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            painter.setBrush(QBrush(boardColors[i][j], Qt::SolidPattern));
            painter.drawRect(j * blockSize + 50, i * blockSize + 50, blockSize, blockSize);
            if (board[i][j] == "Fix")
            {
                painter.setBrush(QBrush(boardColors[i][j], Qt::SolidPattern));
                painter.drawRect(j * blockSize + 50, i * blockSize + 50, blockSize, blockSize);
            }
        }
    }

    auto shape = game->getCurrentShape();
    QColor shapeColor = game->shapeColors[game->currentShapeIndex];
    painter.setBrush(QBrush(shapeColor, Qt::SolidPattern));
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                int row = currentRow + i;
                int col = currentCol + j;
                painter.drawRect(col * blockSize + 50, row * blockSize + 50, blockSize, blockSize);
            }
        }
    }

    int nextShapeY = 50 + 100;
    queue<int> tempQueue = game->nextQueue;
    while (!tempQueue.empty())
    {
        int shapeIndex = tempQueue.front();
        tempQueue.pop();
        auto nextShape = game->shapes[shapeIndex];
        QColor nextShapeColor = game->shapeColors[shapeIndex];
        painter.setBrush(QBrush(nextShapeColor, Qt::SolidPattern));
        for (int i = 0; i < nextShape.size(); ++i)
        {
            for (int j = 0; j < nextShape[i].size(); ++j)
            {
                if (nextShape[i][j] == 1)
                {
                    painter.drawRect(cols * blockSize + 70 + j * blockSize, nextShapeY + i * blockSize, blockSize, blockSize);
                }
            }
        }
        nextShapeY += (nextShape.size() + 1) * blockSize;
    }

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));
    painter.drawText(QRect(50 + cols * blockSize + 20, rows * blockSize + 80, 150, 20), Qt::AlignCenter, "Current Score: " + QString::number(score));
}

void TetrisGameWindow::keyPressEvent(QKeyEvent *event)
{
    if (game->isGameOver)
        return;

    switch (event->key())
    {
    case Qt::Key_Down:
        moveBlockDown();
        break;
    case Qt::Key_Left:
        moveBlockLeft();
        break;
    case Qt::Key_Right:
        moveBlockRight();
        break;
    case Qt::Key_Z:
        game->rotateCurrentShapeCounterClockwise();
        drawNext();
        break;
    case Qt::Key_X:
        game->rotateCurrentShapeClockwise();
        drawNext();
        break;
    case Qt::Key_Space:
        game->dropBlock();
        drawNext();
        break;
    default:
        break;
    }
}

void TetrisGameWindow::timerEvent(QTimerEvent *event)
{
    if (game->isGameOver)
        return;

    if (event->timerId() == timerId)
    {
        moveBlockDown();
        drawNext();
    }
}

void TetrisGameWindow::moveBlockDown()
{
    if (canMoveDown())
    {
        game->currentRow++;
    }
    else
    {
        game->fixBlock();
        game->clearFullLines();
        createNewBlock();
    }
    drawNext();
}

void TetrisGameWindow::moveBlockLeft()
{
    if (canMoveLeft())
    {
        game->currentCol--;
        drawNext();
    }
}

void TetrisGameWindow::moveBlockRight()
{
    if (canMoveRight())
    {
        game->currentCol++;
        drawNext();
    }
}

bool TetrisGameWindow::canMoveDown()
{
    int nextRow = game->currentRow + 1;

    auto shape = game->getCurrentShape();
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                int row = nextRow + i;
                int col = game->currentCol + j;
                if (row >= game->rows || game->board[row][col] != "Empty")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool TetrisGameWindow::canMoveLeft()
{
    int nextCol = game->currentCol - 1;

    auto shape = game->getCurrentShape();
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                int row = game->currentRow + i;
                int col = nextCol + j;
                if (col < 0 || game->board[row][col] != "Empty")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool TetrisGameWindow::canMoveRight()
{
    int nextCol = game->currentCol + 1;

    auto shape = game->getCurrentShape();
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                int row = game->currentRow + i;
                int col = nextCol + j;
                if (col >= game->cols || game->board[row][col] != "Empty")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void TetrisGameWindow::rotateBlockClockwise()
{
    game->rotateCurrentShapeClockwise();
    drawNext();
}

void TetrisGameWindow::rotateBlockCounterClockwise()
{
    game->rotateCurrentShapeCounterClockwise();
    drawNext();
}

void TetrisGameWindow::fixBlock()
{
    game->fixBlock();
}

void TetrisGameWindow::createNewBlock()
{
    game->spawnNewShape();
}



void TetrisGameWindow::updateBoard()
{
    update();
}

void TetrisGameWindow::handleGameOver()
{
    killTimer(timerId);
    GameoverWindow* gameOverWindow = new GameoverWindow;
    gameOverWindow->show();
}

void TetrisGameWindow::drawNext()
{
    if (game->isGameOver)
    {
        for (int i = 0; i < game->rows; i++)
            for (int j = 0; j < game->cols; j++)
            {
                if (game->board[i][j] == "Empty")
                    game->board[i][j] = "Fix";
            }
        return;
    }

    update();
}
