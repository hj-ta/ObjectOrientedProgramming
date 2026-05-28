#include <iostream>

using namespace std;

bool multiple(int first, int second) {  //정수 두개를 인수로 받는다
    if (second % first == 0) {  //참일 조건 : 나누어 떨어질때, 즉 배수일때
        return true;          //참을 출력
    }
    else {
        return false;        //거짓을 출력
    }
}


int main() {
    int first, second;
    bool result;   //bool형 사용

    cout << "Enter the 1st number: ";
    cin >> first;
    cout << "Enter the 2nd number: ";
    cin >> second;
   
    cout << boolalpha;    
    result = multiple(first, second);
    cout << "multiple(" << first << "," << second << "):" << result << endl;

   //조건에 해당하면 1,즉 true를 출력하고 해당되지 않으면 0, 즉 false를 출력한다.



}