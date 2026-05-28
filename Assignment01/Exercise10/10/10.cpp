#include <iostream>

using namespace std;

int main()
{
	int row;  //행 갯수

	char spa[20][20]; //2차원 문자열에 별을 찍고 꺼낼것.spa는 평면space를 의미한다.
	cout << "Enter the number of rows: ";
	cin >> row;

	for (int i = 0; i < row; i++)     //2중 for문을 이용해 배열 안에 공백을 먼저 찍는다.
	{
		for(int j=0; j<row; j++)
		{
			spa[i][j] = ' ';
		}
	}
	spa[0][row / 2] = '*';          //1번째행(0행) 중간에 첫번째 별을 찍는다. row 값이 모두 홀수이기 때문에 row/2 가 딱 중간이다

	 
  // 중앙 맨위의 별에서부터 왼쪽 오른쪽 을 나눠 찍을것이다. 먼저 다이아몬드<> 중 왼쪽 절반을 < 이모양대로 위에서부터 내려가면서 찍을 것이다.


	for (int i = 0; i < row; i++)      //for 문을 이용해 배열을 훑으면서 별을 만나면 조건에 따라 왼쪽 아래 혹은 오른쪽 아래에 별을 찍을것
	{
		for (int j = 0; j < row; j++)
		{
			if (spa[i][j] == '*')    //별을 만나면 아래 조건문에 따라 어느위치에 별을 찍을지 결정
			{
				if (i < row / 2)    // i가 row/2 일 때니까 행값이 작을 때, 즉 위쪽이다. 모양으로는 < 중에서 위쪽 절반인 / 이다.
				{
					spa[i + 1][j - 1] = '*';       // < 중에서 / 모양을 찍을땐 왼쪽 아래로 찍어야 하기 때문에 다음과 같이 설정
				}
				else{
					spa[i + 1][j + 1] = '*';       // < 중에서 
				}

			}

		}
	}

	// 이제 다이아몬드 <> 중에 >를 출력할 차례이다. 이번엔 아래에서 위로 올라간다. 따라서 오른쪽 맨 아래 부터 시작한다.

	for (int i = row - 1; i > 0; i--)     // 아래에서 위로 올라간다.
	{
		for (int j = row - 1; j > 0; j--)
		{
			if (spa[i][j] == '*')
			{
				if (i > row / 2)       // > 중 위쪽 이라면 왼쪽 위로 찍는다
				{
					spa[i - 1][j + 1] = '*';
					break;                    //break 안해주면 같은 행에있는 다른 별을 만나 또 별을 찍어 오류가난다.
				}
				else
				{
					spa[i - 1][j +-1] = '*';    // > 중 아래쪽 이라면 만난별 기준 오른쪽 위에 별을 찍는다.
					break;
				}

			}
		}
	}

	for (int i = 0; i < row; i++)     //출력한다.
	{
		for (int j = 0; j < row; j++)
		{
			cout << spa[i][j];
		}
		cout << endl;
	}





}
