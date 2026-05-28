#include <iostream>

using namespace std;
int main() {
	int num;  //몫
	int temp;  // 나머지
	int result = 0;  //결과값


	cout << "Enter the number: ";
	cin >> num;              //초기num은 입력값

	while (num != 0)       //종료조건 : 몫이 0이될때
	{
		temp = num % 10;   //몫을 10으로 나눈값의 나머지가 temp ==>1의 자릿수
		num = num / 10; //num을 `0으로 나눈값의 몫을 다시 num에 저장 (초기num 값은 입력숫자)

	    result = result * 10 + temp ;  //10배씩 커지면서, 일의자리였던 숫자가 왼쪽으로 한칸씩 밀려나는게 보임(몇자리수인지 정해지지 않았으니 한번에 보내는게 아니라 한칸씩 밀어서 보내는것이다.)
	}                                 // 전에 구한식에 10을 곱한후, 나머지연산으로 구한 숫자를 더해서 result 구한다.(3--> 3*10+6 --> 3*100+6*10+2 --> 3*1000+6*100+2*10+8 // 8263-->3628 ) 

	cout << "Reversed number: " << result;   

	
	return 0;
}
 