#include <iostream>
#include <ctime>
using namespace std;

void printarry(int arr[], int size) {  //배열을 출력하는 함수, 후에 값이 없을때도
	for (int i = 0; i < size; i++) {   // 출력을 해야하기 때문에 따로 만듬
		cout << arr[i] << " ";
	}
	cout << endl;
}

void quicksort(int arr[], int low, int high) {  //퀵소트 함수
	if (low < high) {
		int pivot = arr[high];
		int i = low - 1;

		for (int j = low; j < high; j++) {
			if (arr[j] <= pivot) {
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[high]);
		int pi = i + 1;
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
		
	}

}

void merge(int arr[], int low, int mid, int high) { //이거 다시생각
	int n1 = mid - low + 1;
	int n2 = high - mid;

	int* L = new int[n1];
	int* R = new int[n2];

	for (int i = 0; i < n1; i++) {
		L[i] = arr[low + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = arr[mid + 1 + j];
	}

	int i = 0, j = 0, k = low; // 변수를 일렬로 선언하면 안되는건가?
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = R[j];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	 }
}


void mergesort(int arr[], int low, int high) {
	if (low < high) {
		int mid = low + (high - low) / 2;
		mergesort(arr, low, mid);
		mergesort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}


int binarySearch(const int arr[], int target, int size) { 
	int left = 0, right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (arr[mid] == target)
			return mid;

		else if (arr[mid] < target)
			left = mid + 1;

		else
			right = mid - 1;
	}
	return left;
}

int main() {
	srand(time(NULL));   //null=0?
	const int size = 10;
	int numbers[size + 1];

	for (int i = 0; i < size; ++i) { //++i, i++ 차이?
		numbers[i] = rand() % 101;
	}
	
	cout << "Random values: ";
	printarry(numbers, size);

	int method;
	cout << "Select sorting method (1:Quick Sort, 2 : Merge Sort):";
	cin >> method;

	if (method == 1) {
		quicksort(numbers, 0, size - 1);
		cout << "Sorted numbes (Quick Sort) : ";
	}
	else if (method == 2) {
		mergesort(numbers, 0, size - 1);
		cout << "Sorted numbes (Merge Sort) : ";
	}
	printarry(numbers, size);

	int searchValue;
	cout << "Enter a value to search: ";
	cin >> searchValue;
	int index = binarySearch(numbers, searchValue, size);

	if (numbers[index] == searchValue)
		cout << "Searched number index: " << index << endl;
	else {
		//index A?? searchValue 해야되나?

		for (int i = size; i > index; i--)
		numbers[i] = numbers[i - 1];
		numbers[index] = searchValue;
		cout << "Updated numbers: ";
		printarry(numbers, size + 1);
	}

}