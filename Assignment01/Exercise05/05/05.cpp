#include <iostream>

using namespace std;
int main() {

	int num;   //입력받는 숫자
	int a;     // (10^n으로) 나누어줄 값이다. 나눠서 각 자리숫자들을 만들어야되기때문에 
	int first;   //

	cout << "Enter the number: ";
	cin >> num;
	
	int b ;   //10의n승을 구현할때 사용해 줄것이다 10^n 와 같이 자릿수를 담을것

	for (int i = 5; i > 0; i--)  //전체에 대한 포문, 1행이 i=5 가 되도록 조건을 설정 (형식이 항상 5로 정해져있기 때문에 5에서 감소하는 식으로 조건을 만듬)
	{
		for (int j = 1; j <= i; j++)//한 행에대한 반복문(위에서 첫행을 i=5로 두었기 때문에 첫번째 행에 i까지면 5개 , 두번째 행일때 i=4고 4개 숫자 이런식으로 출력할수있다. )
		{
			a = num;
			b = 1;        //b의값을 초기화 해준다.

			for (int k = i - j; k >= 1; k--)//한 자릿수에 대한 포문
			{
			    a = a / 10;
				b = b * 10;                // 자릿수,즉 10의n승 변수는 b 에 담을꺼임 어덯게? 포문을 자릿수만큼 돌리면서
			}                              //1행1열에서 필요한 b값은 10^4 그때 i값은 5, j값은 1,그럼 k=4, 포문이4번돌면서10^4
			cout << a << "  "; 
			 
			if(j==1)    
			{
				first = num % b;      //

			}
			num = num % b;     //

		}
		num = first;


		cout << "\n";  //단락나누기

	}



	return 0;
}