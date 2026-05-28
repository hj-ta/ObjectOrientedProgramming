#include <iostream>
#include <ctime>

using namespace std;



void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void printMatrixWithTotal(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        int total = 0;
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
            total += matrix[i][j];
        }
        cout << "| Sum: " << total;
        cout << endl;
    }
}

void generateRandomMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 101;
        }
    }
}

void swapIntPointer(int*& ptr1, int*& ptr2) {
    int* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

void swapRows(int**& matrix, int row1, int row2, int cols) {
    for (int j = 0; j < cols; ++j) {
        swap(matrix[row1][j], matrix[row2][j]);
    }
}

void sortByDescendingRows(int**& matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols - 1; ++j) {
            for (int k = 0; k < cols - j - 1; ++k) {
                if (matrix[i][k] < matrix[i][k + 1]) {
                    int temp = matrix[i][k];
                    matrix[i][k] = matrix[i][k + 1];
                    matrix[i][k + 1] = temp;
                }
            }
        }
    }
}

int rowSum(int* row, int cols) {
    int sum = 0;
    for (int i = 0; i < cols; ++i) {
        sum += row[i];
    }
    return sum;
}

void sortByAscendingRowSum(int**& matrix, int rows, int cols) {
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = i + 1; j < rows; ++j) {
            if (rowSum(matrix[i], cols) > rowSum(matrix[j], cols)) {
                swapRows(matrix, i, j, cols);
            }
        }
    }
}

int main() {
    srand(time(0));
    const int rows = 10;
    const int cols = 10;

    /*int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }*/

    // Hardcoded 2D array
    int arr[10][10] = {
        {55,98,26,77,68,0,59,63,96,14},
        {14,46,37,45,49,94,81,61,14,50},
        {11,24,50,3,97,1,5,72,98,85},
        {80,53,52,26,2,37,88,51,10,96},
        {25,11,15,97,2,53,69,88,72,55},
        {15,99,32,9,34,2,4,5,89,57},
        {36,21,82,1,11,53,32,9,47,41},
        {44,47,65,76,49,25,28,94,23,25},
        {77,71,91,81,95,34,61,19,84,45},
        {2,84,35,97,89,53,32,5,80,22}
    };

    // Convert to int**
    int** matrix = new int* [10];
    for (int i = 0; i < 10; ++i) {
        matrix[i] = new int[10];
        for (int j = 0; j < 10; ++j) {
            matrix[i][j] = arr[i][j];
        }
    }

    //generateRandomMatrix(matrix, rows, cols);

    cout << "Original Matrix:" << endl;
    printMatrix(matrix, rows, cols);

    cout << "\nSort by Row (Descending Order):" << endl;
    sortByDescendingRows(matrix, rows, cols);
    printMatrixWithTotal(matrix, rows, cols);

    cout << "\nSort by Sum (Ascending Order):" << endl;
    sortByAscendingRowSum(matrix, rows, cols);
    printMatrixWithTotal(matrix, rows, cols);

   // return 0;
}
