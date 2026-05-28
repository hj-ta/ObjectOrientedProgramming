#ifndef TETRISGAMEWINDOW_H
#define TETRISGAMEWINDOW_H

#include <QWidget>
#include "TetrisGame.h"

class TetrisGameWindow : public QWidget
{
    Q_OBJECT

public:
    TetrisGameWindow(QWidget *parent = nullptr);
    ~TetrisGameWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private slots:
    void updateBoard();
    bool canMoveRight();
    void moveBlockDown();
    void moveBlockLeft();
    void handleGameOver();
    void moveBlockRight();
    bool canMoveLeft();
    void rotateBlockClockwise();
    void createNewBlock();
    void rotateBlockCounterClockwise();
    void fixBlock();
    bool canMoveDown();
    void drawNext();

private:
    TetrisGame *game;
    int timerId;
    const int blockSize = 20;

};

#endif // TETRISGAMEWINDOW_H
