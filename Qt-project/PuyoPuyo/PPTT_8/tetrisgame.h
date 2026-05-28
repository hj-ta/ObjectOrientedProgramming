#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <vector>
#include <queue>
#include <string>
#include <map>
#include <QColor>
#include <QObject>
using namespace std;

class TetrisGame : public QObject
{
    Q_OBJECT
public:
    TetrisGame();
    ~TetrisGame();

    void initializeBoard(); // Initialize the game board
    int getRandomShape(); // Generate a random block index
    void dropBlock(); // Drop the current block one row down
    bool checkGameOver(); // Check if the game is over
    vector<vector<int>> getCurrentShape(); // Return the current block shape
    void fixBlock(); // Fix the current block to the board
    void rotateShapeClockwise(); // Rotate the current block clockwise
    void generateNextShapes(); // Generate the next blocks
    void clearFullLines(); // Clear the full lines
    void rotateShapeCounterClockwise(); // Rotate the current block counterclockwise
    void spawnNewShape(); // Spawn a new block
    int rowsCount; // Number of rows in the game board
    int colsCount; // Number of columns in the game board
    double axis_row; // Row position of the current block's center
    int score; // Current game score
    double axis_col; // Column position of the current block's center
    bool gameover; // Game status (true if game is over)
    vector<vector<string>> board; // Game board represented as strings
    vector<vector<int>> currentShape; // Current block shape
    vector<vector<QColor>> boardColors; // Colors of the cells in the game board
    queue<int> nextQueue; // Queue of next blocks
    int currentShapeIndex; // Index of the current block
    map<int, QColor> shapeColors; // Mapping of block indices to their colors
    vector<vector<vector<int>>> shapes; // Shapes of the blocks
    int rotationState; // Current rotation state of the block
signals:
    void linesCleared(); // Signal that lines have been cleared
    void gameOver(); // Signal that the game is over

private:
    vector<vector<int>> rotateShape(const vector<vector<int>>& shape, bool clockwise); // Rotate the block
    bool canRotate(const vector<vector<int>>& rotatedShape); // Check if the block can be rotated
    bool canMoveDown(); // Check if the block can move down
    QColor darkenColor(const QColor& color); // Darken the color
    QColor brightenColor(const QColor& color); // Brighten the color

};

#endif // TETRISGAME_H
