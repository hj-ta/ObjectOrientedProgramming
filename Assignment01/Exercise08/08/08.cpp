#include <iostream>

using namespace std;

int gcd(int first, int second) {//최대공약수를 구하는 재귀함수이다.

    if (second == 0) {  //종료조건으로 나머지가 0이면 나누어 떨어진다는것임으로 약수가 되니 재귀함수 호출을 멈춘다.
        return first;
    }
    else {   //최대공약수를 구하기 위한 모듈러 연산을 유클리드 호제법에 따라 해준다. 
        return gcd(second, first % second);
    }
}

int main() {
    int first, second;
    cout << "Enter the 1st number: ";
    cin >> first;                       //1번 숫자 입력 받기

    cout << "Enter the 2nd number: ";
    cin >> second;                     //2번 숫자 입력 받기

    cout << "gcd(" << first << "," << second << "): " << gcd(first, second) << endl;  //재귀함수를 연산하고 최종값 출력한다


}