#include <iostream>

using namespace std;


class Matrix {
private:
	double data[4][4];
	int row, col;

public:
	Matrix() :row(4), col(4) { //생성자?
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				data[i][j] = 0;
			}
		}
	}

	~Matrix() {}

	void setValue(double arr[4][4]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				data[i][j] = arr[i][j];
			}
		}
	}

	void display() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}


	//행렬끼리 연산
	Matrix operator+(const Matrix& mtx) {
		Matrix result;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.data[i][j] = this->data[i][j] + mtx.data[i][j];
			}
		}
		return result;
	}

	Matrix operator-(const Matrix& mtx) {
		Matrix result;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.data[i][j] = this->data[i][j] - mtx.data[i][j];
				//     아님 그냥 = data[][]-mtx[][]

			}
		}
		return result;
	}

	Matrix operator*(const Matrix& mtx) {
		Matrix result;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.data[i][j] = 0;
				for (int k = 0; k < col; k++)
					result.data[i][j] += this->data[i][k] * mtx.data[k][j];
			}
		}
		return result;
	}

	//스칼라 연산
	Matrix operator+(int Scalar)const {
		Matrix result;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.data[i][j] = this->data[i][j] + Scalar;
			}
		}
		return result;
	}

	Matrix operator-(int Scalar)const {
		Matrix result;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.data[i][j] = this->data[i][j] - Scalar;
			}
		}
		return result;
	}
	Matrix operator*(int Scalar)const {
		Matrix result;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.data[i][j] = this->data[i][j] * Scalar;
			}
		}
		return result;
	}
	Matrix operator/(int Scalar)const {
		Matrix result;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.data[i][j] = this->data[i][j] / Scalar;
			}
		}
		return result;
	}



};

int main() {
	Matrix mat1, mat2;

	double arr1[4][4]{
		{2, 3, 4, 5},
		{6, 7, 8, 9},
		{9, 12, 15, 18},
		{3, 9, 0, 2}
	};

	double arr2[4][4]{
		{1, 3, 2, 1},
		{0, 1, 1, 0},
		{3, 2, 0, 1},
		{2, 1, 0, 3}
	};

	mat1.setValue(arr1);
	mat2.setValue(arr2);

	Matrix mat3 = mat1 - mat2;

	Matrix mat4 = mat1 * mat2;

	cout << "Matrix 1:" << endl;
	mat1.display();

	cout << "\nMatrix 2:" << endl;
	mat2.display();

	cout << "\nMatrix 3:" << endl;
	mat3.display();

	cout << "\nMatrix 4 (Matrix1 * Matrix2)" << endl;
	mat4.display();

	// 스칼라 연산
	int Scalar = 3;

	Matrix ScalarAdd = mat1 + Scalar;
	Matrix ScalarSub = mat1 - Scalar;
	Matrix ScalarMul = mat1 * Scalar;
	Matrix ScalarDiv = mat1 / Scalar;

	cout << "\n------------------------\n\n";

	cout << "Matrix 1 : " << endl;
	mat1.display();

	cout << "\nMatrix1 ScalarAdd with " << Scalar << " : " << endl;
	ScalarAdd.display();

	cout << "\nMatrix1 ScalarSub with " << Scalar << " : " << endl;
	ScalarSub.display();

	cout << "\nMatrix1 ScalarMul with " << Scalar << " : " << endl;
	ScalarMul.display();

	cout << "\nMatrix1 ScalarDiv with " << Scalar << " : " << endl;
	ScalarDiv.display();


	return 0;
}