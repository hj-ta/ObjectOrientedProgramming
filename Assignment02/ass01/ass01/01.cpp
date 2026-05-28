#include <iostream>
#include <ctime>
using namespace std;

int main() {
	srand(time(NULL));

	int size = rand() % 16 + 5;  // 배열 사이즈는 5~20 까지 랜덤으로 생성
	int* arr = new int[size];

	for (int i = 0; i <= size; i++) { //
		int num = rand() % 101;
		arr[i] = num;
	}
	int max = -1;
	int min = 101;  //저번에 출력했는데 max 값이 배열에 없는값인100이 나왔음 왜 그런지 나중에 알아보자
	int max_idx, min_idx = 0;

	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {     //최대값 찾기,주소값 저장
			max = arr[i];
			max_idx = i;
		}

		if (arr[i] < min) {   //최소값 찾기,주소값 저장
			min = arr[i];
			min_idx = i;
		}
	}

	cout << "Size of the arry: " << size << "\n";    //출력
	cout << "Random numbers: ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n\n";

	cout << "Maxinum value : " << max << "\t,Adress: " << &arr[max_idx] << "\n";
	cout << "Mininum value : " << min << "\t,Adress: " << &arr[min_idx] << "\n";

}