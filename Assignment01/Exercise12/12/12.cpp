#include <iostream>

using namespace std;


int fiboiter(int n) {     // 재귀함수를 쓰지않고 피보나치수를 구하는 방식
    int a = 0, b = 1, c;   //수열이 0과1로 시작하기 때문에 
   
    if (n == 1)              //첫번째를 구하고자 할때
    {
        return b;
    }
    for (int i = 3; i <= n; i++) {  //실질적인 연산은 3항부터 시작하니까 i=3 으로 설정함
        c = a + b;         
        a = b;
        b = c;
    }
    return b;
}
int fiborec(int n) {   //재귀함수를 사용하여 피보나치수 구하기
    if (n <= 2) {
        return n-1;
    }
    return fiborec(n - 1) + fiborec(n - 2);  //3번째항=2번째항 + 첫번재 항 을 재귀함수로 구현한것
}


int main() {
    int input;
   
    cout << "Enter the number: ";
    cin >> input;
    cout << "Fibonacci_iter(" << input << "): " << fiboiter(input) << endl;
    cout << "Fibonacci_rec(" << input << "): " << fiborec(input) << endl;



}