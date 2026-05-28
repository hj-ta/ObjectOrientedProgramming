#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QTimerEvent>
#include <QKeyEvent>
#include "Games.h"
#include "GameOverWindow.h"

const int BLOCK_SIZE=50;
const int MARGIN=5;
const int SPPED_MS = 1000;

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QString gamename, QWidget *parent = nullptr);
    ~GameWindow();

    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent* event);

    void drawNext();

    int timer;

private:
    Game* p_game;
    QString GAMENAME;
    GameoverWindow* gameoverwindow;
};

#endif // GAMEWINDOW_H
