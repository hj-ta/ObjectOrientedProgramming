#include <iostream>

using namespace std;
int main() {
    char input[10];
    int head = 0;  //첫 번째 문자(0번지)
    int tail = 9;  //마지막 문자(9번지)
    cout << "Enter ten characters: ";
    for (int i = 0; i < 10; i++) {    //문자열로 입력받기
        cin >> input[i];
    }
    cout << "Input characters are:" << endl;
    for (int j = 0; j < 5; j++) {       //문자 2개씩 짝지어서 출력하는데,그걸 5번 반복한다
        cout << input[head] << " " << input[tail] << endl;

        head++;          // for 문을 반복할때마다 head는 0에서 1씩 증가
        tail--;          //for 문을 반복할때마다 tail은 9에서 1씩 감소 
    }
        // (위에꺼 종료조건은 n>9-n)k
        


    return 0;
}