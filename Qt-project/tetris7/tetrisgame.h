#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QObject>
#include <QColor>
#include <vector>
#include <queue>

class TetrisGame : public QObject
{
    Q_OBJECT

public:
    TetrisGame();
    ~TetrisGame();

    int rows; // Number of rows in the game board
    int cols; // Number of columns in the game board
    double currentRow; // Current row position of the falling block
    double currentCol; // Current column position of the falling block
    int score; // Current score
    bool isGameOver; // Game over flag

    std::vector<std::vector<std::string>> board; // Game board
    std::vector<std::vector<QColor>> boardColors; // Colors of the game board
    std::vector<std::vector<std::vector<int>>> shapes; // Shapes of the Tetris blocks
    std::vector<QColor> shapeColors; // Colors of the Tetris blocks
    std::vector<std::vector<int>> currentShape; // Current shape of the falling block
    int currentShapeIndex; // Index of the current shape
    std::queue<int> nextQueue; // Queue for the next shapes

    std::vector<std::vector<int>> getCurrentShape() const; // Get the current shape
    void rotateCurrentShapeClockwise(); // Rotate the current shape clockwise
    void rotateCurrentShapeCounterClockwise(); // Rotate the current shape counterclockwise
    void dropBlock(); // Drop the current block
    int getRandomShape(); // Get a random shape
    void fixBlock(); // Fix the current block on the board
    void clearFullLines(); // Clear full lines on the board
    bool checkGameOver(); // Check if the game is over
    std::vector<std::vector<int>> rotateShape(const std::vector<std::vector<int>>& shape, bool clockwise); // Rotate a shape
    bool canRotate(const std::vector<std::vector<int>>& rotatedShape) const; // Check if a shape can be rotated
    bool canMoveDown() const; // Check if the current shape can move down
    void generateNextShapes(); // Generate the next shapes
    void spawnNewShape(); // Spawn a new shape

signals:
    void linesCleared(); // Signal emitted when lines are cleared
    void gameOver(); // Signal emitted when the game is over

private:
    void initializeBoard(); // Initialize the game board
};

#endif // TETRISGAME_H
