#include <iostream>

using namespace std;
                                //최소공배수*최대공약수=두수의곱 이용, 8번의 최대공약수 식 이용하기위한
int gcd(int first, int second) {//재귀함수 gcd 에 대한 선언

    if (second == 0) {  //종료조건: 나머지가 0일때, 즉 나누어떨어질때
        return first;   //first를 반환
    }
    else {
        return gcd(second, first % second);  // 그렇지 않으면 계속해서 자기자신을 호출
    }
}

int lcm(int first, int second) {   //함수 lcm 에 대한 선언

        return first * second / gcd(first, second); //if와 else를 나누어 생각할 필요가 없으므로 두수의곱 나누기 최대공약수를 출력한다. 그것이 최소공배수이다.

}

int main() {
    int first, second;
    cout << "Enter the 1st number: ";
    cin >> first;                     //first 값 입력받는다

    cout << "Enter the 2nd number: ";
    cin >> second;                  //second 값 입력받는다

    cout << "lcm(" << first << "," << second << "): " << lcm(first, second) << endl;   //재귀함수 lcm을 형식에 맞춰 출력한다.


}