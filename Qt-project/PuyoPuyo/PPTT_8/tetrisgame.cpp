#include "TetrisGame.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <QTimer>
using namespace std;

TetrisGame::TetrisGame()
{
    rowsCount = 22;
    colsCount = 10;
    axis_row = 0;
    axis_col = colsCount / 2;
    score = 0;
    gameover = false;
    board.resize(rowsCount, vector<string>(colsCount, "Empty")); // 'board'를 'ROW' 수의 행으로 크기 조정하고, 각 행은 'COL' 수의 열을 가지며, 모든 열은 "Empty" 문자열로 초기화됩니다.
    boardColors.resize(rowsCount, vector<QColor>(colsCount, QColor(255, 255, 255))); // 'boardColors'를 'ROW' 수의 행으로 크기 조정하고, 각 행은 'COL' 수의 QColor 객체를 가지며, 모든 객체는 흰색(RGB: 255, 255, 255)으로 초기화됩니다.
    srand(time(0)); //random 값을 초기화 시킨다.

    shapes = {
        // I shape
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        // O shape
        {{1, 1},
         {1, 1}},
        // T shape
        {{0, 1, 0},
         {1, 1, 1},
         {0, 0, 0}},
        // S shape
        {{0, 1, 1},
         {1, 1, 0},
         {0, 0, 0}},
        // Z shape
        {{1, 1, 0},
         {0, 1, 1},
         {0, 0, 0}},
        // J shape
        {{1, 0, 0},
         {1, 1, 1},
         {0, 0, 0}},
        // L shape
        {{0, 0, 1},
         {1, 1, 1},
         {0, 0, 0}}
    };

    // Assign colors to shapes
    shapeColors = {
        {0, QColor(0, 255, 255)}, // I shape - Cyan
        {1, QColor(255, 255, 0)}, // O shape - Yellow
        {2, QColor(128, 0, 128)}, // T shape - Purple
        {3, QColor(0, 255, 0)},   // S shape - Green
        {4, QColor(255, 0, 0)},   // Z shape - Red
        {5, QColor(0, 0, 255)},   // J shape - Blue
        {6, QColor(255, 165, 0)}  // L shape - Orange
    };

    initializeBoard(); // board를 초기화시킨다.
    generateNextShapes(); //다음 블록을 생성한다.
    spawnNewShape();//새로운 블록을 가져온다.
}

TetrisGame::~TetrisGame()
{
}

void TetrisGame::initializeBoard()
{
    /**
    * 게임 보드를 초기화합니다.
    * 모든 셀을 "Empty"로 설정하고, 첫 두 줄을 회색으로 설정합니다.
    */
    for (int i = 0; i < rowsCount; ++i)
    {
        for (int j = 0; j < colsCount; ++j)
        {
            board[i][j] = "Empty"; // 모든 공간을 Empty이다.
            if (i < 2)
                boardColors[i][j] = QColor(192, 192, 192); // 첫 위 두줄은 회색이어야한다.
            else
                boardColors[i][j] = QColor(255, 255, 255); // 나머지는 흰색이다.
        }
    }
}

//테트리스를 랜덤으로 받아온다.
// Initialize the game board
int TetrisGame::getRandomShape()
{
    /**
    * 랜덤한 블록 인덱스를 생성합니다.
    */
    return rand() % shapes.size();
}


void TetrisGame::fixBlock()
{
    /**
    * 현재 블록을 보드에 고정하고, 게임 종료 여부를 검사합니다.
    */
    QColor color = darkenColor(shapeColors[currentShapeIndex]);

    for (int i = 0; i < currentShape.size(); ++i)
    {
        for (int j = 0; j < currentShape[i].size(); ++j)
        {
            if (currentShape[i][j] == 1)
            {
                int row = axis_row + i;  // 블록의 행 위치 계산
                int col = axis_col + j; // 블록의 열 위치 계산
                board[row][col] = "FixedBlock";  // 보드의 해당 위치에 고정 블록 설정
                boardColors[row][col] = color;  // 보드의 해당 위치에 블록 색상 설정
            }
        }
    }

    if (checkGameOver())
    {
        gameover = true; //게임 종료를 표시
        emit gameOver(); // 게임 종료 신호를 발생시킨다.
    }
}

//어둡게 만들어준다.
QColor TetrisGame::darkenColor(const QColor& color)
{
    /**
    * 주어진 색상을 어둡게 만듭니다.
    */
    int factor = 90; // Darken factor
    return QColor(max(color.red() - factor, 0),
                  max(color.green() - factor, 0),
                  max(color.blue() - factor, 0));
}

//밝게 만들어준다.
QColor TetrisGame::brightenColor(const QColor& color)
{
    /**
    * 주어진 색상을 밝게 만듭니다.
    */
    int factor = 140; // Brighten factor
    return QColor(min(color.red() + factor, 255),
                  min(color.green() + factor, 255),
                  min(color.blue() + factor, 255));
}

//한줄이 완성되어 있으면 한줄을 삭제한다.
void TetrisGame::clearFullLines()
{
    /**
    * 가득 찬 줄을 찾아 제거하고, 점수를 증가시킵니다.
    */
    QVector<int> linesToClear; // 삭제할 라인 번호를 저장할 벡터

    for (int i = 2; i < rowsCount; ++i) // 첫 두 줄(회색)은 제외
    {
        bool fullLine = true; // 현재 행이 가득 찬 상태인지 나타내는 플래그 초기화

        for (int j = 0; j < colsCount; ++j)
        {
            if (board[i][j] == "Empty") // 현재 셀이 비어 있는지 확인
            {
                fullLine = false; // 빈 셀이 있으면 현재 행은 가득 찬 상태가 아님
                break;
            }
        }

        if (fullLine) // 현재 행이 가득 찬 상태라면
        {
            linesToClear.append(i); // 삭제할 행 목록에 추가
        }
    }

    if (linesToClear.isEmpty()) // 삭제할 행이 없는 경우 함수 종료
    {
        return;
    }

    for (int line : linesToClear)
    {
        for (int j = 0; j < colsCount; ++j)
        {
            boardColors[line][j] = brightenColor(boardColors[line][j]); // 행을 밝게 표시
        }
    }

    emit linesCleared(); // 창에서 업데이트를 트리거하는 신호 발생

    QTimer::singleShot(200, [this, linesToClear]() {
        // 삭제할 각 행에 대해 처리
        for (int line : linesToClear)
        {
            for (int k = line; k > 2; --k) // 현재 행보다 위에 있는 행들을 한 칸씩 아래로 이동
            {
                for (int j = 0; j < colsCount; ++j)
                {
                    board[k][j] = board[k - 1][j]; // 행을 아래로 이동
                    boardColors[k][j] = boardColors[k - 1][j]; // 색상도 함께 이동
                }
            }
            for (int j = 0; j < colsCount; ++j) // 최상단 행을 비움
            {
                board[2][j] = "Empty";
                boardColors[2][j] = QColor(255, 255, 255); // 흰색으로 설정
            }
        }

        emit linesCleared(); // 창에서 업데이트를 트리거하는 신호를 다시 발생
    });

    score += linesToClear.size(); // 삭제된 라인의 개수만큼 점수 증가
}

//회색 한줄에 걸치면 게임 오버
bool TetrisGame::checkGameOver()
{
    /**
    * 게임이 종료되었는지 확인합니다.
    * 첫 두 줄에 블록이 있는지 검사합니다.
    */
    for (int j = 0; j < colsCount; ++j)
    {
        if (board[1][j] != "Empty")
        {
            return true;
        }
    }
    return false;
}

//지금 블록을 반환
vector<vector<int>> TetrisGame::getCurrentShape()
{
    /**
    * 현재 블록의 모양을 반환합니다.
    */
    return currentShape;
}

//시계방향으로 돌릴 수 있으면 돌리고 돌릴 상태를 현재 상태로 바꾼다.
void TetrisGame::rotateShapeClockwise()
{
    /**
    * 현재 블록을 시계 방향으로 회전합니다.
    */
    auto rotated = rotateShape(currentShape, true);
    if (canRotate(rotated))
    {
        currentShape = rotated;
    }
}

//반시계방향으로 돌릴 수 있으면 돌리고 돌릴 상태를 현재 상태로 바꾼다.
void TetrisGame::rotateShapeCounterClockwise()
{
    /**
    * 현재 블록을 반시계 방향으로 회전합니다.
    */
    auto rotated = rotateShape(currentShape, false);
    if (canRotate(rotated))
    {
        currentShape = rotated;
    }
}

vector<vector<int>> TetrisGame::rotateShape(const vector<vector<int>>& shape, bool clockwise)
{
    /**
    * 주어진 블록을 시계 방향 또는 반시계 방향으로 회전합니다.
    */
    int n = shape.size(); // 회전된 크기(n x n 형태로 가정
    vector<vector<int>> rotated(n, vector<int>(n, 0));
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

bool TetrisGame::canRotate(const vector<vector<int>>& rotatedShape)
{
    /**
    * 주어진 블록을 회전할 수 있는지 검사합니다.
    */
    int n = rotatedShape.size();  // 회전된 블록의 크기(n x n 형태로 가정)
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (rotatedShape[i][j] == 1)
            {
                int newRow = axis_row + i;
                int newCol = axis_col + j;
                if (newRow < 0 || newRow >= rowsCount || newCol < 0 || newCol >= colsCount || board[newRow][newCol] != "Empty")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool TetrisGame::canMoveDown()
{
    /**
    * 현재 블록을 한 칸 아래로 이동할 수 있는지 검사합니다.
    */
    int next_row = axis_row + 1; // 현재 블록이 한 칸 아래로 이동했을 때의 새로운 행 위치
    auto shape = getCurrentShape(); // 현재 블록의 모양을 가져옵니다.
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                int row = next_row + i; // 블록의 현재 행 위치 계산
                int col = axis_col + j; // 블록의 현재 열 위치 계산
                if (row >= row || board[row][col] != "Empty")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

//블록이 떨어진다.
void TetrisGame::dropBlock()
{
    /**
    * 현재 블록을 가능한 한 아래로 이동시키고, 고정시킵니다.
    */
    while (canMoveDown())
    {
        axis_row++;
    }
    fixBlock();
    clearFullLines();
    spawnNewShape();
}

// 만약 혹시나 컴퓨터가 인식을 못해서 여러개를 pop할 수 있는 상황이 올 수도 있어서
// 대기 큐 사이즈로 했다.
void TetrisGame::generateNextShapes()
{
    /**
    * 다음에 나올 블록을 생성하여 큐에 추가합니다.
    */
    while (nextQueue.size() < 5)
    {
        nextQueue.push(getRandomShape());
    }
}

// 새로운 블록을 가져온다.
void TetrisGame::spawnNewShape()
{
    /**
    * 새로운 블록을 생성하여 게임에 추가합니다.
    */
    axis_row = 0; //제일 위에서 시작
    axis_col = colsCount / 2; // 그 중 가운데에서 시작
    currentShapeIndex = nextQueue.front(); //현재 대기 중인 테트리스 중 앞에 것이 현재 꺼이다.
    nextQueue.pop(); //다음 블록 중 앞에 있는 하나를 가져온다.
    currentShape = shapes[currentShapeIndex]; // 복사본 사용
    generateNextShapes(); //하나를 가져왔기 때문에 하나가 빈다 그렇기 때문에 추가해야한다.
}
