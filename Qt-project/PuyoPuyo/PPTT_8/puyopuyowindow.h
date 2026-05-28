#ifndef PUYOPUYOWINDOW_H
#define PUYOPUYOWINDOW_H

#include <QWidget>
#include "PuyoPuyoGame.h"

class PuyoPuyoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PuyoPuyoWindow(QWidget *parent = nullptr);
    ~PuyoPuyoWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    PuyoPuyoGame *p_game;
    int timer;
    const int BlockSize = 30; // Define BlockSize

    void movePuyoDown();
    void movePuyoLeft();
    void movePuyoRight();
    void rotatePuyoClockwise();
    void rotatePuyoCounterClockwise();
    void fixPuyo();
    void createNewPuyo();
    void drawNext();

private slots:
    void updateBoard();
    void handleGameOver();
};

#endif // PUYOPUYOWINDOW_H
