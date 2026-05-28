#include<iostream>

using namespace std;

void generateMatrix(int** matrix, int size) {
	if (size == 1) {  //기저조건일때
		matrix[0][0] = 1;
		return;
	}
	generateMatrix(matrix, size / 2);  //1사분면에 해당하는 행렬, 복사해줄값

	for (int i = 0; i < size / 2; i++) {  //2.3분에 값을 그대로 복사하고, 4분면에는 -1을 곱한후 입력
		for (int j = 0; j < size / 2; j++) {
			matrix[i][j+size/2] = matrix[i][j];  //제2사분면
			matrix[i + size / 2][j] = matrix[i][j];  //제3사분면
			matrix[i + size / 2][j + size / 2] = -matrix[i][j]; //제4사분면
		}
	}
}

void printMatrix(int** matrix, int size) {  //행렬을 만들어 출력하는 함수
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] == 1) cout << " " << matrix[i][j] << " ";
			else cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {

	int n;
	cout << "Enter the value of n for Hadamard matrix (2^n x 2^n) :";
	cin >>n;

	int size;

	size = 1 << n; //비트연산을 통해 2의n승에 해당하는 사이즈를 출력핟록 연산
	cout << size;

	int** hadamardMatrix = new int* [size];  //size 개수만큼의 포인터변수를 같는 행렬을 동적할당

	for (int i = 0; i < size; i++) {
		hadamardMatrix[i] = new int [size];  //위에 해당하는 한칸에 또 하나의 배열??을 생성
	}

	generateMatrix(hadamardMatrix, size);
	cout << "Hadamard Matrix of size " << size << "x" << size << ":\n";
	printMatrix(hadamardMatrix, size);

	for (int i = 0; i < size; i++) {
		delete[] hadamardMatrix[i];    //할당한 메모리 해제
	}
	delete[] hadamardMatrix;

	return 0;
}