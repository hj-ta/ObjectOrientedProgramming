#include "PuyoPuyoWindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMessageBox>
#include "PuyoPuyoGame.h"

PuyoPuyoWindow::PuyoPuyoWindow(QWidget *parent)
    : QWidget(parent), p_game(new PuyoPuyoGame())
{
    connect(p_game, &PuyoPuyoGame::puyosCleared, this, &PuyoPuyoWindow::updateBoard);
    connect(p_game, &PuyoPuyoGame::gameOver, this, &PuyoPuyoWindow::handleGameOver);
    timer = startTimer(500); // Start the timer
    resize(700, 1100);
    setWindowTitle("Puyo Puyo");
}

PuyoPuyoWindow::~PuyoPuyoWindow()
{
    delete p_game; // Delete the game object
}

void PuyoPuyoWindow::paintEvent(QPaintEvent *event)
{
    int rowCount = p_game->rowCount; // Number of rows in the game board
    int colCount = p_game->colCount; // Number of columns in the game board
    auto& gameBoard = p_game->gameBoard; // Current game board
    auto& boardColors = p_game->boardColors; // Current game board colors
    double currentRow = p_game->currentRow; // Current row position
    double currentCol = p_game->currentCol; // Current column position
    int currentScore = p_game->currentScore; // Current score
    int chainCounter = p_game->chainCounter; // Current chain count

    QPainter painter(this); // Create QPainter object
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern)); // Set brush to white
    painter.drawRect(50, 50, colCount * BlockSize, rowCount * BlockSize); // Draw game board

    painter.setPen(Qt::black); // Set pen to black
    painter.setFont(QFont("Arial", 14)); // Set font to Arial, size 14

    painter.drawText(QRect(50 + colCount * BlockSize + 20, 50, 100, 20), Qt::AlignCenter, "NEXT"); // Draw "NEXT" text

    // Draw the game board (squares)
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            painter.drawRect(j * BlockSize + 50, i * BlockSize + 50, BlockSize, BlockSize);

            if (gameBoard[i][j] != "Empty")
            {
                painter.setBrush(QBrush(boardColors[i][j], Qt::SolidPattern));
                painter.drawEllipse(j * BlockSize + 50, i * BlockSize + 50, BlockSize, BlockSize);
            }
        }
    }

    // Draw the current puyo (tiles)
    auto puyo = p_game->retrieveCurrentPuyo();
    auto puyoColors = p_game->retrievePuyoColors();
    QColor puyoColor1 = puyoColors[puyo[0]];
    QColor puyoColor2 = puyoColors[puyo[1]];

    painter.setBrush(QBrush(puyoColor1, Qt::SolidPattern));
    painter.drawEllipse(currentCol * BlockSize + 50, currentRow * BlockSize + 50, BlockSize, BlockSize);

    if (p_game->orientation == PuyoPuyoGame::Orientation::Horizontal) {
        painter.setBrush(QBrush(puyoColor2, Qt::SolidPattern));
        painter.drawEllipse((currentCol + 1) * BlockSize + 50, currentRow * BlockSize + 50, BlockSize, BlockSize);
    } else {
        painter.setBrush(QBrush(puyoColor2, Qt::SolidPattern));
        painter.drawEllipse(currentCol * BlockSize + 50, (currentRow + 1) * BlockSize + 50, BlockSize, BlockSize);
    }

    // Draw the next puyo
    int nextPuyoY = 50 + 100;
    // Assuming retrieveNextQueue() returns a const reference or a copy
    const std::queue<int>& tempQueue = p_game->retrieveNextQueue();
    int spacing = 50; // Vertical spacing between displayed next Puyos
    auto puyoPairings = p_game->retrievePuyoPairings();
    std::queue<int> displayQueue(tempQueue); // Make a copy for display purposes
    int nextPuyoCount = 0;
    while (!displayQueue.empty() && nextPuyoCount < 2) {
        int puyoIndex = displayQueue.front();
        displayQueue.pop();
        auto nextPuyo = puyoPairings[puyoIndex];
        QColor nextPuyoColor1 = puyoColors[nextPuyo[0]];
        QColor nextPuyoColor2 = puyoColors[nextPuyo[1]];

        painter.setBrush(QBrush(nextPuyoColor1, Qt::SolidPattern));
        painter.drawEllipse(colCount * BlockSize + 70, nextPuyoY, BlockSize, BlockSize);

        painter.setBrush(QBrush(nextPuyoColor2, Qt::SolidPattern));
        painter.drawEllipse(colCount * BlockSize + 70, nextPuyoY + BlockSize, BlockSize, BlockSize);

        nextPuyoY += 2 * BlockSize + spacing;
        nextPuyoCount++;
    }
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));
    painter.drawText(QRect(50 + colCount * BlockSize + 20, 50 + 200, 100, 50), Qt::AlignCenter, "current chain : " + QString::number(chainCounter));
}

void PuyoPuyoWindow::keyPressEvent(QKeyEvent *event)
{
    if (p_game->isGameOver)
        return;

    switch (event->key())
    {
    case Qt::Key_Down:
        movePuyoDown();
        break;
    case Qt::Key_Left:
        movePuyoLeft();
        break;
    case Qt::Key_Right:
        movePuyoRight();
        break;
    case Qt::Key_Z:
        rotatePuyoCounterClockwise();
        updateBoard();
        break;
    case Qt::Key_X:
        rotatePuyoClockwise();
        updateBoard();
        break;
    case Qt::Key_Space:
        while (p_game->canMoveDown())
        {
            movePuyoDown();
        }
        updateBoard();
        break;
    default:
        break;
    }
}

void PuyoPuyoWindow::timerEvent(QTimerEvent *event)
{
    if (p_game->isGameOver)
        return;

    if (event->timerId() == timer)
    {
        movePuyoDown();
        updateBoard();
    }
}

void PuyoPuyoWindow::movePuyoDown()
{
    if (p_game->canMoveDown())
    {
        p_game->currentRow++;
    }
    else
    {
        p_game->placePuyo();
        createNewPuyo();
    }
    updateBoard();
}

void PuyoPuyoWindow::movePuyoLeft()
{
    if (p_game->canMoveLeft())
    {
        p_game->currentCol--;
        updateBoard();
    }
}

void PuyoPuyoWindow::movePuyoRight()
{
    if (p_game->canMoveRight())
    {
        p_game->currentCol++;
        updateBoard();
    }
}

void PuyoPuyoWindow::rotatePuyoClockwise()
{
    if (p_game->canRotateClockwise())
    {
        p_game->rotatePuyoClockwise();
        updateBoard();
    }
}

void PuyoPuyoWindow::rotatePuyoCounterClockwise()
{
    if (p_game->canRotateCounterClockwise())
    {
        p_game->rotatePuyoCounterClockwise();
        updateBoard();
    }
}

void PuyoPuyoWindow::fixPuyo()
{
    p_game->placePuyo();
}

void PuyoPuyoWindow::createNewPuyo()
{
    p_game->addNewPuyo();
}

void PuyoPuyoWindow::updateBoard()
{
    if (p_game->isGameOver)
    {
        for (int i = 0; i < p_game->rowCount; i++)
            for (int j = 0; j < p_game->colCount; j++)
            {
                if (p_game->gameBoard[i][j] == "Empty")
                    p_game->gameBoard[i][j] = "FixedPuyo";
            }
        return;
    }
    (p_game->currentScore)++;
    update();
}

void PuyoPuyoWindow::handleGameOver()
{
    killTimer(timer);
    QMessageBox::information(this, "Game Over", "Game Over! Your score: " + QString::number(p_game->currentScore));
}
