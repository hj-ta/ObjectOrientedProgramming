#include <iostream>


using namespace std;

int main()
{
	int a;

	
	cout << "Enter the five numbers: ";
	//cin>>a>>b>>c>>d>>e
	//cin은 공백,개행,탭 등 문자 무시
	cin >> a;   //입력을 이미 한번 받음
	int avg = a;
	int max = a;
	int min = a;


	
	for (int i = 1; i < 5; i++)  //위에서 초기값을 첫번째 a 값으로 저장했기 때문에 i가 0~4가 아니라1~4인것이다.
	{
		cin >> a;

		if(min>a)//돌면서 최솟값 찾기
		{
			min = a;
		}
		if (a > max)//돌면서 최댓값 찾기
		{
			max = a;
		}

		avg += a; //받으면서 평균을 구하기전 먼저 sum
	
	}


	if (avg >0) {//평균값이 양수일때
		if (avg % 5 > 0)//즉, 소숫점이 생기면(딱나누어떨x)
		{
			if ((avg % 5) / 5.0 > 0.5)//소숫점!
			{
				avg = (avg / 5) + 1;
			}
			else
			{
				avg = (avg / 5);
			}
		}
		else //저 위에꺼에 대한 else임
		{
			avg = avg / 5;
		}
	}

    else { //평균값이 음수일때

		if (( - 1 * avg) % 5 > 0)//즉, 소숫점이 생기면(딱나누어떨x)
		{
			if ((( - 1 * avg) % 5) / 5.0 > 0.5)//소숫점!
			{
				avg = (avg / 5) -1;
			}
			else{
			
				avg = (avg / 5);
			}
		}
		else 
		{
			avg = avg / 5;
		}

	}



	cout << "MIN: " << min << endl;
	cout << "MAX: " << max << endl;
	cout << "AVG: " << avg << endl;
}
 