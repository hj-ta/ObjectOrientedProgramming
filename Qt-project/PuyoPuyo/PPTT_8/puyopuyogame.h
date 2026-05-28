#ifndef PUYOPUYOGAME_H
#define PUYOPUYOGAME_H

#include <QObject>
#include <vector>
#include <queue>
#include <string>
#include <QColor>

class PuyoPuyoGame : public QObject
{
    Q_OBJECT

public:
    PuyoPuyoGame();
    ~PuyoPuyoGame();
    enum class Orientation
    {
        Vertical,
        Horizontal
    } orientation;
    const int* retrieveCurrentPuyo() const;
    void rotatePuyoClockwise();
    void rotatePuyoCounterClockwise();
    bool canMoveDown() const;
    bool canMoveLeft() const;
    bool canMoveRight() const;
    bool canRotateClockwise() const;
    bool canRotateCounterClockwise() const;
    int rowCount;
    int colCount;
    int currentRow;
    int currentCol;
    int currentScore;
    int chainCounter;
    bool isGameOver;
    std::vector<QColor> retrievePuyoColors() const;
    std::queue<int> retrieveNextQueue() const;
    std::vector<std::vector<int>> retrievePuyoPairings() const;
    std::vector<std::vector<std::string>> gameBoard;
    std::vector<std::vector<QColor>> boardColors;
    void fixPuyo();

public slots:
    void placePuyo();
    void addNewPuyo();
    void removePuyos();
    void applyGravityEffect();
    bool isGameOverCondition() const;
signals:
    void puyosCleared(int chainCounter);
    void gameOver();

private:
    void resetBoard();
    int generateRandomPuyo() const;
    void prepareNextPuyos();
    bool performBfsClear(int row, int col, const std::string& color);
    bool isValidMove(int newRow, int newCol, int secondRow, int secondCol) const;
    QColor darkenPuyoColor(const QColor& color) const;

    std::vector<std::vector<int>> puyoPairings;
    std::vector<QColor> puyoColors;
    int currentPuyo[2];
    int currentPuyoIndex;
    std::queue<int> nextQueue;
};

#endif // PUYOPUYOGAME_H
