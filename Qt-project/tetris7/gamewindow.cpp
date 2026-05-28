#include "GameWindow.h"

GameWindow::GameWindow(QString gamename, QWidget *parent) : QWidget(parent)
{
    timer=startTimer(SPPED_MS);
    GAMENAME = gamename;

    if (GAMENAME == "Puyopuyo")
    {
        p_game = new PuyopuyoGame();
        resize(500, 800);
    }
    else if (GAMENAME == "Tetris")
    {
        p_game = new TetrisGame();
        resize(700, 1100);
    }
    else if (GAMENAME == "PuyopuyoTetris")
    {
        p_game = new PuyopuyoTetrisGame();
        resize(700, 900);
    }
    setWindowTitle(gamename);
}

GameWindow::~GameWindow()
{
    delete p_game;
    delete gameoverwindow;
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    int ROW = p_game->ROW;
    int COL = p_game->COL;
    int LENGTH = p_game->LENGTH;

    string** board = p_game->board;
    string* next = p_game->next;

    double axis_row = p_game->axis_row;
    double axis_col = p_game->axis_col;

    int score = p_game->score;

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN,COL*BLOCK_SIZE,ROW*BLOCK_SIZE);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,BLOCK_SIZE,BLOCK_SIZE),Qt::AlignCenter,"NEXT");

    for(int k = 0; k < LENGTH; k++)
    {
        std::string current_color = next[k];

        int current_col = MARGIN*10+COL*(BLOCK_SIZE/1)+0*(BLOCK_SIZE/1);
        int current_row = MARGIN*10+0*(BLOCK_SIZE/2) + 100 * k + 100;
        int one = (BLOCK_SIZE/2);

        if (next[k].length() == 2)
        {
            for (int l = 0; l < 2; l++)
            {
                if (next[k][l] == 'R')
                {
                    painter.setBrush(QBrush(QColor(255, 0, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'Y')
                {
                    painter.setBrush(QBrush(QColor(255, 255, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'G')
                {
                    painter.setBrush(QBrush(QColor(0, 255, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'B')
                {
                    painter.setBrush(QBrush(QColor(0, 0, 255),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'P')
                {
                    painter.setBrush(QBrush(QColor(255, 0, 255),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }
            }
        }
        //X
        //X

        if (next[k] == "O")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
        }
        //OO
        //OO

        else if (next[k] == "T")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        // T
        //TTT

        else if (next[k] == "S")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + 2 * one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
        }
        // SS
        //SS

        else if (next[k] == "Z")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        //ZZ
        // ZZ

        else if (next[k] == "J")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        //J
        //JJJ

        else if (next[k] == "L")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col + 2 * one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        //  L
        //LLL

        else if (next[k] == "I")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
            painter.drawRect(current_col + 3 * one, current_row + one, one, one);
        }
        //
        //IIII
    }

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    if (GAMENAME == "Puyopuyo")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current chain : " + QString::number(score));
    if (GAMENAME == "Tetris")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current line : " + QString::number(score));
    if (GAMENAME == "PuyopuyoTetris")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current chain&line : " + QString::number(score));

    for(int i=0; i<ROW; i++)
        for(int j=0; j<COL; j++)
        {
                painter.setBrush(QBrush(QColor(255, 255, 255),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
        }

    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COL;j++)
        {
            if(board[i][j] == "BlackPuyo")
            {
                painter.setBrush(QBrush(QColor(0, 0, 0),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            if(board[i][j] == "BlackBlock")
            {
                painter.setBrush(QBrush(QColor(0, 0, 0),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Gray")
            {
                painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "White")
            {
                painter.setBrush(QBrush(QColor(255, 255, 255),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Red")
            {
                painter.setBrush(QBrush((QColor(255, 0, 0)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Yellow")
            {
                painter.setBrush(QBrush((QColor(255, 255, 0)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Green")
            {
                painter.setBrush(QBrush((QColor(0, 255, 0)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Blue")
            {
                painter.setBrush(QBrush((QColor(0, 0, 255)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Purple")
            {
                painter.setBrush(QBrush((QColor(255, 0, 255)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
        }
    }

    painter.setBrush(QBrush(QColor(0, 0, 0),Qt::SolidPattern));
    painter.drawRect(axis_col*BLOCK_SIZE+MARGIN + BLOCK_SIZE/4,axis_row*BLOCK_SIZE+MARGIN + BLOCK_SIZE/4,BLOCK_SIZE/2,BLOCK_SIZE/2);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (p_game->gameover == true)
        return;

    switch(event->key())
    {
    case Qt::Key_Down:
        drawNext();
        break;
    case Qt::Key_Left:
        drawNext();
        break;
    case Qt::Key_Right:
        drawNext();
        break;
    case Qt::Key_Space:
        p_game->gameover = true;
        p_game->axis_row = -1;
        p_game->axis_col = -1;
        killTimer(timer);
        drawNext();
        gameoverwindow = new GameoverWindow;
        gameoverwindow->show();
        break;
    case Qt::Key_Z:
        drawNext();
        break;
    case Qt::Key_X:
        drawNext();
        break;
    default:
        break;
    }
}

void GameWindow::timerEvent(QTimerEvent* event)
{
    if (p_game->gameover == true)
        return;

    if(event->timerId()==timer)
        drawNext();
}

void GameWindow::drawNext()
{
    int ROW = p_game->ROW;
    int COL = p_game->COL;

    string** board = p_game->board;
    string* next = p_game->next;

    int LENGTH = p_game->LENGTH;

    if (p_game->gameover == true)
    {
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
            {
                if (board[i][j] == "Red" || board[i][j] == "Yellow" || board[i][j] == "Green" || board[i][j] == "Blue" || board[i][j] == "Purple")
                    board[i][j] = "BlackPuyo";

                else if (board[i][j] == "Gray")
                    board[i][j] = "BlackBlock";
            }

        return;
    }

    for (int i = 0; i < LENGTH; i++)
    {
        if (next[i].length() == 2)
        {
            for (int j = 0; j < 2; j++)
            {
                if (next[i][j] == 'R')
                {
                    next[i][j] = 'Y';
                }

                else if (next[i][j] == 'Y')
                {
                    next[i][j] = 'G';
                }

                else if (next[i][j] == 'G')
                {
                    next[i][j] = 'B';
                }

                else if (next[i][j] == 'B')
                {
                    next[i][j] = 'P';
                }

                else if (next[i][j] == 'P')
                {
                    next[i][j] = 'R';
                }
            }
        }

        else
        {
            if (next[i][0] == 'I')
            {
                next[i][0] = 'J';
            }

            else if (next[i][0] == 'J')
            {
                next[i][0] = 'L';
            }

            else if (next[i][0] == 'L')
            {
                next[i][0] = 'O';
            }

            else if (next[i][0] == 'O')
            {
                next[i][0] = 'S';
            }

            else if (next[i][0] == 'S')
            {
                next[i][0] = 'Z';
            }

            else if (next[i][0] == 'Z')
            {
                next[i][0] = 'T';
            }

            else if (next[i][0] == 'T')
            {
                next[i][0] = 'I';
            }
        }
    }

    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            if (GAMENAME == "Puyopuyo" || GAMENAME == "PuyopuyoTetris")
            {
                if(board[i][j] == "Red")
                {
                    board[i][j] = "Yellow";
                }

                else if(board[i][j] == "Yellow")
                {
                    board[i][j] = "Green";
                }

                else if(board[i][j] == "Green")
                {
                    board[i][j] = "Blue";
                }

                else if(board[i][j] == "Blue")
                {
                    board[i][j] = "Purple";
                }

                else if(board[i][j] == "Purple")
                {
                    board[i][j] = "Red";
                }
            }

            if (GAMENAME == "Tetris" || GAMENAME == "PuyopuyoTetris")
            {
                if(board[i][j] == "White")
                {
                    board[i][j] = "Gray";
                }

                else if(board[i][j] == "Gray")
                {
                    board[i][j] = "White";
                }
            }
        }

    (p_game->score)++;
    update();
}
