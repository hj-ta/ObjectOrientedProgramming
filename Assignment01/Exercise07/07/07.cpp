#include <iostream>

using namespace std;

int pow(int exponent, int power) {       //재귀함수를 만들고 각 변수는 곱하는수, 곱하는 횟수(즉 지수)로 설정해준다.
    if (power == 0) {  //숫자^0=1임을 이용하여 종료조건을 설정
        return 1;
    }
    else {    //아닐경우 재귀함수로 자기자신을 호출하게 만든다. 종료조건 전까지
        return exponent * pow(exponent, power - 1);
    }
}

int main() {
    int exponent, power;   //변수선언
    cout << "Enter the exponent: ";   //곱할 값을 입력받는다
    cin >> exponent;
    cout << "Enter the power: ";       //곱할 횟수 (n승, 즉 지수)를 입력받는다.
    cin >> power;
    cout << "power(" << exponent << "," << power << "): " << pow(exponent, power) << endl;  //재귀함수를 연산한값을 출력해준다.


}